CFLAGS = -std=c++20 -O2 -Wall
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


$(BIN_DIR)/VKPlayground: $(OBJS)
	mkdir -p $(BIN_DIR)
	clang++ $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)  
	clang++ $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: test clean

test: $(BIN_DIR)/VKPlayground
	./$(BIN_DIR)/VKPlayground

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
