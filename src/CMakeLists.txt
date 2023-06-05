set(target ${Q_LIBRARY})

file(GLOB srcs "../src/*.cpp" "../src/gates/*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs} )
target_link_libraries(${target} ${LIBRARY_DEPS})