/* Auto-generated by genmsg_cpp for file /home/jake/kinetic_workspace/sandbox/Kinect-Based-Sound-Localization/KBSL/srv/FitBestPlaneSrv.srv */
#ifndef KBSL_SERVICE_FITBESTPLANESRV_H
#define KBSL_SERVICE_FITBESTPLANESRV_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "ros/service_traits.h"

#include "geometry_msgs/Point32.h"


#include "geometry_msgs/Point32.h"
#include "geometry_msgs/Point32.h"

namespace KBSL
{
template <class ContainerAllocator>
struct FitBestPlaneSrvRequest_ {
  typedef FitBestPlaneSrvRequest_<ContainerAllocator> Type;

  FitBestPlaneSrvRequest_()
  : P()
  {
  }

  FitBestPlaneSrvRequest_(const ContainerAllocator& _alloc)
  : P(_alloc)
  {
  }

  typedef std::vector< ::geometry_msgs::Point32_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Point32_<ContainerAllocator> >::other >  _P_type;
  std::vector< ::geometry_msgs::Point32_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Point32_<ContainerAllocator> >::other >  P;


  typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator>  const> ConstPtr;
}; // struct FitBestPlaneSrvRequest
typedef  ::KBSL::FitBestPlaneSrvRequest_<std::allocator<void> > FitBestPlaneSrvRequest;

typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvRequest> FitBestPlaneSrvRequestPtr;
typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvRequest const> FitBestPlaneSrvRequestConstPtr;



template <class ContainerAllocator>
struct FitBestPlaneSrvResponse_ {
  typedef FitBestPlaneSrvResponse_<ContainerAllocator> Type;

  FitBestPlaneSrvResponse_()
  : P0()
  , n()
  {
  }

  FitBestPlaneSrvResponse_(const ContainerAllocator& _alloc)
  : P0(_alloc)
  , n(_alloc)
  {
  }

  typedef  ::geometry_msgs::Point32_<ContainerAllocator>  _P0_type;
   ::geometry_msgs::Point32_<ContainerAllocator>  P0;

  typedef  ::geometry_msgs::Point32_<ContainerAllocator>  _n_type;
   ::geometry_msgs::Point32_<ContainerAllocator>  n;


  typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator>  const> ConstPtr;
}; // struct FitBestPlaneSrvResponse
typedef  ::KBSL::FitBestPlaneSrvResponse_<std::allocator<void> > FitBestPlaneSrvResponse;

typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvResponse> FitBestPlaneSrvResponsePtr;
typedef boost::shared_ptr< ::KBSL::FitBestPlaneSrvResponse const> FitBestPlaneSrvResponseConstPtr;


struct FitBestPlaneSrv
{

typedef FitBestPlaneSrvRequest Request;
typedef FitBestPlaneSrvResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct FitBestPlaneSrv
} // namespace KBSL

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "a50f259239b279a44076645ba45c7569";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xa50f259239b279a4ULL;
  static const uint64_t static_value2 = 0x4076645ba45c7569ULL;
};

template<class ContainerAllocator>
struct DataType< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "KBSL/FitBestPlaneSrvRequest";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Point32[] P\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point32\n\
# This contains the position of a point in free space(with 32 bits of precision).\n\
# It is recommeded to use Point wherever possible instead of Point32.  \n\
# \n\
# This recommendation is to promote interoperability.  \n\
#\n\
# This message is designed to take up less space when sending\n\
# lots of points at once, as in the case of a PointCloud.  \n\
\n\
float32 x\n\
float32 y\n\
float32 z\n\
";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "185eea9c3fedfb05e4edf26c506b38ef";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x185eea9c3fedfb05ULL;
  static const uint64_t static_value2 = 0xe4edf26c506b38efULL;
};

template<class ContainerAllocator>
struct DataType< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "KBSL/FitBestPlaneSrvResponse";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Point32 P0\n\
geometry_msgs/Point32 n\n\
\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point32\n\
# This contains the position of a point in free space(with 32 bits of precision).\n\
# It is recommeded to use Point wherever possible instead of Point32.  \n\
# \n\
# This recommendation is to promote interoperability.  \n\
#\n\
# This message is designed to take up less space when sending\n\
# lots of points at once, as in the case of a PointCloud.  \n\
\n\
float32 x\n\
float32 y\n\
float32 z\n\
";
  }

  static const char* value(const  ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.P);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct FitBestPlaneSrvRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.P0);
    stream.next(m.n);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct FitBestPlaneSrvResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<KBSL::FitBestPlaneSrv> {
  static const char* value() 
  {
    return "dc3f7ccf7e8285059dcdda5775cca1b9";
  }

  static const char* value(const KBSL::FitBestPlaneSrv&) { return value(); } 
};

template<>
struct DataType<KBSL::FitBestPlaneSrv> {
  static const char* value() 
  {
    return "KBSL/FitBestPlaneSrv";
  }

  static const char* value(const KBSL::FitBestPlaneSrv&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "dc3f7ccf7e8285059dcdda5775cca1b9";
  }

  static const char* value(const KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "KBSL/FitBestPlaneSrv";
  }

  static const char* value(const KBSL::FitBestPlaneSrvRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "dc3f7ccf7e8285059dcdda5775cca1b9";
  }

  static const char* value(const KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "KBSL/FitBestPlaneSrv";
  }

  static const char* value(const KBSL::FitBestPlaneSrvResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // KBSL_SERVICE_FITBESTPLANESRV_H

