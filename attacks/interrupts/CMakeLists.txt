
add_executable(ptrace "ptrace.cpp" "victim_code.s")
target_link_libraries(ptrace PUBLIC xom-static m)
