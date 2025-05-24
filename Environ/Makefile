CXX := clang++
CXXFLAGS := -g -std=c++11
INCLUDES := -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost -I /Users/christopherlinder/miniconda3/include/python3.12 -I /Users/christopherlinder/Library/Python/3.9/lib/python/site-packages/numpy/_core/include -I ../DataStructures -I /graphing

CXXFLAGS += -MMD
BUILD_DIR := build
#SOURCES:=test.cpp
SOURCES=$(wildcard *.cpp)
SOURCES+=../DataStructures/LOB.cpp
SOURCES+=graphing/graphUtils.cpp
SOURCES+=multiPort/complexWhile.cpp
OBJS:=$(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SOURCES)) #good
#OBJS:=$(SOURCES:.cpp=.o)
#DEPS:= $(OBJS:.o=.d)
DEPS:= test.cpp
TARGET:=$(BUILD_DIR)/output
#TARGET:=$(BUILD_DIR)
#-include $(OBJS:.o=.d)

#$(TARGET): $(OBJS) #good
$(TARGET): $(SOURCES)
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Users/christopherlinder/miniconda3/lib $(CXX) $(CXXFLAGS) $(INCLUDES) -L /Users/christopherlinder/miniconda3/lib -lpython3.12 -lm -rpath /Users/christopherlinder/miniconda3/lib $^ -o $@

#flags to compile everything: -MMD -MP
#$(BUILD_DIR)/%.o: ./%.cpp
#	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Users/christopherlinder/miniconda3/lib $(CXX) $(CXXFLAGS) $(INCLUDES) ./%.cpp

%.o: %.cpp
	LD_LIBRARY_PATH=D_LIBRARY_PATH:/Users/christopherlinder/miniconda3/lib clang++ -g -std=c++11 -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost -I /Users/christopherlinder/miniconda3/include/python3.12 -I /Users/christopherlinder/Library/Python/3.9/lib/python/site-packages/numpy/_core/include -L /Users/christopherlinder/miniconda3/lib -lpython3.12 -lm -rpath /Users/christopherlinder/miniconda3/lib -c $^ -o $@

#build/test.o: test.cpp
#	LD_LIBRARY_PATH=D_LIBRARY_PATH:/Users/christopherlinder/miniconda3/lib clang++ -g -std=c++11 -MMD -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost -I /Users/christopherlinder/miniconda3/include/python3.12 -I /Users/christopherlinder/Library/Python/3.9/lib/python/site-packages/numpy/_core/include -L /Users/christopherlinder/miniconda3/lib -lpython3.12 -lm -rpath /Users/christopherlinder/miniconda3/lib test.cpp -o build/output

#build/while.o: while.cpp while.hpp
#	clang++ -g -std=c++1y -I /Users/christopherlinder/Library/Mobile\ Documents/.Trash/boost/boost while.cpp

clean:
	$(RM) build/*.o