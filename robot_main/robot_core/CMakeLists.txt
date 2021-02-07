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

file(GLOB LIFE_DIRECTORY_LISTS include/*)
set(LIFE_INCLUDE_DIR "")
set(LIFE_SRCS "")
set(LIFE_HEADERS "")
foreach(LIFE_DIRECTORY_LIST ${LIFE_DIRECTORY_LISTS})
  list(APPEND LIFE_INCLUDE_DIR ${LIFE_DIRECTORY_LIST})
  message("ADD INCLUDE DIRECTORY : ${LIFE_DIRECTORY_LIST}")
  file(GLOB LIFE_LIB_SRC ${LIFE_DIRECTORY_LIST}/*.cpp )
  list(APPEND LIFE_SRCS ${LIFE_LIB_SRC})
  file(GLOB LIFE_LIB_HEADER ${LIFE_DIRECTORY_LIST}/*.h )
  list(APPEND LIFE_HEADERS ${LIFE_LIB_HEADER})
endforeach()

catkin_package(
  INCLUDE_DIRS include ${LIFE_INCLUDE_DIR}
  LIBRARIES robot_core
  CATKIN_DEPENDS life_msgs roscpp sensor_msgs geometry_msgs
  DEPENDS system_lib
)

include_directories(
  include
  ${LIFE_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
)

message("LIFE_LIB_SRC : ${LIFE_SRCS}")
message("LIFE_LIB_HEADER : ${LIFE_HEADERS}")
add_library(life_lib ${LIFE_SRCS} ${LIFE_HEADERS})
target_include_directories(life_lib 
PRIVATE include ${LIFE_INCLUDE_DIR}
)

add_executable(robot_core src/main.cpp)
add_dependencies(robot_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_core
   ${catkin_LIBRARIES} life_lib
)

