CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
LDFLAGS  := -lm
BUILD    := ./build
TARGET   := programa
SRC      := $(wildcard src/*.c)

all: $(BUILD)/$(TARGET)

$(BUILD)/$(TARGET): $(SRC)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BUILD)/$(TARGET) $(SRC)

.PHONY: all clean run

clean:
	-@rm -rvf $(BUILD)

run: $(BUILD)/$(TARGET)
	./$(BUILD)/$(TARGET)

compilar: clean $(BUILD)/$(TARGET)
	$(BUILD)/$(TARGET)