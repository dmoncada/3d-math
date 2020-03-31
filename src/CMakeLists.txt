# Bring the sources for the shared library into the project.
file(GLOB SOURCES "*.cpp")

# Generate the shared library from the sources.
add_library(3d-math SHARED ${SOURCES})

# Set the library installation location; use `sudo make install` to apply.
install(TARGETS 3d-math DESTINATION /usr/lib)
