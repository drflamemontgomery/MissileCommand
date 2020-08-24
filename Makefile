CC=g++
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lX11
SRCS=src/main.cpp src/tower.cpp src/cursor.cpp src/explosion.cpp src/bullet.cpp src/house.cpp
HEADERS=src/tower.h src/cursor.h src/explosion.h src/bullet.h src/house.h
EXEDIR=bin
OUTFILE=main

exec : $(EXEDIR)
	$(CC) -o $(EXEDIR)/$(OUTFILE) $(HEADERS) $(SRCS) $(CFLAGS)
	$(EXEDIR)/$(OUTFILE)


$(EXEDIR):
	mkdir $(EXEDIR)


.PHONY : clean
clean : $(OBJS)
		find . -name "*~" -exec rm {} \;
		find . -name "#*#" -exec rm {} \;
