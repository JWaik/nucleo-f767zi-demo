# Collect DSDL-generated C sources
file(GLOB_RECURSE DSDL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dsdlc_generated/src/*.c
)

add_library(dronecan_module STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DroneCAN.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DroneCANAPI.cpp

    # DSDL auto-generated encode/decode functions
    ${DSDL_SOURCES}

    # STM32 CAN driver (provides canardSTM32Init/Transmit/Receive)
    ${CMAKE_SOURCE_DIR}/modules/DroneCAN/libcanard/drivers/stm32/canard_stm32.c
)

target_include_directories(dronecan_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dsdlc_generated/include
    ${CMAKE_SOURCE_DIR}/modules/DroneCAN/libcanard
    ${CMAKE_SOURCE_DIR}/modules/DroneCAN/libcanard/drivers/stm32
)

target_link_libraries(dronecan_module
    canard_tgt
    stm32cubemx
)

target_compile_definitions(dronecan_module PRIVATE
    DRONECAN_CXX_WRAPPERS
)
