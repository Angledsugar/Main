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
set(MY_HEADER include/robot_core.h include/core.h)

add_library(mylib include/robot_core.cpp include/core.cpp ${MY_HEADER})

add_executable(robot_core src/main.cpp ${MY_HEADER})
add_dependencies(robot_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_core
   ${catkin_LIBRARIES} mylib -lwiringPi -lrt -lpthread
)
