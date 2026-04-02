CC = gcc
CFLAGS = -Wall -Wextra -o

SRCS = main.c calculos.c algoritmo_genetico.c manipulacao_arquivos.c
TARGET = programa

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)