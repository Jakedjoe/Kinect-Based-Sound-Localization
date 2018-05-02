/* Auto-generated by genmsg_cpp for file /home/jake/kinetic_workspace/sandbox/Kinect-Based-Sound-Localization/KBSL/msg/PlaneParametersMsg.msg */
#ifndef KBSL_MESSAGE_PLANEPARAMETERSMSG_H
#define KBSL_MESSAGE_PLANEPARAMETERSMSG_H
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

#include "geometry_msgs/Point32.h"
#include "geometry_msgs/Point32.h"

namespace KBSL
{
template <class ContainerAllocator>
struct PlaneParametersMsg_ {
  typedef PlaneParametersMsg_<ContainerAllocator> Type;

  PlaneParametersMsg_()
  : n()
  , P0()
  {
  }

  PlaneParametersMsg_(const ContainerAllocator& _alloc)
  : n(_alloc)
  , P0(_alloc)
  {
  }

  typedef  ::geometry_msgs::Point32_<ContainerAllocator>  _n_type;
   ::geometry_msgs::Point32_<ContainerAllocator>  n;

  typedef  ::geometry_msgs::Point32_<ContainerAllocator>  _P0_type;
   ::geometry_msgs::Point32_<ContainerAllocator>  P0;


  typedef boost::shared_ptr< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::KBSL::PlaneParametersMsg_<ContainerAllocator>  const> ConstPtr;
}; // struct PlaneParametersMsg
typedef  ::KBSL::PlaneParametersMsg_<std::allocator<void> > PlaneParametersMsg;

typedef boost::shared_ptr< ::KBSL::PlaneParametersMsg> PlaneParametersMsgPtr;
typedef boost::shared_ptr< ::KBSL::PlaneParametersMsg const> PlaneParametersMsgConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::KBSL::PlaneParametersMsg_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::KBSL::PlaneParametersMsg_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace KBSL

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::KBSL::PlaneParametersMsg_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4fb5fd99bb835e5ad2523b4094d56e8b";
  }

  static const char* value(const  ::KBSL::PlaneParametersMsg_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x4fb5fd99bb835e5aULL;
  static const uint64_t static_value2 = 0xd2523b4094d56e8bULL;
};

template<class ContainerAllocator>
struct DataType< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "KBSL/PlaneParametersMsg";
  }

  static const char* value(const  ::KBSL::PlaneParametersMsg_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Point32 n\n\
geometry_msgs/Point32 P0\n\
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

  static const char* value(const  ::KBSL::PlaneParametersMsg_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::KBSL::PlaneParametersMsg_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::KBSL::PlaneParametersMsg_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.n);
    stream.next(m.P0);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct PlaneParametersMsg_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::KBSL::PlaneParametersMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::KBSL::PlaneParametersMsg_<ContainerAllocator> & v) 
  {
    s << indent << "n: ";
s << std::endl;
    Printer< ::geometry_msgs::Point32_<ContainerAllocator> >::stream(s, indent + "  ", v.n);
    s << indent << "P0: ";
s << std::endl;
    Printer< ::geometry_msgs::Point32_<ContainerAllocator> >::stream(s, indent + "  ", v.P0);
  }
};


} // namespace message_operations
} // namespace ros

#endif // KBSL_MESSAGE_PLANEPARAMETERSMSG_H

