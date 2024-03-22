add_executable(benchmarks
    "micro.c"
    "allocation.c"
    "utils.c"
    "jumper.s"
    "benchmarks-main.c"
)
target_link_libraries(benchmarks m xom-static xom-aes-gcm-static)
target_include_directories(benchmarks PUBLIC ../demos/aes-gcm/include)

add_executable(enc_bench
    "encryption_benchmarks.c"
    "../demos/hmac/hmac_sha256.s"
    "../demos/aes-gcm/src/aes-vaes.s"
)
target_link_libraries(enc_bench xom-static gcrypt)
target_include_directories(enc_bench PUBLIC ../demos/aes-gcm/include)