CXX := clang++
CXXFLAGS := -g -std=c++11
INCLUDES := -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost

BUILD_DIR := build
#SOURCES:=$(shell find . -type f -name '*.cpp')
SOURCES=test.cpp
OBJS:=$(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS:= $(OBJS:.o=.d)
TARGET:=$(BUILD_DIR)/output

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(BUILD_DIR)/%.o: ./%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./%.cpp

build/test.o: test.cpp
	clang++ -g -std=c++1y -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost test.cpp

build/while.o: while.cpp while.hpp
	clang++ -g -std=c++1y -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost while.cpp

clean:
	$(RM) build/*.o