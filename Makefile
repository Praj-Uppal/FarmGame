# Makefile

# To compile ncurses, navigate to the ncurses subdirectory within a WSL shell (e.g. ncurses-6.3) and use the following command & config flags.
# 1. CC=clang CXX=clang++ ./configure --prefix /home/spagett/docs/UNI/oop/FARM-GAME-1/ncurses --enable-widec --with-pthread CFLAGS="-fPIC" CXXFLAGS="-fPIC"
# 2. make -j16
# 3. make install
# NOTE: replace --prefix value with the appropriate absolute path on your PC pointing to <project root>/ncurses

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

	# $(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) $(SRCS) $(LIBS)
	$(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp ./src/GameManager.cpp ./src/main.cpp $(LIBS)
	./$(TARGET)
	
.PHONY: display
display:
	$(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp $(LIBS)
	./$(TARGET)
	
# Just build
.PHONY: build 
build: 
	# $(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) $(SRCS) $(LIBS)

# Clean repo
.PHONY: clean
clean: 
	# rm -f $(TARGET)
