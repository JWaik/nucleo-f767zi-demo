
add_library(dronecan_module STATIC
    DroneCAN.cpp
)

target_include_directories(dronecan_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/dsdlc_generated/include
)

target_link_libraries(dronecan_module
    canard_tgt
)
