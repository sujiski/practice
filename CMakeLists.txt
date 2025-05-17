cmake_minimum_required(VERSION 3.14)
project(acc_simulation)

set(CMAKE_CXX_STANDARD 17)

# vcpkg経由でインストールしたパッケージを使うための設定
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(acc_simulation ${SOURCES} main.cpp)

# ライブラリをリンク（nlohmann_json::nlohmann_json は vcpkg経由で定義される）
target_link_libraries(my_acc_sim PRIVATE nlohmann_json::nlohmann_json)