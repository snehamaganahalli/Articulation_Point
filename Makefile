all:
	g++ articulation_point.cpp -std=c++11 -o exe

clean:
	/bin/rm -rf exe
