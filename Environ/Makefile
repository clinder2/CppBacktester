CXX := clang++
CXXFLAGS := -g -std=c++11
INCLUDES := -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost -I /Users/christopherlinder/miniconda3/include/python3.12 -I /Users/christopherlinder/Library/Python/3.9/lib/python/site-packages/numpy/_core/include

CXXFLAGS += -MMD
BUILD_DIR := build
SOURCES:=test.cpp
#SOURCES=$(wildcard *.cpp)
OBJS:=$(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
#DEPS:= $(OBJS:.o=.d)
DEPS:= test.cpp while.cpp
TARGET:=$(BUILD_DIR)/output
#-include $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Users/christopherlinder/miniconda3/lib $(CXX) $(CXXFLAGS) $(INCLUDES) -L /Users/christopherlinder/miniconda3/lib -lpython3.12 -lm -rpath /Users/christopherlinder/miniconda3/lib $^ -o $@

#flags to compile everything: -MMD -MP
$(BUILD_DIR)/%.o: ./%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./%.cpp

build/test.o: test.cpp
	clang++ -g -std=c++1y -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost -L /Users/christopherlinder/miniconda3/lib -lpython3.12 test.cpp

build/while.o: while.cpp while.hpp
	clang++ -g -std=c++1y -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost while.cpp

clean:
	$(RM) build/*.o