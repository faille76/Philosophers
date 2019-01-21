##
## Makefile for make in /nm/
##
## Made by Frederic ODDOU
## Login   <frederic.oddou@epitech.eu>
##
## Started on  Mon Feb 13 14:09:31 2017 Frederic ODDOU
## Last update Thu Mar 16 21:49:18 2017 Frederic ODDOU
##

ECHO	=	/bin/echo -e
DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[0;31m"
BLUE	=	"\033[0;34m"

DIR_INC =	./include/
DIR_SRC =	./src/
DIR_GRAPH =	$(DIR_SRC)graphic/

SRC 	=	$(DIR_SRC)main.c \
		$(DIR_SRC)parser.c \
		$(DIR_SRC)vars.c \
		$(DIR_SRC)philosophes_construct.c \
		$(DIR_SRC)philosophes_utils.c \
		$(DIR_SRC)philosophes.c \
		$(DIR_GRAPH)construct_graphic.c \
		$(DIR_GRAPH)core_graphic.c \
		$(DIR_GRAPH)menu_box_graphic.c \
		$(DIR_GRAPH)content_box_graphic.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wextra \
		-Wall \
		-Werror \
		-I$(DIR_INC) \
		-fPIC

LDFLAGS	=	-lncurses \
		-L ./lib -Wl,-rpath,./lib -lriceferee -lpthread

NAME	=	./philo

mess:
		@$(ECHO) $(RED) " _____  _     _ _                       _" $(DEFAULT)
		@$(ECHO) $(RED) "|  __ \\| |   (_) |                     | |" $(DEFAULT)
		@$(ECHO) $(RED) "| |__) | |__  _| | ___  ___  ___  _ __ | |__   ___  ___" $(DEFAULT)
		@$(ECHO) $(RED) "|  ___/| '_ \\| | |/ _ \\/ __|/ _ \\| '_ \\| '_ \\ / _ \\/ __|" $(DEFAULT)
		@$(ECHO) $(RED) "| |    | | | | | | (_) \\__ \\ (_) | |_) | | | |  __/\\__ \\" $(DEFAULT)
		@$(ECHO) $(RED) "|_|    |_| |_|_|_|\\___/|___/\\___/| .__/|_| |_|\\___||___/" $(DEFAULT)
		@$(ECHO) $(RED) "				  | |" $(DEFAULT)
		@$(ECHO) $(RED) "				  |_|" $(DEFAULT)

all:		mess $(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

debug:
		@make re CC="gcc -D DEBUG" -C ./ -f Makefile -s

graphic:
		@make re CC="gcc -D GRAPHIC" -C ./ -f Makefile -s

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY:		all clean fclean re $(NAME) .c.o mess debug graphic
