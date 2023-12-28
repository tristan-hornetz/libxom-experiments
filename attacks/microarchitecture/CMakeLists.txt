include_directories("xom_tests/libcache")
include_directories("xom_tests")

add_executable(microarchitecture
        xom_tests/microarchitecture.cpp
        xom_tests/spectre/BTB.cpp
        xom_tests/spectre/PHT.c
        xom_tests/spectre/RSB.c
        xom_tests/meltdown.c
)
target_link_directories(microarchitecture PUBLIC "/usr/lib32")
target_link_libraries(microarchitecture PUBLIC xom-static32 gcc)
target_link_options(microarchitecture PUBLIC -m32)
target_compile_options(microarchitecture PUBLIC -m32 -Os)

