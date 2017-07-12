cmake_minimum_required(VERSION 3.7)
#project name
project(Projector4500_Configurator)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()
#head file path
INCLUDE_DIRECTORIES(
        "LC4500API"
        "/usr/include/libusb-1.0"
        ${OPENGL_INCLUE_DIRS}
        ./
)
set(LC4500API_INCLUDE_PATH ./LC4500API)
add_executable(Projector4500_Configurator main.cpp
        ProjectorLC4500.cpp
        ProjectorOpenGL.cpp
        OpenGLContext.Unix.cpp
        ${LC4500API_INCLUDE_PATH}/hid.Libusb.c
        ${LC4500API_INCLUDE_PATH}/API.cpp
        ${LC4500API_INCLUDE_PATH}/usb.cpp)
TARGET_LINK_LIBRARIES(Projector4500_Configurator
        -lusb-1.0
        -lpthread
        -lXxf86vm
        -lX11
        ${OpenCV_LIBS}
        ${OPENGL_LIBRARIES})