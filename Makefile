CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SOURCES := main.cpp Eliza.cpp Utils.cpp ResponseTracker.cpp \
           Concern.cpp GenericVerbs.cpp Relationships.cpp Financial.cpp \
           Wellbeing.cpp Education.cpp Entertainment.cpp Family.cpp

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
