cmake_minimum_required(VERSION 3.29)
project(Shop_Management_System)

set(CMAKE_CXX_STANDARD 20)

# Set the output directory for executable files to the root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(Shop_Manager
        src/main.cpp
        src/Authentication.cpp
        src/Employee.cpp
        src/Inventory.cpp
        src/ProcessOrder.cpp
        src/TransactionRecords.cpp
        src/UpdateInventory.cpp)

# Include header files directory
target_include_directories(Shop_Manager PRIVATE include)