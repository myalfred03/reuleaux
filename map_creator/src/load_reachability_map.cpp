#include <ros/ros.h>
#include "map_creator/WorkSpace.h"
#include <map_creator/hdf5_dataset.h>
#include <ros/package.h>
#include "std_msgs/String.h"

class loadReach {
public:
 loadReach();
 map_creator::WorkSpace datahdf5(std::string& map);
 void chatterCallback(const std_msgs::String::ConstPtr& msg);


private:
 ros::NodeHandle n;
 ros::Publisher workspace_pub;
 ros::Subscriber workspace_sub;
 map_creator::WorkSpace ws;




};

loadReach::loadReach(){

  // TODO: It can be published as a latched topic. So the whole message will be published just once and stay on the
  // topic
   workspace_pub = n.advertise< map_creator::WorkSpace >("reachability_map", 1);
  // bool latchOn = 1;
  // ros::Publisher workspace_pub = n.advertise<map_creator::WorkSpace>("reachability_map", 1, latchOn);
   workspace_sub = n.subscribe("/my_lab_uni/map_reuleaux",10,&loadReach::chatterCallback,this);

//   std::string filemap;

//   filemap = ros::package::getPath("map_creator") + "/maps/fanuc_r1000ia80f.h5";
////   map_creator::WorkSpace ws;
//   ws = datahdf5(filemap);
//       while (ros::ok())
//       {
//         ros::spinOnce();

//       }

}

void loadReach::chatterCallback(const std_msgs::String::ConstPtr& msg)
 { std::string filemap;

   ROS_INFO("I heard: [%s]", msg->data.c_str());
   filemap = msg->data;
   std::cout << filemap <<std::endl;
   filemap =msg->data.c_str();

    ws = datahdf5(filemap);
    ros::Rate loop_rate(2);
     while (ros::ok())
     {
       ros::spinOnce();
       workspace_pub.publish(ws);
       loop_rate.sleep();
     }
//    workspace_pub.publish(ws);

 }

map_creator::WorkSpace loadReach::datahdf5(std::string& map){

  hdf5_dataset::Hdf5Dataset h5(map);
  h5.open();

  MultiMapPtr pose_col_filter;
  MapVecDoublePtr sphere_col;
  float res;
  h5.loadMapsFromDataset(pose_col_filter, sphere_col, res);

  // Creating messages
  map_creator::WorkSpace ws;
  ws.header.stamp = ros::Time::now();
  ws.header.frame_id = "/my_lab_world/base_link";
  ws.resolution = res;

  for (MapVecDoublePtr::iterator it = sphere_col.begin(); it != sphere_col.end(); ++it)
  {
     map_creator::WsSphere wss;
     wss.point.x = (*it->first)[0];
     wss.point.y = (*it->first)[1];
     wss.point.z = (*it->first)[2];
     wss.ri = it->second;

     for (MultiMapPtr::iterator it1 = pose_col_filter.lower_bound(it->first); it1 != pose_col_filter.upper_bound(it->first); ++it1)
     {
        geometry_msgs::Pose pp;
        pp.position.x = it1->second->at(0);
        pp.position.y = it1->second->at(1);
        pp.position.z = it1->second->at(2);
        pp.orientation.x = it1->second->at(3);
        pp.orientation.y = it1->second->at(4);
        pp.orientation.z = it1->second->at(5);
        pp.orientation.w = it1->second->at(6);
        wss.poses.push_back(pp);
      }
      ws.WsSpheres.push_back(wss);
    }
      return ws;
}

int main(int argc, char **argv)
{
//  if (argc < 2)
//  {
//    ROS_ERROR_STREAM("Please provide the name of the reachability map. If you have not created it yet, Please create "
//                     "the map by running the create reachability map launch file in map_creator");
//    return 1;
//  }
//  else
//  {
    ros::init(argc, argv, "workspace");
//    ros::Rate loop_rate(10);
    int count = 0;
//    while (ros::ok())
//    {
//      loadReach loadReachOB;

//      ros::spinOnce();
////      sleep(5);
////      ++count;
//    }
//  }
    loadReach loadReachOB;
    ros::spin();


  return 0;
}