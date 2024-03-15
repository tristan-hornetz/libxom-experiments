add_executable(dma_attack dma_attack.c)
configure_file(kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel.cl COPYONLY)
include_directories(${OpenCL_INCLUDE_DIRS})
target_link_libraries(dma_attack PUBLIC ${OpenCL_LIBRARIES} xom-static)