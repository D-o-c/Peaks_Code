cmake_minimum_required(VERSION 3.9)
project(dump_import)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-march=native -Wall -lbz2 -lz \
            -lmysqlcppconn -static-libgcc -pthread -lstdc++ -pipe -lgmp -lboost_system -lboost_filesystem")

add_definitions(-DGPG_COMPATIBLE)
add_definitions(-DTMP_FOLDER_CSV="/var/lib/mysql-files/gpg_keyserver/dump_import/")
add_definitions(-DERROR_FOLDER="/tmp/gpg_keyserver_ERRORS/dump_import_errors/")
add_definitions(-DDEFAULT_DUMP_PATH="/tmp/pgp_dump/")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Werror")

set(SOURCE_FILES main.cc DBManager.cc Thread_Pool.cc unpacker.cc DBStruct.h utils.cc Key_Tools.cc DB_info.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(dump_import ${SOURCE_FILES})

set(OpenPGP_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../OpenPGP)
include_directories(${OpenPGP_DIRECTORY})
link_directories(${OpenPGP_DIRECTORY})

target_link_libraries(dump_import ${OpenPGP_DIRECTORY}/libOpenPGP.a)
