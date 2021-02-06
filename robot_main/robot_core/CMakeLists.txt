cmake_minimum_required(VERSION 3.0.2)
project(robot_core)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  life_msgs
  roscpp
  sensor_msgs
  geometry_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES robot_core
  CATKIN_DEPENDS life_msgs roscpp sensor_msgs geometry_msgs
  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB LIFE_LIB_SRC
     "include/*.cpp"
)
add_library(life_lib ${LIFE_LIB_SRC})
target_include_directories(life_lib 
PRIVATE include
)

add_executable(robot_core src/main.cpp)
add_dependencies(robot_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_core
   ${catkin_LIBRARIES} life_lib
)

