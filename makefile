CXX = /opt/homebrew/opt/llvm/bin/clang++
# Use C++23 standard:
CXXFLAGS = -std=c++23
# Include SDL3 headers and src directory, plus Homebrew include:
CXXFLAGS += -Isrc -I/opt/homebrew/include
# Treat SDL3 as system headers (suppresses warnings):
CXXFLAGS += -isystem $(shell pkg-config --variable=includedir sdl3)
# Increase warning levels:
CXXFLAGS += -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Wimplicit-fallthrough
# Treat warnings as errors:
CXXFLAGS += -Werror

LDFLAGS = $(shell pkg-config --libs sdl3) $(shell pkg-config --libs sdl3-image)
LDFLAGS += -L/opt/homebrew/opt/llvm/lib/c++ -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++ -L/opt/homebrew/lib

# All sources except the two mains and the test files
ALL_SRCS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
TEST_SRCS = $(filter %_test.cpp, $(ALL_SRCS))
SHARED_SRCS = $(filter-out src/client.cpp src/server.cpp $(TEST_SRCS), $(ALL_SRCS))
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_BIN = ./out/test_runner
TEST_LDFLAGS = $(LDFLAGS) -lgtest -lgtest_main -pthread

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
	$(CXX) $(SHARED_OBJS) $(CLIENT_OBJ) -o ./out/client $(LDFLAGS) && ./out/client

# Build and run the server.
server: $(SHARED_OBJS) $(SERVER_OBJ)
	$(CXX) $(SHARED_OBJS) $(SERVER_OBJ) -o ./out/server $(LDFLAGS) && ./out/server

debug-server: CXXFLAGS += -g -DDEBUG_MODE
debug-server: $(SHARED_OBJS) $(SERVER_OBJ)
	$(CXX) $(SHARED_OBJS) $(SERVER_OBJ) -o ./out/server $(LDFLAGS) && ./out/server

# Compile all source files.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the object files and both executables.
clean:
	rm -f $(SHARED_OBJS) $(CLIENT_OBJ) $(SERVER_OBJ) $(TEST_OBJS) ./out/client ./out/server $(TEST_BIN)

# Format files using clang-format.
format:
	clang-format --style=file:.clang-format -i $(SHARED_SRCS) src/client.cpp src/server.cpp $(TEST_SRCS) $(HDRS)

# Run `clang-tidy` on source files.
tidy:
	clang-tidy $(SHARED_SRCS) src/client.cpp src/server.cpp $(TEST_SRCS) -- $(CXXFLAGS)

# Run `clang-tidy` with automatic fixes.
tidy-fix:
	clang-tidy $(SHARED_SRCS) src/client.cpp src/server.cpp $(TEST_SRCS) --fix -- $(CXXFLAGS)

# Build and run tests.
test: $(SHARED_OBJS) $(TEST_OBJS)
	$(CXX) $(SHARED_OBJS) $(TEST_OBJS) -o $(TEST_BIN) $(TEST_LDFLAGS)
	$(TEST_BIN)

.PHONY: build game server debug-game debug-server clean format tidy tidy-fix test