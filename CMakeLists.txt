cmake_minimum_required(VERSION 3.8.0)
project (libxom C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_library(GMP_LIBRARIES gmp PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
find_library(unicorn PATHS ${LIB_INSTALL_DIR})
find_library(keystone PATHS ${LIB_INSTALL_DIR} "/usr/local/lib")

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG "-O0 -DDEBUG_FAULT_HANDLER")
set(CMAKE_CXX_FLAGS "-O3 -fconstexpr-ops-limit=2147483648 -march=native")

# set(CMAKE_VERBOSE_MAKEFILE TRUE)
add_link_options("-znoexecstack")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxom)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modxom)

add_subdirectory("libxom")
add_subdirectory("modxom")

add_subdirectory(demos)
add_subdirectory(benchmarks)
add_subdirectory(attacks)

install(TARGETS xom DESTINATION /usr/lib)
install(FILES libxom/libxom.h DESTINATION include)
install(FILES modxom/modxom.h DESTINATION include)
install(FILES ./xom DESTINATION /usr/bin PERMISSIONS WORLD_READ WORLD_EXECUTE)