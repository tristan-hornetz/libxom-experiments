add_executable(benchmark_micro
    "micro.c"
    "utils.c"
    "jumper.s"
)
target_link_libraries(benchmark_micro m xom-static xom-aes-gcm-static)
target_include_directories(benchmark_micro PUBLIC ../demos/aes-gcm/include)