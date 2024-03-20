
add_executable(hmac_sha256 hmac_sha256.c hmac_sha256.s)
target_link_libraries(hmac_sha256 PUBLIC xom-static)
target_compile_options(hmac_sha256 PUBLIC "-mavx2;-msha;-mrdrnd")

add_executable(hmac_noxom hmac_sha256_noxom.c hmac_sha256.s)
target_compile_options(hmac_noxom  PUBLIC "-mavx2;-msha;-mrdrnd")
