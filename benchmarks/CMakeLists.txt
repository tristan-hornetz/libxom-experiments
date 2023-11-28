add_executable(benchmark_micro
    "micro.c"
    "utils.c"
)
target_link_libraries(benchmark_micro xom-static)
target_compile_options(benchmark_micro PUBLIC "-lrt -lm")
target_link_libraries(benchmark_micro m)