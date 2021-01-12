cmake_minimum_required(VERSION 3.0.2)
project(robot_core)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  life_msgs
  roscpp
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES robot_core
  CATKIN_DEPENDS life_msgs roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robot_core src/main.cpp)
add_dependencies(robot_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_core
   ${catkin_LIBRARIES}
)
