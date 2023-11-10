cmake_minimum_required(VERSION 3.26)
project(source)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(source
        carte.cpp
        carte.h
        espacejeux.cpp
        espacejeux.hpp
        jetons.cpp
        jetons.hpp
        joueur.cpp
        joueur.hpp
        main.cpp
        partie.cpp
        partie.hpp
        strategy.cpp
        strategy.hpp
        sqlite/shell.c
        sqlite/sqlite3.c
        sqlite/sqlite3.h
        sqlite/sqlite3ext.h)
