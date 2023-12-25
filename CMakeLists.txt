cmake_minimum_required(VERSION 3.8.0)
project (libxom C ASM)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_C_FLAGS_RELEASE "-O3")

# set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory("modxom")

add_link_options("-znoexecstack")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxom)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modxom)
add_library(xom SHARED 
    "libxom/libxom.c"
    "libxom/reg_clear.s"
)
target_link_libraries(xom PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom PUBLIC "-fPIC;-mrdrnd;-mmmx;-msse2")

add_library(xom-static STATIC
    "libxom/libxom.c"
    "libxom/reg_clear.s"
)
target_link_libraries(xom-static PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom-static PUBLIC "-mrdrnd;-mmmx;-msse2")

add_subdirectory(demos)

install(TARGETS xom DESTINATION /usr/lib)
install(FILES libxom/libxom.h DESTINATION include)
install(FILES ./xom DESTINATION /usr/bin PERMISSIONS WORLD_READ WORLD_EXECUTE)