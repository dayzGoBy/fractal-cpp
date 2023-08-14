project(fractal)

add_library(fractal
        include/fractal.hpp src/fractal.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC include)

enable_testing()

add_executable(FractalTests tests/FractalTest.cpp)
target_link_libraries(FractalTests PRIVATE Catch2::Catch2WithMain fractal)