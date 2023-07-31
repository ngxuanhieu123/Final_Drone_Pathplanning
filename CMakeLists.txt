cmake_minimum_required(VERSION 3.16.3)

project(Path_planning_project VERSION 1.0.0)

find_package(PahoMqttCpp REQUIRED)

include_directories(${RAPIDJSON_INCLUDE_DIRS})

include_directories("../rapidjson/include/")

add_subdirectory(algorithm_library)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC algorithm PahoMqttCpp::paho-mqttpp3)