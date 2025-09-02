cmake_minimum_required(VERSION 3.15)
project(InMemoryDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(InMemoryDB
  src/main.cpp
  src/Database.cpp
  src/QueryEngine.cpp
)

enable_testing()