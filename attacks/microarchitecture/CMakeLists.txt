include_directories("xom_tests/libcache")
include_directories("xom_tests")

add_executable(microarchitecture
        xom_tests/microarchitecture.cpp
        xom_tests/spectre/BTB.cpp
        xom_tests/spectre/PHT.c
        xom_tests/spectre/RSB.c
        #xom_tests/meltdown.c
        xom_tests/ridl.c
        xom_tests/load_value.s
        xom_tests/portsmash.c
)
target_link_libraries(microarchitecture PUBLIC xom-static gcc)

add_executable(meltdown
    xom_tests/meltdown.c
)
target_link_libraries(meltdown PUBLIC xom-static gcc)

add_executable(spectre
    xom_tests/spectre.c
    xom_tests/spectre_victim.s
)
target_link_libraries(spectre PUBLIC xom-static gcc pthread)

