add_library(Motor-lib
    src/MotorControllerCANInterface.cpp
    src/MotorInterface.cpp
    src/MotorStateTracker.cpp
)

target_include_directories(Motor-lib PUBLIC include)

target_link_libraries(Motor-lib mbed-os-lib Common-lib)
