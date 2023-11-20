
add_executable(xom_demo_basic
    "basic.c"
)
target_link_libraries(xom_demo_basic xom)
target_compile_options(xom_demo_basic PUBLIC "-fPIC;-fno-omit-frame-pointer")

add_subdirectory(aes-gcm)
