add_executable(benchmarks
    "micro.c"
    "allocation.c"
    "utils.c"
    "jumper.s"
    "benchmarks-main.c"
)
target_link_libraries(benchmarks m xom-static xom-aes-gcm-static)
target_include_directories(benchmarks PUBLIC ../demos/aes-gcm/include)