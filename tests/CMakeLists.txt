enable_testing()

file(GLOB SRCS *.cpp)

add_executable(csv_parser_tests ${SRCS})
target_link_libraries(csv_parser_tests PRIVATE csv_lib)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
gtest_discover_tests(csv_parser_tests)

target_link_libraries(csv_parser_tests PRIVATE gtest_main)
target_include_directories(csv_parser_tests PUBLIC ${CMAKE_SOURCE_DIR}/src)
