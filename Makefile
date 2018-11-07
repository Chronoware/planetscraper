OBJS   = colors.c states.c events.c tick.c render.c main.c
STATES = stateIntro.c stateMenu.c
CC    = gcc
FLAGS = -lSDL2 -lSDL2_image
NAME  = Planet\ Scraper

all: $(OBJS)
	$(CC) $(OBJS) $(STATES) $(FLAGS) -o $(NAME)
