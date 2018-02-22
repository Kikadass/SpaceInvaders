cmake_minimum_required(VERSION 3.8)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "-framework CoreFoundation -framework ApplicationServices")

set(OpenCV_DIR "/Users/kikepieraserra/GitHub/FinalYearProject/opencv-3.3.0/build/CMakeFiles/Export/share/OpenCV")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)



set(SOURCE_FILES main.cpp include/Entity.cpp include/Entity.h include/Player.cpp include/Player.h include/Game.cpp include/Game.h include/Enemy.cpp include/Enemy.h include/Bullet.cpp include/Bullet.h)
add_executable(SpaceInvaders ${SOURCE_FILES})

# linking
target_link_libraries( SpaceInvaders ${OpenCV_LIBS} )

