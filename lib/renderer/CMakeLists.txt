project(Fractals)

add_library(renderer
        include/renderer.hpp src/renderer.cpp
        include/lodepng.h src/lodepng.cpp
        )

target_include_directories(renderer PUBLIC include)
target_link_libraries(renderer fractal)

enable_testing()