file(GLOB SRCS *.cpp)
file(GLOB PRIVATE_INCS *.hpp)
file(GLOB INCS ../inc/*.hpp)

list(FILTER SRCS EXCLUDE REGEX "main\\.cpp$")

add_library(csv_lib ${INCS} ${PRIVATE_INCS} ${SRCS})
add_executable(csv_parser main.cpp)

target_include_directories(csv_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(csv_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

target_link_libraries(csv_parser PRIVATE csv_lib)
target_include_directories(csv_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
