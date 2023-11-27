cmake_minimum_required(VERSION 3.8.0)
project (libxom C ASM)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_C_FLAGS_RELEASE "-O3")

add_subdirectory("modxom")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxom)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modxom)
add_library(xom SHARED 
    "libxom/libxom.c"
)
target_link_libraries(xom PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom PUBLIC "-fPIC;-mrdrnd")

add_library(xom-static STATIC
    "libxom/libxom.c"
)
target_link_libraries(xom-static PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom-static PUBLIC "-mrdrnd")

add_subdirectory(demos)

install(TARGETS xom DESTINATION /usr/lib)
install(FILES libxom/libxom.h DESTINATION include)
install(FILES ./xom DESTINATION /usr/bin PERMISSIONS WORLD_READ WORLD_EXECUTE)