file(GLOB SRCS *.cpp)
file(GLOB INCS *.hpp)

list(FILTER SRCS EXCLUDE REGEX "main\\.cpp$")

add_library(csv_lib ${INCS} ${SRCS})
add_executable(csv_parser main.cpp)

target_include_directories(csv_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(csv_parser PRIVATE csv_lib)
target_include_directories(csv_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
