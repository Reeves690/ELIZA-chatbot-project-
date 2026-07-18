# Makefile for the ELIZA project -- MILESTONE SUBMISSION
# Only the core engine + component 1 (Generic Verbs) are wired up at
# this stage. No special flags are required beyond C++17 support.

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SOURCES := main.cpp Eliza.cpp Utils.cpp ResponseTracker.cpp GenericVerbs.cpp

OBJECTS := $(SOURCES:.cpp=.o)
TARGET := eliza

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
