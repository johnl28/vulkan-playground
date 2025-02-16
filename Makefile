CFLAGS = -std=c++20 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

VKPlayground: $(OBJS)
	clang++ $(CFLAGS) -o VKPlayground $(OBJS) $(LDFLAGS)

%.o: %.cpp
	clang++ $(CFLAGS) -c $< -o $@

.PHONY: test clean

test: VKPlayground
	./VKPlayground

clean:
	rm -f VKPlayground $(OBJS)