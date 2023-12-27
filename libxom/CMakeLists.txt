add_library(xom SHARED
    "libxom.c"
    "reg_clear.s"
)
target_link_libraries(xom PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom PUBLIC "-fPIC;-mrdrnd;-mmmx;-msse2")

add_library(xom-static STATIC
    "libxom.c"
    "reg_clear.s"
)
target_link_libraries(xom-static PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom-static PUBLIC "-mrdrnd;-mmmx;-msse2")

add_library(xom-static32 STATIC
    "libxom.c"
)
target_link_libraries(xom-static32 PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
target_compile_options(xom-static32 PUBLIC -m32 -mrdrnd -mmmx -msse2)
target_link_options(xom-static32 PUBLIC -m32 -mrdrnd -mmmx -msse2)