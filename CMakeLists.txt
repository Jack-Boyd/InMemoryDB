cmake_minimum_required(VERSION 3.15)
project(InMemoryDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Boost REQUIRED)

add_executable(InMemoryDB
  src/main.cpp
  src/Database.cpp
  src/QueryEngine.cpp
  src/Transaction.cpp
  src/Persistence.cpp
  src/Network.cpp
)

target_include_directories(InMemoryDB PRIVATE include ${Boost_INCLUDE_DIRS})

enable_testing()
