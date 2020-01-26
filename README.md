# reuleaux
=====
Google Summer of Code Project: Robot reachability and Base Placement


[Franz Reuleaux] (https://en.wikipedia.org/wiki/Franz_Reuleaux): *Franz Reuleaux (30 September 1829 -20 August 1905) was a lecturer of the Berlin Royal Technical Academy where he was later appointed as the President. He was often referred as the “father of kinematics”. After becoming a professor at the Swiss Federal Institute of Zurich, he became Rector at Königs Technischen Hochschule Berlin – Charlottenburg. Despite his involvement in German politics he became widely-known as an engineer-scientist, professor and industrial consultant, education reformer and leader of technical elite of Germany. He was also a member of Royal Swiss Acedemy of Sciences.
Reuleaux relied deeply on the concept of kinematic chain which could be abstracted in kinematic pairs- chains of elementary links. Constraints on each kinematic pairs can lead to constraints on whole machine. He is best remembered for Reuleaux triangle and the development of compact symbolic notion to describe the topology of very wide variety of mechanisms.*



Documentation about Map creation can be found at: [map_creator] (https://github.com/ros-industrial-consortium/reuleaux/tree/master/map_creator)

Documentation about Workspace Visualization can be found at: [workspace_visualization] (https://github.com/ros-industrial-consortium/reuleaux/tree/master/workspace_visualization)

Documentation about Base Placement Planner can be found at: [Base Placement Plugin] (https://github.com/ros-industrial-consortium/reuleaux/tree/master/base_placement_plugin)

Please refer to [http://wiki.ros.org/reuleaux] (http://wiki.ros.org/reuleaux) for detailed description and instructions.

Change to run melodic 
	Test





	- reuleaux/map_creator/include/map_creator/mh5_ikfast.cpp:1154:18: error: ‘isnan’ was not declared in this scope
         else if (isnan(cj4array[0]))

         Possible proble with generate ikfast file from openRave

         Solution

Repaced:
#include <math.h>
with:
#include <cmath>
and all instances of
isnan
with:
std::isnan




	-	reuleaux/map_creator/src/create_reachability_map.cpp:38:33: note: suggested alternative: ‘forward’
   std::string file = str(boost::format("%s_r%d_reachability.h5") % k.getRobotName() % resolution);


	-	reuleaux/map_creator/src/create_capability_map.cpp:36:18: note: suggested alternative: ‘forward’
       str(boost::format("%s_r%d_capability.h5") % k.getRobotName() % resolution);

    -   reuleaux/map_creator/src/create_inverse_reachability_map.cpp: In function ‘int main(int, char**)’:
/home/alfredo/ros_ws/src/reuleaux/map_creator/src/create_inverse_reachability_map.cpp:66:26: error: ‘format’ is not a member of ‘boost’
       file =  str(boost::format("%s_r%d_Inv_reachability.h5") % k.getRobotName() % res);

Solution
       	
Add #include <boost/format.hpp>


Images

![image](https://github.com/myalfred03/reuleaux/blob/melodic-test/img/1.png)
Modelo de robot MH5 Reachability index 10

![image](https://github.com/myalfred03/reuleaux/blob/melodic-test/img/2.png)
Modelo de robot IRB2600 Reachability index 37