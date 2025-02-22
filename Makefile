CFLAGS = -std=c++20 -O2 -Wall
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

$(BIN_DIR)/VKPlayground: $(OBJS)
	mkdir -p $(BIN_DIR)
	clang++ $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	clang++ $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: test clean

test: $(BIN_DIR)/VKPlayground
	./$(BIN_DIR)/VKPlayground

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
