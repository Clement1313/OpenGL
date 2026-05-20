CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
TARGET = tp2

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
