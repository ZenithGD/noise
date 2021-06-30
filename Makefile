LIBS = libs
SRC = src
BUILD = build
BIN = bin

VPATH = $(LIBS) $(SRC)
INCLUDES = -I. $(addprefix -I, $(VPATH))

MAIN = main
MAIN_DEPS = $(addprefix $(BUILD)/, $(MAIN).o $(MATH).o $(NOISE).o)

LINES = lines
NOISE = noise
MATH = mathutils

CC = g++
CFLAGS = -Wall -std=c++20 $(INCLUDES)
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: dirs main
	@echo "Compilación terminada."

main: $(MAIN_DEPS) | $(BUILD) $(BIN)
	$(CC) $(MAIN_DEPS) -o $(BIN)/$(MAIN) $(CFLAGS) $(LFLAGS)
	
$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# additional required headers
$(BUILD)/$(MAIN).o: $(LIBS)/$(NOISE).hpp $(LIBS)/$(MATH).hpp

# individual headers
$(BUILD)/$(MATH).o: $(LIBS)/$(MATH).hpp
dirs:
	mkdir -p bin build

clean:
	rm -rvf bin build