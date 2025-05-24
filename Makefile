# Makefile

# To compile ncurses use the following config flags
# CC=clang CXX=clang++ ./configure --prefix /home/spagett/docs/UNI/oop/FARM-GAME-1/ncurses --enable-widec --with-pthread CFLAGS="-fPIC" CXXFLAGS="-fPIC
# replace prefix path with your prefix

# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Exec name
TARGET = main 

# Sources
SRCS = main.cpp

# Library includes
LIB_INC = -I ncurses/include/ -I ncurses/include/ncursestw/ -L ncurses/lib/

# Activate library
LIBS = -lncursestw -ldl -pthread

# Build and run
.PHONY: all
all: 
	echo "This is not working yet"
	# $(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) $(SRCS) $(LIBS)
	# ./$(TARGET)
	
.PHONY: display
display:
	$(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp $(LIBS)
	./$(TARGET)
	
# Just build
.PHONY: build 
build: 
	echo "This is not working yet"
	# $(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) $(SRCS) $(LIBS)

# Clean repo
.PHONY: clean
clean: 
	echo "This is not working yet"
	# rm -f $(TARGET)
