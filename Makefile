CXX := g++
CXXFLAGS := -std=c++17
SRC_DIR := src
TARGET := $(PROBLEM)

$(TARGET):
	$(CXX) $(SRC_DIR)/$(TARGET).cc -o $(TARGET) $(CXXFLAGS)
