CC = gcc
CFLAGS = -Wall -Wextra
SRCS = src/main.c src/calculos.c src/algoritmo_genetico.c src/manipulacao_arquivos.c
TARGET = programa

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)