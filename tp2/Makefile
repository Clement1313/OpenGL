CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LDLIBS = -lGLEW -lGL -lglut

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
TARGET = tp2

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
