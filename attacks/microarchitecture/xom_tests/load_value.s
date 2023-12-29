.file "xom_tests/load_value.s"

.text
.globl load_magic_value
load_magic_value:
    mov 8(%ebp), %edx
load_magic_value_repeat:
    mov $0x01abcdef, %eax
    xor %eax, %eax
    clflush (%edx)
    jmp load_magic_value_repeat
