
add_executable(demo-rsa "rsa-main.c")
target_link_libraries(demo-rsa PRIVATE OpenSSL::SSL gmp)
