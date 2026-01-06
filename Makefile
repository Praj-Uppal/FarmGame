# Makefile

# To compile ncurses, navigate to the ncurses subdirectory within a WSL shell (e.g. ncurses-6.3) and use the following command & config flags.
# 1. CC=clang CXX=clang++ ./configure --prefix /yourPathHere/FarmGame/ncurses --enable-widec --with-pthread CFLAGS="-fPIC" CXXFLAGS="-fPIC"
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
LIB_INC = -I ncurses/include/ncursestw/ -L ncurses/lib/

# Activate library
LIBS = -lncursesw -ldl -pthread

# Build and run
.PHONY: ale
all: 
	@if [ ! -d "ncurses" ]; then \
		echo "Error: ncurses was not found, please install it to ./ncurses!"; \
		exit 1; \
	fi
	@$(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp ./src/GameManager.cpp ./src/main.cpp $(LIBS) 2> /dev/null
	./$(TARGET)
	
# Just build
.PHONY: build 
build: 
	@if [ ! -d "ncurses" ]; then \
		echo "Error: ncurses was not found, please install it to ./ncurses!"; \
		exit 1; \
	fi
	@$(CXX) $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp ./src/GameManager.cpp ./src/main.cpp $(LIBS) 2> /dev/null

.PHONY: release-
	release:-
	@if [ ! -d "ncurses" ]; then \
		echo "Error: ncurses was not found, please install it to ./ncurses!"; \
		exit 1; \
	fi
	@$(CXX) -O3 $(CXXFLAGS) $(LIB_INC) -o $(TARGET) ./src/Display.cpp ./src/Player.cpp ./src/FarmPlot.cpp ./src/CarrotPlant.cpp ./src/PotatoPlant.cpp ./src/Entity.cpp ./src/Item.cpp ./src/Plant.cpp ./src/Plot.cpp ./src/Inventory.cpp ./src/GameManager.cpp ./src/main.cpp $(LIBS) 2> /dev/null

# Clean repo
.PHONY: clean
clean: 
	@rm -f $(TARGET)
	@rm -f save.dat
