all: chaos.cpp
	g++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio chaos.cpp -o chaos.exe