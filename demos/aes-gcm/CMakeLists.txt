set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")

add_library(xom-aes-gcm SHARED
        src/gcm.c
        src/gfmul.s
        src/aes-init.c
)
target_include_directories(xom-aes-gcm PUBLIC "include")
target_compile_options(xom-aes-gcm PUBLIC -msse -maes -mrdrnd -O3)

add_library(xom-aes-gcm-static STATIC
        src/gcm.c
        src/gfmul.s
        src/aes-init.c
)
target_include_directories(xom-aes-gcm-static PUBLIC "include")
target_compile_options(xom-aes-gcm-static PUBLIC -msse -maes -mrdrnd -O3)

add_executable(aes-gcm aes-gcm-tool.c)
target_link_libraries(aes-gcm xom-aes-gcm-static xom-static)

add_executable(dump-aes-fun src/dump-aes-fun.c src/aes.s)
target_include_directories(dump-aes-fun PUBLIC "include")
