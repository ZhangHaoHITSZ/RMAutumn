
find_package(OpenCV 4.0  REQUIRED)
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    "/usr/include/eigen3"
)
add_executable(one one.cpp)
target_link_libraries(one
    ${OpenCV_LIBS}
)
add_executable(two two.cpp)
target_link_libraries(two
    ${OpenCV_LIBS}
)
add_executable(trackbar trackbar.cpp)
target_link_libraries(trackbar
    ${OpenCV_LIBS}
)
add_library(kalman kalman.cpp)
add_executable(test test.cpp)
target_link_libraries(test kalman)
