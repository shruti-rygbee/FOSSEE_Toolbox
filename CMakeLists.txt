cmake_minimum_required(VERSION 2.8)

project( ImageProcessingToolbox)

find_package( OpenCV REQUIRED )

add_executable( stdfilt stdfilt.cpp)
target_link_libraries( stdfilt ${OpenCV_LIBS} )
