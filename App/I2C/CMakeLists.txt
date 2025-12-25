add_library(i2c_module STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/I2C.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/I2C_API.cpp
)

target_include_directories(i2c_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(i2c_module
    stm32cubemx
)