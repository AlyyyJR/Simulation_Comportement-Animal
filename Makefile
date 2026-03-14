CXX = g++
CXXFLAGS = -w
INCLFLAGS = -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
EXEC_FILES = Main

all: Main

Main:
	$(CXX) $(INCLFLAGS) -o Main *.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC_FILES)