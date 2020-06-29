CC=g++
CFLAGS=-c -Wall
CXXFLAGS = -Wall -c $(DEBUG) -std=c++11 -pthread  `pkg-config gtkmm-3.0 --cflags --libs`
LDFLAGS=
SOURCES=MPC_Player.cpp mpc-gui-p2p-peer3.cpp MPCGUI.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mpc-gui-p2p-peer3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ `pkg-config gtkmm-3.0 --cflags --libs`

.cpp.o:
	$(CC) $(CXXFLAGS) $< -o $@ `pkg-config gtkmm-3.0 --cflags --libs`


#~ all:
#~ 	g++ -std=c++11 *.cpp -o mpc-gui-p2p-peer3 `pkg-config gtkmm-3.0 --cflags --libs`
