project(Fractals)

add_library(renderer
        include/renderer.hpp src/renderer.cpp
        include/lodepng.h src/lodepng.cpp
        include/color_mappers.hpp src/color_mappers.cpp
        include/renderer_general.hpp src/renderer_general.cpp
        )

target_include_directories(renderer PUBLIC include)
target_link_libraries(renderer fractal)

enable_testing()