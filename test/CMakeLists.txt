project(ngen_state_system_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ngen_state_system_tests
        test_game_state.cpp test_state_tree.cpp.cpp)

target_link_libraries(ngen_state_system_tests gtest gtest_main)
target_link_libraries(ngen_state_system_tests ngen_state_system)
