/*
** graphic.h for graphic in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue Mar 14 22:39:40 2017 Frederic ODDOU
** Last update Tue Mar 14 22:39:40 2017 Frederic ODDOU
*/

#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "philo.h"

/*
** Graphical struct for ncurses
*/

typedef struct	s_graphic
{
  SCREEN	*win;
  int		first_elem;
  int		curs;
  bool		(*create)(struct s_graphic *graphic);
  void		(*destroy)(struct s_graphic *graphic);
  bool		(*keycontrol)(t_core *core, struct s_graphic *graphic);
  void		(*reset)(t_core *core, struct s_graphic *graphic);
  void		(*menu_box)(t_core *core, struct s_graphic *graphic);
  void		(*content_box)(t_core *core, struct s_graphic *graphic);
}		t_graphic;

/*
** construct_graph.c
*/

void		construct_graphic(t_graphic *graphic);
bool		create_graphic(t_graphic *graphic);
void		destroy_graphic(t_graphic *graphic);

bool		core_graphic(t_core *core);

void		reinit_graphic(t_core *core, t_graphic *this);
void		menu_box_graphic(t_core *core, t_graphic *this);
void		content_box_graphic(t_core *core, t_graphic *this);
bool		key_control_graphic(t_core *core, t_graphic *this);
void		reset_graphic(t_core *core, t_graphic *this);
void		print_state_graphic(t_state state, WINDOW *local_win);
