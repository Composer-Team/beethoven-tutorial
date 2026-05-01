cmake_minimum_required(VERSION 3.20)
project(vector_add LANGUAGES CXX)

find_package(beethoven REQUIRED)

beethoven_build(vector_tb SOURCES vector_tb.cc)
