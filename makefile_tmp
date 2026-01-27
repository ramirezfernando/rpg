CXX = clang++
# Use C++20 standard:
CXXFLAGS = -std=c++20
# Include SDL2 headers and src directory:
CXXFLAGS += -Isrc
# Treat SDL2 as system headers (suppresses warnings):
CXXFLAGS += -isystem $(shell pkg-config --variable=includedir sdl2)
# Increase warning levels:
CXXFLAGS += -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion
# Treat warnings as errors:
CXXFLAGS += -Werror
LDFLAGS = $(shell pkg-config --libs sdl2) $(shell pkg-config --libs sdl2_image)
SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
HDRS = $(wildcard src/*.h) $(wildcard src/*/*.h) $(wildcard src/*/*/*.h)
OBJS = $(SRCS:.cpp=.o)

# Build the game
build:
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS)

# Build and run the game
game: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS) && ./out/play

# Debug using `leaks` tool that comes with macOS to check for memory leaks.
# `export MallocStackLogging=1` to get file and line number of memory leaks.
# Note: AddressSanitizer does not work on macOS Slicon.
debug: CXXFLAGS += -g -DDEBUG_MODE
debug: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS)
	leaks --atExit --list -- ./out/play

# Compile all source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the object files and the executable
clean:
	rm -f $(OBJS) ./out/play

# Format files using clang-format
format:
	clang-format --style=file:.clang-format -i $(SRCS) $(HDRS)

# Run clang-tidy on source files
tidy:
	clang-tidy --header-filter='src/.*' $(SRCS) -- $(CXXFLAGS)

# Run clang-tidy with automatic fixes
tidy-fix:
	clang-tidy --header-filter='src/.*' $(SRCS) --fix -- $(CXXFLAGS)

.PHONY: build game debug clean format tidy tidy-fix