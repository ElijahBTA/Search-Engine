cmake_minimum_required(VERSION 3.15)
project(SearchEngine)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)
# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(search_engine DocumentParserr.cpp
        IndexHandlerr.cpp porter2_stemmer.cpp
        DocumentContents.cpp QueryProcessor.cpp
        Interface.cpp main.cpp
)
add_executable(tests test.cpp AvlTree.h)
# this makes sure we also link rapidjson
target_include_directories(search_engine PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
