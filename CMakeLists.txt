cmake_minimum_required(VERSION 3.10)

project(vehicle_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(sim
    main.cpp
    domain/model/Vehicle.cpp
    domain/model/Environment.cpp
    domain/service/Controller.cpp
    usecase/RunSimulation.cpp
    usecase/SimulationStep.cpp
    infrastructure/Logger.cpp
)

target_include_directories(sim PRIVATE
    ${PROJECT_SOURCE_DIR}
)