main: maze.o graphics.o rat.o
	g++ -Wall -o $@ $^ -lglut -lGLU -lGL

maze.o: maze.cpp maze.h
	g++ -std=c++11 -c $< 
graphics.o: graphics.cpp graphics.h maze.h
	g++ -std=c++11 -c $<
rat.o: rat.cpp rat.h graphics.h
	g++ -std=c++11 -c $<









clean:
	rm main *.o
