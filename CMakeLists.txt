cmake_minimum_required(VERSION 3.11)

project(CPP_r-type_2019)
add_definitions("-fPIC")
set(CMAKE_CXX_STANDARD 11)

# conan
#find_package(Boost)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# source file common
set(SRC_COMMON ${CMAKE_SOURCE_DIR}/src/include/)
FILE(GLOB_RECURSE SRC_COMMON_FILE ${SRC_COMMON}/*.cpp)
FILE(GLOB_RECURSE INC_COMMON_FILE ${SRC_COMMON}/*.hpp)

# source files r-type_server
set(SRC_SERVER ${CMAKE_SOURCE_DIR}/src/server/src/)
set(INC_SERVER ${CMAKE_SOURCE_DIR}/src/server/include/)

# source files r-type_client
set(SRC_CLIENT ${CMAKE_SOURCE_DIR}/src/client/src/)
set(INC_CLIENT ${CMAKE_SOURCE_DIR}/src/client/include/)

# File server
FILE(GLOB_RECURSE SRC_SERVER_FILE ${SRC_SERVER}/*.cpp)
FILE(GLOB_RECURSE INC_SERVER_FILE ${INC_SERVER}/*.hpp)

# File client
FILE(GLOB_RECURSE SRC_CLIENT_FILE ${SRC_CLIENT}/*.cpp)
FILE(GLOB_RECURSE INC_CLIENT_FILE ${INC_CLIENT}/*.hpp)

#compiler
if (UNIX)
    add_executable(r-type_server ${SRC_SERVER_FILE} ${SRC_COMMON_FILE} ${INC_COMMON_FILE} ${INC_SERVER})
    #add_executable(r-type_server ${SRC_SERVER_FILE} ${SRC_COMMON_FILE})
    target_link_libraries(r-type_server ${CONAN_LIBS})
    add_executable(r-type_client ${SRC_CLIENT_FILE}  ${SRC_COMMON_FILE} ${INC_COMMON_FILE} ${INC_CLIENT})
    #add_executable(r-type_client ${SRC_CLIENT_FILE}  ${SRC_COMMON_FILE})
    target_link_libraries(r-type_client ${CONAN_LIBS})
endif(UNIX)
