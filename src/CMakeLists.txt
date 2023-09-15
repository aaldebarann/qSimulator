set(target ${Q_LIBRARY})

file(GLOB srcs "../src/*.cpp" "../src/gates/*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs} ../include/shor.h)
target_link_libraries(${target} ${LIBRARY_DEPS})