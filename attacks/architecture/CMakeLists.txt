
add_executable(ptrace "ptrace.c" "victim_code.s")
target_link_libraries(ptrace PUBLIC xom-static)