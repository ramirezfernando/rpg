CXX = clang++
CXXFLAGS = -std=c++11 $(shell pkg-config --cflags sdl2) -Isrc
LDFLAGS = $(shell pkg-config --libs sdl2) $(shell pkg-config --libs sdl2_image)
SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default build
game: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS)

# Debug using `leaks` tool that comes with macOS to check for memory leaks.
# `export MallocStackLogging=1` to get file and line number of memory leaks.
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