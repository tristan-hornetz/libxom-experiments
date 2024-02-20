include_directories("xom_tests/libcache")
include_directories("xom_tests")

add_executable(meltdown
    meltdown.c
)
target_link_libraries(meltdown PUBLIC xom-static gcc)

add_executable(spectre
    spectre.c
        spectre_asm.s
)
target_link_libraries(spectre PUBLIC xom-static)

add_executable(port_contention
    port_contention.c
    port_profile.s
    ../../demos/aes-gcm/src/aes.s
    crypto/openssl/aesni_ctr32_openssl.s
    crypto/openssl/chacha20_openssl.s
    crypto/openssl/cmll-x86_64.s
    crypto/openssl/aria_openssl.c
    crypto/openssl/camellia_openssl.c
    crypto/linux/aesni_linux.S
    crypto/linux/camellia_linux.c
    crypto/linux/camellia_linux.S
    crypto/linux/chcha_linux.S
    crypto/linux/chacha_linux.c
    crypto/linux/aria_linux.c
)
target_compile_options(port_contention PUBLIC "-O3")
target_compile_options(port_contention PUBLIC "-msse3")
target_link_libraries(port_contention PUBLIC xom-static xom-aes-gcm-static)
target_include_directories(port_contention PUBLIC ../demos/aes-gcm/include)
