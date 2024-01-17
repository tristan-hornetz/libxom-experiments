
add_executable(xom_demo_basic
    "basic.c"
)
target_link_libraries(xom_demo_basic xom)

add_executable(xom_demo_features
    "features.c"
)
target_link_libraries(xom_demo_features xom)
target_compile_options(xom_demo_features PUBLIC "-fPIC;-fno-omit-frame-pointer")

add_subdirectory(aes-gcm)
add_subdirectory(rsa)