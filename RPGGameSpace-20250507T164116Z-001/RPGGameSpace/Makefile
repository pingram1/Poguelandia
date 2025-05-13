# Makefile for Game Battle RPG

CXX = g++  # The C++ compiler
CXXFLAGS = -std=c++11 -Wall  # Compiler flags (C++11 standard and warnings)

# List of all source files
SOURCES = $(wildcard *.cpp)

# The output executable
TARGET = GameBattleRPG

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable from the source files
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean up the generated files
clean:
	rm -f $(TARGET)
