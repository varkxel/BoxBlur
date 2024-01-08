cmake_minimum_required(VERSION 3.16)
project(LodePNG C)

add_library(LodePNG lodepng.c Include/lodepng.h)

target_include_directories(LodePNG PUBLIC Include)
