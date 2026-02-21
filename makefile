CXX = /opt/homebrew/opt/llvm/bin/clang++
# Use C++23 standard:
CXXFLAGS = -std=c++23
# Include SDL3 headers and src directory:
CXXFLAGS += -Isrc
# Treat SDL3 as system headers (suppresses warnings):
CXXFLAGS += -isystem $(shell pkg-config --variable=includedir sdl3)
# Increase warning levels:
CXXFLAGS += -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Wimplicit-fallthrough
# Treat warnings as errors:
CXXFLAGS += -Werror
LDFLAGS = $(shell pkg-config --libs sdl3) $(shell pkg-config --libs sdl3-image)

# All sources except the two mains
SHARED_SRCS = $(filter-out src/client.cpp src/server.cpp, $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp))
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

CLIENT_OBJ = src/client.o
SERVER_OBJ = src/server.o

HDRS = $(wildcard src/*.h) $(wildcard src/*/*.h) $(wildcard src/*/*/*.h)

# Build both binaries.
build: $(SHARED_OBJS) $(CLIENT_OBJ) $(SERVER_OBJ)
	$(CXX) $(SHARED_OBJS) $(CLIENT_OBJ) -o ./out/client $(LDFLAGS)
	$(CXX) $(SHARED_OBJS) $(SERVER_OBJ) -o ./out/server $(LDFLAGS)

# Build and run the client.
game: $(SHARED_OBJS) $(CLIENT_OBJ)
	$(CXX) $(SHARED_OBJS) $(CLIENT_OBJ) -o ./out/client $(LDFLAGS) && ./out/client

debug-game: CXXFLAGS += -g -DDEBUG_MODE
debug-game: $(SHARED_OBJS) $(CLIENT_OBJ)
	$(CXX) $(SHARED_OBJS) $(CLIENT_OBJ) -o ./out/client $(LDFLAGS)

# Build and run the server.
server: $(SHARED_OBJS) $(SERVER_OBJ)
	$(CXX) $(SHARED_OBJS) $(SERVER_OBJ) -o ./out/server $(LDFLAGS) && ./out/server

debug-server: CXXFLAGS += -g -DDEBUG_MODE
debug-server: $(SHARED_OBJS) $(SERVER_OBJ)
	$(CXX) $(SHARED_OBJS) $(SERVER_OBJ) -o ./out/server $(LDFLAGS)

# Compile all source files.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the object files and both executables.
clean:
	rm -f $(SHARED_OBJS) $(CLIENT_OBJ) $(SERVER_OBJ) ./out/client ./out/server

# Format files using clang-format.
format:
	clang-format --style=file:.clang-format -i $(SHARED_SRCS) src/client.cpp src/server.cpp $(HDRS)

# Run `clang-tidy` on source files.
tidy:
	clang-tidy $(SHARED_SRCS) src/client.cpp src/server.cpp -- $(CXXFLAGS)

# Run `clang-tidy` with automatic fixes.
tidy-fix:
	clang-tidy $(SHARED_SRCS) src/client.cpp src/server.cpp --fix -- $(CXXFLAGS)

.PHONY: build game server debug-game debug-server clean format tidy tidy-fix