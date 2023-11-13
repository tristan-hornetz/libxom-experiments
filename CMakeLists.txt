cmake_minimum_required(VERSION 3.8.0)
project (libxom)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory("modxom")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxom)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modxom)
add_library(xom SHARED 
    "libxom/libxom.c"
)
target_link_libraries(xom PRIVATE Threads::Threads)

add_executable(xom_demo
    "demo.c"
)
target_link_libraries(xom_demo xom)
target_compile_options(xom_demo PUBLIC "-fPIC;-pthread")


install(TARGETS xom DESTINATION /usr/lib)
install(FILES libxom/libxom.h DESTINATION include)