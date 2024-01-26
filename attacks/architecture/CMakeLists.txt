
add_executable(ptrace "ptrace.cpp" "instructions.cpp" "victim_code.s")
target_link_libraries(ptrace PUBLIC xom-static unicorn keystone m)
