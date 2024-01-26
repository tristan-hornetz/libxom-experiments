#ifndef INSTRUCTION_ENCODINGS_H
#define INSTRUCTION_ENCODINGS_H
#ifdef __cplusplus

#include <array>

static constexpr std::array<instruction, 4324> instruction_encodings = {
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "ADC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "ADC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "ADC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADCX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADDSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ADDSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ADDSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ADDSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADDSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ADDSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ADOX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "AESDEC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESDEC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "AESDEC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESDECLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESDECLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "AESDECLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESENC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESENC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "AESENC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESENCLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESENCLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "AESENCLAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESIMC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AESIMC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "AESIMC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "AND",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "AND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "AND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "AND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "AND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "AND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "AND",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ANDNPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDNPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ANDNPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDNPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ANDNPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDNPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "BLENDVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "BLENDVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "BLENDVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "BLENDVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "BLENDVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "BLENDVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "BLSI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BLSMSK",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BLSR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BSF",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "BSF",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "BSF",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "BSR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "BSR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "BSR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "BSWAP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "BSWAP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BT",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BT",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTC",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTC",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "BTS",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CALL",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        5
    },
    (instruction) {
        "CALL",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        5
    },
    (instruction) {
        "CALL",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        5
    },
    (instruction) {
        "CALL",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        5
    },
    (instruction) {
        "CALL",
        "%s",
        1,
        {parameter_type::INTEGER, },
        5
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "CALL",
        "*%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "CALL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        5
    },
    (instruction) {
        "CALL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        5
    },
    (instruction) {
        "CALL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        5
    },
    (instruction) {
        "CALL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        5
    },
    (instruction) {
        "CALL",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        5
    },
    (instruction) {
        "CBW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CDQ",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CDQE",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CLAC",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "CLC",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CLD",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CLFLUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CLFLUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CLFLUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CLFLUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CLFLUSH",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CLFLUSH",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CLFLUSHOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CLFLUSHOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CLFLUSHOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CLFLUSHOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CLFLUSHOPT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CLFLUSHOPT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CLI",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CLTS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CLWB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CLWB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CLWB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CLWB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CLWB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CLWB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMC",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CMOVA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNAE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNC",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNGE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMOVNLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "CMOVNLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMOVNLE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "CMP",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "CMP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "CMP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "CMP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "CMP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "CMP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "CMP",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "CMPS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CMPSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "CMPSQ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CMPSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMPXCHG16B",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG16B",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG16B",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG16B",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG16B",
        "%s",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "CMPXCHG16B",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "CMPXCHG8B",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG8B",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG8B",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG8B",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG8B",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "CMPXCHG8B",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "COMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "COMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "COMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "COMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "COMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "COMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CPUID",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CQO",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CVTDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPD2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPD2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTPD2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPI2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPI2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTPI2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPI2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTPI2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPI2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPS2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTPS2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTPS2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "CVTSD2SI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CVTSD2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSD2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSD2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSI2SD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSI2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSI2SS",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSI2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSI2SS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSS2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSS2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTSS2SD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTSS2SI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CVTTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTTPD2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "CVTTPS2DQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "CVTTSD2SI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CVTTSS2SI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "CWD",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "CWDE",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "DEC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "DEC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "DEC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "DEC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "DIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "DIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "DIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "DIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "DIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "DIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "DIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "DIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "DIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "DIVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "DIVPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "DIVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "DIVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "DIVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "DIVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "DIVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "EMMS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "F2XM1",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FABS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FADD",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FADDP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FBLD",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FBLD",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FBLD",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FBLD",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FBLD",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FBLD",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FBSTP",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FBSTP",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FBSTP",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FBSTP",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FBSTP",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FBSTP",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FCHS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCLEX",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "FCOM",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCOMI",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCOMIP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCOMP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCOMPP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FCOS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FDECSTP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FDIV",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FDIVP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FDIVR",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FDIVRP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FINCSTP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FINIT",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "FLD1",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FLDCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FLDCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FLDCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FLDCW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FLDCW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FLDENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FLDENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FLDENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FLDENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FLDENV",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FLDENV",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FLDL2E",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDL2T",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDLG2",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDLN2",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDPI",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FLDZ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FMUL",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FMULP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FNCLEX",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FNINIT",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FNOP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FNSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSAVE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSAVE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTCW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTCW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTENV",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTENV",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        2
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTSW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FNSTSW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FPATAN",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FPREM",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FPREM1",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FPTAN",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FRNDINT",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FRSTOR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "FRSTOR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "FSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSAVE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSAVE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSCALE",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSIN",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSINCOS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSQRT",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTCW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTCW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTCW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTENV",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTENV",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTENV",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSTSW",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTSW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FSTSW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FSUB",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSUBP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSUBR",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FSUBRP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FTST",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FUCOM",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FUCOMI",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FUCOMIP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FUCOMP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FUCOMPP",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FWAIT",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "FXAM",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FXCH",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FXRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FXRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FXRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FXRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FXRSTOR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FXRSTOR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FXSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FXSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FXSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FXSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FXSAVE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "FXSAVE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "FXTRACT",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FYL2X",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "FYL2XP1",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "HADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "HADDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "HADDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HLT",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "HSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "HSUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "HSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "HSUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "IDIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "IDIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "IDIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "IDIV",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "IDIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "IDIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "IDIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "IDIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "IDIV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "IMUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "IMUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "IMUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "IMUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "IMUL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "IMUL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "IMUL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "INC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "INC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "INC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "INC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "INS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "INSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "INSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "INT1",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "INT3",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "INTO",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "INVD",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "INVLPG",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "INVLPG",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "INVLPG",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "INVLPG",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "INVLPG",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "INVLPG",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "IRET",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "IRETQ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "JMP",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        5
    },
    (instruction) {
        "JMP",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        5
    },
    (instruction) {
        "JMP",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        5
    },
    (instruction) {
        "JMP",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JMP",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "JMP",
        "*%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "JMP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        5
    },
    (instruction) {
        "JMP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        5
    },
    (instruction) {
        "JMP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        5
    },
    (instruction) {
        "JMP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JMP",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JA",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JA",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JA",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JA",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JA",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JA",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JAE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JAE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JBE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JBE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JC",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JC",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JC",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JC",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JC",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JC",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JECXZ",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        3
    },
    (instruction) {
        "JECXZ",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        3
    },
    (instruction) {
        "JECXZ",
        "%s",
        1,
        {parameter_type::INTEGER, },
        3
    },
    (instruction) {
        "JECXZ",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        3
    },
    (instruction) {
        "JECXZ",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        3
    },
    (instruction) {
        "JECXZ",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        3
    },
    (instruction) {
        "JRCXZ",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "JRCXZ",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JRCXZ",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JRCXZ",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "JRCXZ",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JRCXZ",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JG",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JG",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JG",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JG",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JG",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JG",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JGE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JGE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JL",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JL",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JL",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JL",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JL",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JL",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JLE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JLE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNA",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNA",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNAE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNAE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNBE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNBE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNC",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNC",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNG",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNG",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNGE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNGE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNL",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNL",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNLE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "JNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "JNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "JNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "JNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "JNLE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "KMOVW",
        "%s, %s",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        5
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "(%s), %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "KMOVW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "KMOVW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "KMOVW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "KMOVW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "KMOVW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_BITMASK, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "LAHF",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "LAR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LAR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LAR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LDDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "LDDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "LDDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "LDMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LDMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LDMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LDMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LDMXCSR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LDMXCSR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LEA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "LEA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "LEA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LEAVE",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "LFENCE",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "LFS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LFS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LFS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LGDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LGDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LGS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LGS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LGS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LIDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LIDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LLDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LLDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LMSW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LMSW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LODS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "LODS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "LODS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LODSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "LODSB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "LODSB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "LODSQ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "LODSQ",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "LODSQ",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LODSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "LODSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "LODSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LOOP",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOP",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOP",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LOOP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOP",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LOOPE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOPE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOPE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LOOPE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOPE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOPE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LOOPNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOPNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOPNE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LOOPNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        2
    },
    (instruction) {
        "LOOPNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        2
    },
    (instruction) {
        "LOOPNE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        2
    },
    (instruction) {
        "LSL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LSL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LSL",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "LSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "LSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LTR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "LTR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "LZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "LZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "LZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        6
    },
    (instruction) {
        "MAXPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MAXPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MAXPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MAXSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MAXSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MFENCE",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "MINPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MINPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MINPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MINSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MINSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MONITOR",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOV",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOV",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVAPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVAPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVAPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVAPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVAPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVAPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVAPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVAPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVAPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVAPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVAPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVAPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVAPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVAPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVAPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVAPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVAPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVAPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "MOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "MOVBE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        6
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        6
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        5
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        9
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        10
    },
    (instruction) {
        "MOVBE",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        9
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVDDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVDDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQA",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVDQA",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVDQA",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVDQA",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVDQA",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVDQA",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVDQU",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVDQU",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVDQU",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVDQU",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVDQU",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVDQU",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVDQU",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVHPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVHPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVHPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVHPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVHPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVHPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVHPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVHPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVHPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVHPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVHPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVHPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVLPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVLPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVLPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVLPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVLPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVLPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVLPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVLPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVLPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVLPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVLPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVLPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVNTDQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTDQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTDQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTDQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTDQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTDQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVNTDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "MOVNTDQA",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVNTI",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVNTPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVNTPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVNTPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVNTPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVNTPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVNTPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVNTPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVNTPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVQ",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "MOVSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "MOVSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "MOVSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "MOVSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "MOVSD",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "MOVSD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVSD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVSD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVSD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVSD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVSD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVSHDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSHDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVSHDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSLDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSLDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVSLDUP",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSQ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "MOVSS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVSS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVSS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVSS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVSS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVSS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "MOVSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "MOVSX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "MOVSX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "MOVUPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVUPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVUPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVUPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVUPD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVUPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVUPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MOVUPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "MOVUPD",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "MOVUPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVUPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVUPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVUPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVUPS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVUPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVUPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MOVUPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "MOVUPS",
        "%s, (%s)",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "MOVZX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "MOVZX",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "MUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "MUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "MUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "MUL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "MULPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MULPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MULPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "MULSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MULSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MULSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "MULSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "MWAIT",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "NEG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "NEG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "NEG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "NEG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "NOP",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "NOP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "NOP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "NOT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "NOT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "NOT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "NOT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "OR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "OR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "OR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "OR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "OR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "OR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "OR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "ORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "ORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "OUTS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "OUTSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "OUTSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "PABSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PABSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PABSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PABSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PABSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PABSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PABSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PABSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PABSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKSSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PACKSSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKSSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PACKSSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PACKSSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKSSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PACKUSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKUSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PACKUSDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKUSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PACKUSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PACKUSWB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PAND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PANDN",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PANDN",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PANDN",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAUSE",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "PAVGB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAVGB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PAVGB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAVGW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PAVGW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PAVGW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PBLENDVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PBLENDVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PBLENDVB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPEQB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPEQD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPEQD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPEQQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PCMPEQQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPEQW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPEQW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPGTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPGTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPGTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PCMPGTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPGTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PCMPGTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PCMPGTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PHADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHADDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHADDSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHADDW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHMINPOSUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHMINPOSUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHMINPOSUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PHSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PHSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMADDUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMADDUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMADDUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMADDWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMADDWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMADDWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMAXSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMAXSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMAXSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMAXSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMAXUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMAXUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMAXUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMAXUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMAXUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMAXUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMINSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMINSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMINSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMINUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMINUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMINUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMINUD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMINUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMINUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMULDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULHRSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULHRSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMULHRSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULHUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULHUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULHUW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULHW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULHW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULHW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PMULLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULUDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PMULUDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PMULUDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        2
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "POP",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "POP",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "POPCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "POPCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "POPCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        6
    },
    (instruction) {
        "POPF",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "POPFQ",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "POR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "POR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "POR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PREFETCHW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "PREFETCHW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "PREFETCHW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "PREFETCHW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "PREFETCHW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "PREFETCHW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "PSADBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSADBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSADBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSHUFB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSHUFB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PSHUFB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PSIGNB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PSIGND",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGNW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSIGNW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PSIGNW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSLLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSLLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSLLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSLLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSLLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSLLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSLLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSLLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSLLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRAD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRAD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSRAD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRAW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRAW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSRAW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSRLD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSRLQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSRLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSRLW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBUSB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBUSW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PSUBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PTEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PTEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "PTEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKHBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKHBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKHDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKHQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKHWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKHWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKLBW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKLDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKLQDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUNPCKLWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PUNPCKLWD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        2
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "PUSH",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "PUSH",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "PUSHF",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "PUSHFQ",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "PXOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "PXOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "PXOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RCL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "RCL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "RCL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "RCL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "RCPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "RCPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RCPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "RCPSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RCPSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "RCPSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RCR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "RCR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "RCR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "RCR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "RDFSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        5
    },
    (instruction) {
        "RDFSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "RDGSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        5
    },
    (instruction) {
        "RDGSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "RDMSR",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "RDPKRU",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "RDPMC",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "RDRAND",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "RDRAND",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "RDRAND",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "RDSEED",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "RDSEED",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "RDSEED",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "RDTSC",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "RDTSCP",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "RET",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "ROL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "ROL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "ROL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "ROL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ROR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "ROR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "ROR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "ROR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "RSM",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "RSQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "RSQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RSQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "RSQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "RSQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "RSQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SAHF",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "SAL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SAL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SAL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SAL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SAR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SAR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SAR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SAR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SBB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "SBB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SBB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SCAS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "SCAS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "SCAS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "SCASB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "SCASB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "SCASB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SCASW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "SCASW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "SCASW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETA",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETA",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETAE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETAE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETBE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETBE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETC",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETC",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETG",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETG",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETGE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETGE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETL",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETL",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETLE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETLE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNA",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNA",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNAE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNAE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNBE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNBE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNC",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNC",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNG",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNG",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNGE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNGE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNL",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNL",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNLE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SETNLE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SFENCE",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "SGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SGDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SGDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SGDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SHA1MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA1MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA1MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA1MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA1MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA1MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA1NEXTE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA1NEXTE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA1NEXTE",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA256MSG1",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA256MSG2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256RNDS2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHA256RNDS2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SHA256RNDS2",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SHL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SHL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SHL",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHLD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SHR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SHR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SHR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "SHRD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "SIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SIDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SIDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SIDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SLDT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SLDT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SMSW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SMSW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SQRTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SQRTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SQRTSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SQRTSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SQRTSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "STAC",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "STC",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "STD",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "STI",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "STMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "STMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "STMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "STMXCSR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "STMXCSR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "STMXCSR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "STOS",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "STOS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "STOS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "STOSB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "STOSB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "STOSB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "STOSQ",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "STOSQ",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "STOSQ",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "STOSW",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "STOSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        2
    },
    (instruction) {
        "STOSW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        4
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        3
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "STR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "STR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SUB",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "SUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "SUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "SUB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "SUB",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "SUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SUBPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "SUBSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SUBSD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SUBSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "SUBSS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "SWAPGS",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "SYSCALL",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "SYSENTER",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "SYSEXIT",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "SYSRET",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "TEST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "TEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "TEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "TEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "TEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "TEST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "TEST",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "TZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "TZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        5
    },
    (instruction) {
        "TZCNT",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        6
    },
    (instruction) {
        "UCOMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UCOMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "UCOMISD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UCOMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "UCOMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UCOMISS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "UNPCKHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "UNPCKHPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "UNPCKHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKHPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "UNPCKLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "UNPCKLPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "UNPCKLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "UNPCKLPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VCOMPRESSPD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VCOMPRESSPS",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VCVTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        7
    },
    (instruction) {
        "VCVTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "%s, %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPH2PS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VCVTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTSD2USI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        6
    },
    (instruction) {
        "VCVTSS2USI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        6
    },
    (instruction) {
        "VCVTTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        7
    },
    (instruction) {
        "VCVTTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPD2UDQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VCVTTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTPS2UDQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTTSD2USI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        6
    },
    (instruction) {
        "VCVTTSS2USI",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        6
    },
    (instruction) {
        "VCVTUDQ2PD",
        "%s, %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VCVTUDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VCVTUDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VCVTUDQ2PS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "VERR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "VERR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "VERW",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "VERW",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "VEXPANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VEXPANDPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VEXPANDPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VEXPANDPS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VGETEXPPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VGETEXPPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VGETEXPPS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQA32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQA32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQA32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQA32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQA32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VMOVDQA32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQA32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQA64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQA64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VMOVDQA64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA64",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA64",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQA64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQU32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQU32",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VMOVDQU32",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU32",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU32",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQU32",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQU64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQU64",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VMOVDQU64",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU64",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU64",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VMOVDQU64",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPBROADCAST",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCAST",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPBROADCAST",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCAST",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCAST",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTB",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTB",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTW",
        "%s, %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPBROADCASTW",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPCOMPRESSD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPCOMPRESSQ",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPCONFLICTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPCONFLICTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPCONFLICTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPCONFLICTQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPEXPANDD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPEXPANDQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPEXPANDQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPLZCNTD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VPLZCNTQ",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTQ",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPLZCNTQ",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VPMOVDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSDB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSDW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQB",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQD",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, %s",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE8, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE16, },
        10
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE32, },
        11
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::IMMEDIATE64, },
        11
    },
    (instruction) {
        "VPMOVUSQW",
        "%s, (%s)",
        2,
        {parameter_type::AVX512_REGISTER, parameter_type::INTEGER, },
        10
    },
    (instruction) {
        "VPTESTMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        7
    },
    (instruction) {
        "VPTESTMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMD",
        "(%s), %s, %s",
        3,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMD",
        "(%s), %s, %s",
        3,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        7
    },
    (instruction) {
        "VPTESTMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        7
    },
    (instruction) {
        "VPTESTNMD",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMD",
        "(%s), %s, %s",
        3,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMD",
        "(%s), %s, %s",
        3,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        7
    },
    (instruction) {
        "VPTESTNMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VPTESTNMQ",
        "(%s), %s, %s",
        3,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, parameter_type::AVX512_BITMASK, },
        6
    },
    (instruction) {
        "VRCP14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VRCP14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VRCP14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRCP14PS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VRSQRT14PD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PD",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        7
    },
    (instruction) {
        "VRSQRT14PS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VRSQRT14PS",
        "(%s), %s",
        2,
        {parameter_type::AVX_REGISTER, parameter_type::AVX512_REGISTER, },
        6
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPD",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        6
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        6
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VTESTPS",
        "(%s), %s",
        2,
        {parameter_type::SSE_REGISTER, parameter_type::AVX_REGISTER, },
        5
    },
    (instruction) {
        "VZEROALL",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "VZEROUPPER",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "WAIT",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "WBINVD",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "WRFSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        5
    },
    (instruction) {
        "WRFSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "WRGSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        5
    },
    (instruction) {
        "WRGSBASE",
        "%s",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "WRMSR",
        "",
        0,
        {},
        2
    },
    (instruction) {
        "WRPKRU",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "XACQUIRE",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        5
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        4
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        9
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        9
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XBEGIN",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XBEGIN",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XBEGIN",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "XBEGIN",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        6
    },
    (instruction) {
        "XBEGIN",
        "%s",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XBEGIN",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XBEGIN",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XBEGIN",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        6
    },
    (instruction) {
        "XBEGIN",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        6
    },
    (instruction) {
        "XBEGIN",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XCHG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "XCHG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "XCHG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "XCHG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "XCHG",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XCHG",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XEND",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "XGETBV",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "XLAT",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "XLAT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        1
    },
    (instruction) {
        "XLAT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        1
    },
    (instruction) {
        "XLAT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        1
    },
    (instruction) {
        "XLAT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        1
    },
    (instruction) {
        "XLAT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        1
    },
    (instruction) {
        "XLAT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        1
    },
    (instruction) {
        "XLATB",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "XLATB",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        1
    },
    (instruction) {
        "XLATB",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        1
    },
    (instruction) {
        "XLATB",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        1
    },
    (instruction) {
        "XLATB",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        1
    },
    (instruction) {
        "XLATB",
        "%s",
        1,
        {parameter_type::INTEGER, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        1
    },
    (instruction) {
        "XLATB",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        1
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XOR",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "XOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "XOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "XOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "XOR",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "XOR",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "XORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "XORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        5
    },
    (instruction) {
        "XORPD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "XORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        4
    },
    (instruction) {
        "XORPS",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XRELEASE",
        "",
        0,
        {},
        1
    },
    (instruction) {
        "XRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XRSTOR",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XRSTOR",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XRSTOR",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XRSTORS",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XRSTORS",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XRSTORS",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XRSTORS",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XRSTORS",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XRSTORS",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVE",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVE",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVE",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVEC",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVEC",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVEC",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVEC",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVEC",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVEC",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVEOPT",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVEOPT",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVEOPT",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVES",
        "%s",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVES",
        "%s",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVES",
        "%s",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVES",
        "%s",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVES",
        "%s",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_QWORD, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "XSAVES",
        "(%s)",
        1,
        {parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "XSETBV",
        "",
        0,
        {},
        3
    },
    (instruction) {
        "XTEST",
        "",
        0,
        {},
        3
    },
};

#endif
#endif
