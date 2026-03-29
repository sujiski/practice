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

# GoogleTest取得
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# テスト実行ファイル
add_executable(sim_test
    tests/SimulationStepTest.cpp
    domain/model/Vehicle.cpp
    domain/model/Environment.cpp
    domain/service/Controller.cpp
    infrastructure/Logger.cpp
    usecase/SimulationStep.cpp
)

target_include_directories(sim_test PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(sim_test gtest_main)

include(GoogleTest)
gtest_discover_tests(sim_test)