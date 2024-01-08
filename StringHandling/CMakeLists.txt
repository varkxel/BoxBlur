cmake_minimum_required(VERSION 3.16)
project(StringHandling C)

add_library(StringHandling StringHandling.c Include/StringHandling.h)

target_include_directories(StringHandling PUBLIC Include)
