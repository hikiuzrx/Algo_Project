build: ui.o linked_list.o App.o
	gcc ui.o linked_list.o App.o -Iheaders $(shell pkg-config --libs --cflags raylib) -o FinaleApp

ui.o:
	gcc -c design/ui.c -Iheaders -o ui.o

linked_list.o:
	gcc -c linked_list/linked_list.c -Iheaders -o linked_list.o

App.o:
	gcc -c App.c -Iheaders -o App.o
