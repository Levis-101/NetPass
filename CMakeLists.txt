cmake_minimum_required(VERSION 3.10)
project(NetPass)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary packages
find_package(Threads REQUIRED)

# Include directories
include_directories(include)

# Add your source files (Make sure these files exist in your src folder!)
add_executable(NetPass 
    src/main.cpp 
    src/firewall.cpp
    src/scheduler.cpp
    src/database.cpp
)

# Link libraries (Threads is used for the Session Reaper)
target_link_libraries(NetPass Threads::Threads)
