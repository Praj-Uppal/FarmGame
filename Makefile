# Makefile

# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Exec name
TARGET = ncurses_test

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
