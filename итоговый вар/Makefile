CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20 -w -O2

SRCTESTS = test.cpp ln.cpp
SRCPI = pi.cpp ln.cpp

OBJTESTS = $(SRCTESTS:.cpp=.o) 
OBJPI = $(SRCPI:.cpp=.o)

TARGETTESTS = test.exe
TARGETPI = pi.exe

all: $(TARGETTESTS) $(TARGETPI)

$(TARGETTESTS): $(OBJTESTS)
	$(CXX) $^ -o $@

$(TARGETPI): $(OBJPI)
	$(CXX) $^ -o $@


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: test
test: $(TARGETTESTS)
	./$(TARGETTESTS)

.PHONY: pi
pi: $(TARGETPI)
	./$(TARGETPI)

clean:
	rm -f *.o $(TARGETTESTS) $(TARGETPI)
