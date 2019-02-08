cmake_minimum_required(VERSION 3.13)
project(containerpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        containerpp
        main.cpp
        Container.h
        Container.cpp
        ContainerTemplate.h)