cmake_minimum_required(VERSION 3.19)
project(BoxBlur C)

set(CMAKE_C_STANDARD 11)

# Custom code
add_subdirectory(StringHandling)

# Libraries
add_subdirectory(lodepng)
find_package(Threads REQUIRED)

add_executable(BoxBlur Main.c Image.c Image.h Blur.c Blur.h)

target_link_libraries(BoxBlur PRIVATE StringHandling)
target_link_libraries(BoxBlur PRIVATE LodePNG)

target_link_libraries(BoxBlur PRIVATE Threads::Threads)
