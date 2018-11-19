IDIR = ../include
OBJS   = colors.c states.c events.c tick.c render.c main.c
STATES = stateIntro.c stateMenu.c stateNewgame.c stateGame.c
CC    = gcc
CFLAGS = -I$(IDIR)
LIBS = -lSDL2 -lSDL2_image
NAME  = Planet\ Scraper

all: $(OBJS)
	$(CC) $(OBJS) $(STATES) $(CFLAGS) $(LIBS) -o $(NAME)
