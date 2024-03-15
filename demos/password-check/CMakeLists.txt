add_executable(password_check password_check.c password_check.s)
target_link_libraries(password_check PUBLIC xom-static gcrypt)
# target_compile_options(password_check PUBLIC "-mavx2;-msha;-mrdrnd")
