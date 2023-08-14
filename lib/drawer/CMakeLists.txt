project(drawer)

add_library(drawer
        include/drawer.hpp src/drawer.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC include)

enable_testing()