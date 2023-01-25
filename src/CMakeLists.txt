file(GLOB SRCS *.cpp)
file(GLOB INCS *.h)

add_library(csv_lib ${INCS} ${SRCS})
add_executable(csv_parser ${INCS} ${SRCS})
target_include_directories(csv_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
