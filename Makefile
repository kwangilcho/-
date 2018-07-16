CXX := g++
CXXFLAGS := -std=c++17
TARGET := $2

$(TARGET) :
	$(CXX) $(CXXFLAGS) -o $(TARGET)
