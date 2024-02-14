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
)
target_link_libraries(port_contention PUBLIC xom-static xom-aes-gcm-static)
target_include_directories(port_contention PUBLIC ../demos/aes-gcm/include)
