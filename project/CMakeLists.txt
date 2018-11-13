cmake_minimum_required(VERSION 3.0.0)
project(opengl_project VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(/usr/local/lib)
link_libraries(libglfw3.a)
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_executable(opengl_project App/Blend.cpp External/glad.c)
#add_executable(opengl_project App/Test.cpp External/glad.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)