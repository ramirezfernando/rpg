CXX = clang++
CXXFLAGS = -std=c++11 $(shell pkg-config --cflags sdl2) -Isrc
LDFLAGS = $(shell pkg-config --libs sdl2) $(shell pkg-config --libs sdl2_image)
SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJS = $(SRCS:.cpp=.o)

game: $(OBJS)
	$(CXX) $(OBJS) -o ./out/play $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) ./out/play

print-vars:
	@echo "Source files:" $(SRCS)