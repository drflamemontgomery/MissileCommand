CC=g++
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lX11
SRCS=src/main.cpp src/tower.cpp 
HEADERS=src/tower.h 
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
