# Bring the sources for the tests into the project.
file(GLOB TEST_SOURCES "src/*.cpp")

# Generate the tests executable from the sources.
add_executable(tests ${TEST_SOURCES})

# Link against the compiled shared library and googletest.
target_link_libraries(tests 3d-math gtest_main)

# Register a test; use `make test` to run it.
add_test(NAME testsuite COMMAND tests)
