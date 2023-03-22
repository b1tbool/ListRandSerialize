cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(serialize VERSION 1.0.0)

file(GLOB_RECURSE Source CONFIGURE_DEPENDS "src/*.h" "src/*.hpp" "src/*.cpp")
add_executable(serialize ${Source})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})