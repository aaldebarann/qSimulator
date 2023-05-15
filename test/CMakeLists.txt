set(target qSimulator_test)

file(GLOB srcs "*.cpp" )

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
