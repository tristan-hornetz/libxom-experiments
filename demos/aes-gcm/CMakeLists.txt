add_link_options("-znoexecstack")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")

add_library(xom-aes-gcm SHARED
        src/gcm.c
        src/aes.s
        src/gfmul.s
)
target_include_directories(xom-aes-gcm PUBLIC "include")
target_compile_options(xom-aes-gcm PUBLIC -msse -maes -mrdrnd -O3)

add_library(xom-aes-gcm-static STATIC
        src/gcm.c
        src/aes.s
        src/gfmul.s
)
target_include_directories(xom-aes-gcm-static PUBLIC "include")
target_compile_options(xom-aes-gcm-static PUBLIC -msse -maes -mrdrnd -O3)

add_executable(aes-gcm aes-gcm-tool.c)
target_link_libraries(aes-gcm xom-aes-gcm-static xom-static)

