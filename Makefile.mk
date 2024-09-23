# Makefile #

CC = gcc
TARGET = test.exe
OBJS = main.o functions.o

$(TARGET): main.o functions.o
	 $(CC) -o $(TARGET) main.o functions.o -lncursesw

functions.o: functions.c
	$(CC) -c functions.c

main.o: main.c
	$(CC) -c main.c

clean:
	del $(OBJS)