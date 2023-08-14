cmake_minimum_required(VERSION 3.14)

project(Int128 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "TESTS_BUILD_TYPE ${TESTS_BUILD_TYPE}")

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.3.2
)

FetchContent_MakeAvailable(Catch2)

if (TESTS_BUILD_TYPE MATCHES ASAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1 -fsanitize=address -fno-omit-frame-pointer
            -fno-inline -fno-sanitize-recover=all)
    set(LINK_OPTS -fsanitize=address)
endif()
if (TESTS_BUILD_TYPE MATCHES MSAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1 -fsanitize=leak
            -fno-omit-frame-pointer -fno-sanitize-recover=all)
    set(LINK_OPTS -fsanitize=leak)
endif()
if (TESTS_BUILD_TYPE MATCHES USAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1
            -fsanitize=undefined,float-cast-overflow,float-divide-by-zero
            -fno-omit-frame-pointer -fno-sanitize-recover=all
            -fsanitize-recover=alignment)
    set(LINK_OPTS
            -fsanitize=undefined,float-cast-overflow,float-divide-by-zero)
endif()

# to run sanitizers locally
# add_compile_options(-fsanitize=address,undefined,leak -fno-sanitize-recover=all)
# add_link_options(-fsanitize=address,undefined,leak)

# Configure clang-tidy
if (${USE_CLANG_TIDY})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

add_subdirectory(lib)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE drawer fractal)
