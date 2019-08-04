project(SDM)
cmake_minimum_required(VERSION 3.6)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# OSX only config (might work UNIX too, not tested)
# add c++11 flags
add_compile_options(-std=c++11)

include_directories("src/include" /
                    /home/jianqiang.rjq/app/opencv2411/include/opencv-2.4.11 )
aux_source_directory("src/include" SOURCES_FILE)

link_directories(/home/jianqiang.rjq/app/opencv2411/lib)


set(CMAKE_CXX_FLAGS "  -std=c++0x  -g -Wall -W   -march=core2 -O -fomit-frame-pointer -pipe -fPIC")
set(CMAKE_C_FLAGS " -std=c++0x -g -Wall -W   -march=core2 -O -fomit-frame-pointer -pipe -fPIC")


set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_gpu opencv_flann opencv_objdetect opencv_calib3d)
add_library(SDM SHARED src/include/ldmarkmodel.cpp)

TARGET_LINK_LIBRARIES(SDM ${OpenCV_LIBS})


ADD_EXECUTABLE(SDM-TEST src/test_model.cpp)
TARGET_LINK_LIBRARIES(SDM-TEST ${OpenCV_LIBS})




