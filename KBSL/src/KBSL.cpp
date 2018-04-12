/**
* Assignment 3 Robust Plane Fitting SOLUTIONS
*/
#include <algorithm>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <geometry_msgs/Point32.h>
#include <sensor_msgs/PointCloud.h>

#include "KBSL/TransformPointSrv.h"
#include "KBSL/FitMinimalPlaneSrv.h"
#include "KBSL/FindInliersSrv.h"
#include "KBSL/FitBestPlaneSrv.h"
#include "KBSL/PlaneParametersMsg.h"

using Eigen::Matrix3f;
using Eigen::Vector3f;
using geometry_msgs::Point32;
using namespace std;

#define PI 3.14159265

//USER PARAMETERS
double kinect_angle = 45.0;
double kinect_height = 0.5;
double user_width = 0.1;
double user_height = 0.8;

float adjusted_height = kinect_height;

float max_sensor_dist = 100;

Vector3f floor_norm(1.0,0,0);
float norm_tol = 1.0;
float max_ground = 3.0;

sensor_msgs::PointCloud full_point_cloud;
// Message for published filtered 3D point clouds.
sensor_msgs::PointCloud ground_point_cloud;
sensor_msgs::PointCloud obstacles_point_cloud;

float x_min = max_sensor_dist;
float x_max = -1*max_sensor_dist;
float y_min = max_sensor_dist;
float y_max = -1*max_sensor_dist;
float z_min = max_sensor_dist;
float z_max = -1*max_sensor_dist;


//DownSampled PointCloud ----- Convert These to Sound
vector<float> angles;
vector<float> angle_distances;

// Publisher for 3D plane filtered point clouds.
ros::Publisher filtered_point_cloud_publisher_;

// RANSAC parameters.
static const int kIterations = 50;
static const float kMinInlierFraction = 0.7;
static const float kEpsilon = 0.03;

struct Rect{
  Rect(float a, Vector3f near, Vector3f far){
    ang = a;
    nearPnt = near;
    farPnt = far;
  }
  float ang;
  Vector3f nearPnt;
  Vector3f farPnt;
};

bool npInRange(Vector3f n, Vector3f p){
  //TODO
  //if angle between n and floor_norm > norm_tol return false
  //else if p.z < z_max ground return false
  //else return true
  return true;
}

// Helper function to convert ROS Point32 to Eigen Vectors.
Vector3f ConvertPointToVector(const Point32& point) {
  return Vector3f(point.x, point.y, point.z);
}

// Helper function to convert Eigen Vectors to ROS Point32.
Point32 ConvertVectorToPoint(const Vector3f& vector) {
  Point32 point;
  point.x = vector.x();
  point.y = vector.y();
  point.z = vector.z();
  return point;
}

void FitMinimalPlane(const Vector3f& P1, const Vector3f& P2, const Vector3f& P3,
                     Vector3f* n, Vector3f* P0) {
  *P0 = P1;
  const Vector3f P21 = P2 - P1;
  const Vector3f P31 = P3 - P1;
  *n = (P21.cross(P31)).normalized();
}

void FindInliers(const Vector3f& n, const Vector3f& P0, float epsilon,
    const vector<Vector3f>& point_cloud, vector<Vector3f>* inliers) {

  inliers->clear();
  for (size_t i = 0; i < point_cloud.size(); ++i) {
    if (fabs((point_cloud[i] - P0).dot(n)) < epsilon) {
      inliers->push_back(point_cloud[i]);
    }
  }
}

void FindInliersFloorObs(const Vector3f& n, const Vector3f& P0, float epsilon,
    const vector<Vector3f>& point_cloud, vector<Vector3f>* inliers, vector<Vector3f>* outliers) {

  x_min = max_sensor_dist;
  x_max = -1* max_sensor_dist;
  y_min = max_sensor_dist;
  y_max = -1* max_sensor_dist;
  z_min = max_sensor_dist;
  z_max = -1*max_sensor_dist;

  inliers->clear();
  for (size_t i = 0; i < point_cloud.size(); ++i) {

    if(point_cloud[i].x() < x_min) x_min = point_cloud[i].x();
    if(point_cloud[i].x() > x_max) x_max = point_cloud[i].x();
    if(point_cloud[i].y() < y_min) y_min = point_cloud[i].y();
    if(point_cloud[i].y() > y_max) y_max = point_cloud[i].y();
    if(point_cloud[i].z() < z_min) z_min = point_cloud[i].z();
    if(point_cloud[i].z() > z_max) z_max = point_cloud[i].z();

    if(y_min < 0) adjusted_height = -1*y_min;
    else adjusted_height = y_min;

    if (fabs((point_cloud[i] - P0).dot(n)) < epsilon) {
      inliers->push_back(point_cloud[i]);
    }
    else{
      outliers->push_back(point_cloud[i]);
    }
  }
}

Vector3f PickRandomPoint(const vector<Vector3f>& point_cloud) {
  if(point_cloud.size() == 0){
    return Vector3f();
  }
  else{
    const int i = rand() % (point_cloud.size());
    return point_cloud[i];
  }
}

Vector3f GetSmallestEigenVector(const Matrix3f& M) {
  // Initialize the eigenvalue solver.
  Eigen::EigenSolver<Matrix3f> eigen_solver;
  // Ask the solver to compute the eigen values and vectors.
  eigen_solver.compute(M);
  // Get all the eigenvalues. Note the result is complex-valued, and we are
  // asking for only the real component by calling ".real()" over the result.
  Vector3f eigen_values = eigen_solver.eigenvalues().real();
  // Get all the eigenvectors. Note the result is complex-valued, and we are
  // asking for only the real component by calling ".real()" over the result.
  Matrix3f eigen_vectors = eigen_solver.eigenvectors().real();

  float smallest_eigenvalue = eigen_values(0);
  Vector3f smallest_eigenvector = eigen_vectors.col(0);
  for (int i = 1; i < 3; ++i) {
    if (eigen_values(i) < smallest_eigenvalue) {
      smallest_eigenvalue = eigen_values(i);
      smallest_eigenvector = eigen_vectors.col(i);
    }
  }
  return (smallest_eigenvector.normalized());
}

void FitBestPlane(const vector<Vector3f>& point_cloud, Vector3f* n_ptr,
                  Vector3f* P0_ptr) {
  // Alias of n.
  Vector3f& n = *n_ptr;
  // Alias of P0.
  Vector3f& P0 = *P0_ptr;

  // Find P0.
  P0.setZero();
  for (size_t i = 0; i < point_cloud.size(); ++i) {
    P0 += point_cloud[i];
  }
  P0 = P0 / static_cast<float>(point_cloud.size());

  // Build M matrix.
  Matrix3f M;
  M.setZero();
  for (size_t i = 0; i < point_cloud.size(); ++i) {
    M = M + (point_cloud[i] - P0) * (point_cloud[i] - P0).transpose();
  }
  n = GetSmallestEigenVector(M);
}

void RANSAC_MOD(const vector<Vector3f>& point_cloud, Vector3f* n_ptr,
            Vector3f* P0_ptr) {

  vector<Vector3f> near_floor_pnts;
  // Copy over the input point cloud - filtering out points above y-max
  for (size_t i = 0; i < point_cloud.size(); ++i) {
    if(point_cloud[i].z() < max_ground){
      near_floor_pnts.push_back(point_cloud[i]);
    }
  }

  // Alias of n.
  Vector3f& n = *n_ptr;
  // Alias of P0.
  Vector3f& P0 = *P0_ptr;

  // Run RANSAC.
  vector<Vector3f> inliers;
  float inlier_fraction = 0;
  int i = 0;
  do {
    ++i;
    const Vector3f P1 = PickRandomPoint(near_floor_pnts);
    const Vector3f P2 = PickRandomPoint(near_floor_pnts);
    const Vector3f P3 = PickRandomPoint(near_floor_pnts);
    FitMinimalPlane(P1, P2, P3, &n, &P0);
    FindInliers(n, P0, kEpsilon, near_floor_pnts, &inliers);
    inlier_fraction = static_cast<float>(inliers.size()) /
        static_cast<float>(near_floor_pnts.size());
  } while (i < kIterations && inlier_fraction < kMinInlierFraction && npInRange(*n_ptr, *P0_ptr));
  FitBestPlane(inliers, n_ptr, P0_ptr);
}

void PointCloudCallback(const sensor_msgs::PointCloud& point_cloud_msg) {
  //TODO perform rotation
  //Perform transformation

  sensor_msgs::PointCloud trans_pnt_cloud;
  trans_pnt_cloud.header = point_cloud_msg.header;

  Matrix3f R;
  //Y-Rotation
  R(0, 0) = cos(kinect_angle*PI/180.0);
  R(0, 2) = sin(kinect_angle*PI/180.0);
  R(1, 1) = 1;
  R(2, 0) = -1.0*sin(kinect_angle*PI/180.0);
  R(2, 2) = cos(kinect_angle*PI/180.0);
  // R(0, 0) = 1.0;
  // R(1, 1) = 1.0;
  // R(2, 2) = 1.0;


  // const Vector3f T(0.0, 0.0, 0.5);
  const Vector3f T(0.0, 0.0, 0.0);

  for(int i = 0; i<(int)point_cloud_msg.points.size(); i++){
    Vector3f P(point_cloud_msg.points[i].x, point_cloud_msg.points[i].y, point_cloud_msg.points[i].z);
    // Compute P_prime from P, R, T.
    Vector3f P_prime = R * P + T;

    Point32 new_point;
    new_point.x = P_prime.x();
    new_point.y = P_prime.y();
    new_point.z = P_prime.z();

    trans_pnt_cloud.points.push_back(new_point);
  }

  full_point_cloud = trans_pnt_cloud;

}

void updateClouds(){
  
  ground_point_cloud.header = full_point_cloud.header;
  obstacles_point_cloud.header = full_point_cloud.header;

  // Create a Vector3f point cloud, of the same size as the input point cloud.
  vector<Vector3f> point_cloud(full_point_cloud.points.size());

  // Copy over the input point cloud.
  for (size_t i = 0; i < point_cloud.size(); ++i) {
    point_cloud[i] = ConvertPointToVector(full_point_cloud.points[i]);
  }

  vector<Vector3f> filtered_point_cloud_ground;
  vector<Vector3f> filtered_point_cloud_obstacles;
  Vector3f n;
  Vector3f P0;
  // Extract filtered point cloud.
  RANSAC_MOD(point_cloud, &n, &P0);
  FindInliersFloorObs(n, P0, kEpsilon, point_cloud, &filtered_point_cloud_ground, &filtered_point_cloud_obstacles);

  // Copy over the output for ground points.
  ground_point_cloud.points.resize(filtered_point_cloud_ground.size());
  for (size_t i = 0; i < filtered_point_cloud_ground.size(); ++i) {
    ground_point_cloud.points[i] =
        ConvertVectorToPoint(filtered_point_cloud_ground[i]);
  }

  //Copy over the output for obstacle points
  obstacles_point_cloud.points.resize(filtered_point_cloud_obstacles.size());
  for (size_t i = 0; i < filtered_point_cloud_obstacles.size(); ++i) {
    obstacles_point_cloud.points[i] =
        ConvertVectorToPoint(filtered_point_cloud_obstacles[i]);
  }

  //TEST WHAT THE POINT CLOUD CONTAIN
  filtered_point_cloud_publisher_.publish(obstacles_point_cloud);

}



void obsAvoid(){

  Vector3f origin = Vector3f(0,0,0);

  int numPaths = 5;

  Vector3f originStraight = Vector3f(1,0,0);
  Vector3f originLeft = Vector3f(x_max,y_min,0)/Vector3f(x_max,y_min,0).norm();
  Vector3f originRight = Vector3f(x_max,y_max,0)/Vector3f(x_max,y_max,0).norm();

  float min_ang = acos(originLeft.dot(originStraight) / (originLeft.norm() * originStraight.norm()));
  min_ang *= -1.0;
  float max_ang = acos(originRight.dot(originStraight) / (originRight.norm() * originStraight.norm()));

  float ang_diff = max_ang - min_ang;
  if(ang_diff < 0) ang_diff *= -1;
  float ang_unit = ang_diff/(float)numPaths;

  Vector3f near = Vector3f(0, origin.y() - (user_width/(float)2), origin.z() - kinect_height);
  Vector3f far = Vector3f(0, origin.y() + (user_width/(float)2), origin.z() + (user_height - kinect_height));

  vector<float> ang_vec;
  vector<float> dist_vec;

  for(int i = 0; i<numPaths; i++){
    ang_vec.push_back(min_ang + ((float)i*ang_unit) + (0.5* ang_unit));
    dist_vec.push_back(max_sensor_dist);
  }

  float rot_init = min_ang - (ang_unit*0.5);

  sensor_msgs::PointCloud temp_cloud = obstacles_point_cloud;

  for (int i = 0; i<(int)temp_cloud.points.size(); i++){
    Vector3f currPnt = ConvertPointToVector(temp_cloud.points[i]);
    float x = currPnt.x() * cos(rot_init) + currPnt.y() * sin(rot_init);
    float y = -1*currPnt.x() * sin(rot_init) + currPnt.y() * cos(rot_init);
    currPnt = Vector3f(x, y, currPnt.z()); //R0 * currPnt;

    for(int j = 0; j<(int)ang_vec.size(); j++){
      x = currPnt.x() * cos(ang_unit) + currPnt.y() * sin(ang_unit);
      y = -1*currPnt.x() * sin(ang_unit) + currPnt.y() * cos(ang_unit);
      currPnt = Vector3f(x, y, currPnt.z()); //R0 * currPnt;
      //check if x,y parameters are within rectangle
      if( currPnt.x() < dist_vec[j] and currPnt.y() > near.y() and currPnt.y() < far.y() and currPnt.z() > near.z() and currPnt.z() < far.z()){
        dist_vec[j] = currPnt.x();
      }
    }

  }
  // float test = dist_vec[0];
  // printf("1: %f\n", test);
  // test = dist_vec[1];
  // printf("2: %f\n", test);
  // test = dist_vec[2];
  // printf("3: %f\n", test);
  // test = dist_vec[3];
  // printf("4: %f\n", test);
  // test = dist_vec[4];
  // printf("5: %f\n\n", test);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "KBSL");
  ros::NodeHandle n;

  filtered_point_cloud_publisher_ = n.advertise<sensor_msgs::PointCloud>("/COMPSCI403/FilteredPointCloud", 1);

  ros::Subscriber point_cloud_subscriber =
    n.subscribe("/COMPSCI403/PointCloud", 1, PointCloudCallback);


    ros::Rate loop(2);
    while (ros::ok()) {

      //Call Function To update floor and obstacle point clouds
      updateClouds();
      obsAvoid();

      ros::spinOnce();
      loop.sleep();
    }

  return 0;
}
