set(target "gtest")

file(GLOB hdrs "*.h*" "../include/*.cpp")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_library(${target} STATIC gtest-all.cc ${srcs} ${hdrs})

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
        ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
(${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_link_libraries(${target} ${pthread})