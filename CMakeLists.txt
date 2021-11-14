cmake_minimum_required (VERSION 2.8) 
project (Viergewinnt)

find_package(WiringPi REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable (Viergewinnt ${SOURCES})  
target_link_libraries (Viergewinnt ${WIRINGPI_LIBRARIES})
add_definitions(-std=c++0x -L/usr/include -lwiringPi)