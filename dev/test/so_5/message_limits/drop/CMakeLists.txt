set(UNITTEST _unit.test.message_limits.drop)
add_executable(${UNITTEST} main.cpp)
target_link_libraries(${UNITTEST} so.${SO_5_VERSION})
add_test(${UNITTEST} ${UNITTEST})
