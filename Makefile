CXX = clang++
CXXFLAGS = -std=c++11 $(shell pkg-config --cflags sdl2) -Isrc
LDFLAGS = $(shell pkg-config --libs sdl2) $(shell pkg-config --libs sdl2_image)
SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HDRS = $(wildcard src/*.h) $(wildcard src/*/*.h)
OBJS = $(SRCS:.cpp=.o)

# Default build
game: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS) && ./out/play

# Debug using `leaks` tool that comes with macOS to check for memory leaks.
# `export MallocStackLogging=1` to get file and line number of memory leaks.
# Note: AddressSanitizer does not work on macOS Slicon.
debug: CXXFLAGS += -g
debug: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS)
	leaks --atExit --list -- ./out/play

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) ./out/play

print-vars:
	@echo "Source files:" $(SRCS)

format:
	clang-format --style=file:.clang-format -i $(SRCS) $(HDRS)
