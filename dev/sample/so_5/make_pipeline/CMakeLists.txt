set(SAMPLE sample.so_5.make_pipeline)
add_executable(${SAMPLE} main.cpp)
target_link_libraries(${SAMPLE} so.${SO_5_VERSION})
install(TARGETS ${SAMPLE} DESTINATION bin)

