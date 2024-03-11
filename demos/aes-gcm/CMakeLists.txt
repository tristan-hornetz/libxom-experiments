add_library(xom-aes-gcm SHARED
        src/aes.s
        src/gcm.c
        src/gfmul.s
        src/aes-init.c
)
target_include_directories(xom-aes-gcm PUBLIC "include")
target_compile_options(xom-aes-gcm PUBLIC -msse -maes -mrdrnd -O3)

add_library(xom-aes-gcm-static STATIC
        src/aes.s
        src/gcm.c
        src/gfmul.s
        src/aes-init.c
)
target_include_directories(xom-aes-gcm-static PUBLIC "include")
target_compile_options(xom-aes-gcm-static PUBLIC -msse -maes -mrdrnd -O3)

add_executable(aes-gcm aes-gcm-tool.c)
target_link_libraries(aes-gcm xom-aes-gcm-static xom-static)

