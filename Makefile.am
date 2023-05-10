# Build subdir objects
AUTOMAKE_OPTIONS = subdir-objects

# Set the default build type to "debug"
build_type = debug

# Define flags for debug and release builds
debug_CFLAGS = -g -O2 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion
debug_CPPFLAGS = -std=c17 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion
release_CFLAGS = -O3 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion
release_CPPFLAGS = -std=c17 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion

# Conditionally set the flags based on the build type
if BUILD_DEBUG
  AM_CFLAGS = $(debug_CFLAGS)
  AM_CPPFLAGS = $(debug_CPPFLAGS)
else
  AM_CFLAGS = $(release_CFLAGS)
  AM_CPPFLAGS = $(release_CPPFLAGS)
endif

# Define the source files for your project
bin_PROGRAMS = vpr-midas
vpr_midas_SOURCES = src/main.c
