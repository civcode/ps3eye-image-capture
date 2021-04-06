cmake_minimum_required(VERSION  2.9)

project(ps3eye)

set (CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)


file(GLOB ps3eye_SRC
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)


add_executable(capture src/main.cpp ${ps3eye_SRC})

target_link_libraries(capture ${OpenCV_LIBS})

