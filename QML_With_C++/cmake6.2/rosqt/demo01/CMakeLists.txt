cmake_minimum_required(VERSION 3.16)

project(ros VERSION 1.0)



add_executable(${PROJECT_NAME} main.cpp)


find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE rclcpp::rclcpp)

