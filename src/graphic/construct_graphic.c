/*
** construct_graph.c for construct in /src/graphic/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue Mar 14 22:54:22 2017 Frederic ODDOU
** Last update Tue Mar 14 22:54:22 2017 Frederic ODDOU
*/

#include <string.h>
#include "graphic.h"

void		construct_graphic(t_graphic *this)
{
  memset(this, 0, sizeof(t_graphic));
  this->create = &create_graphic;
  this->destroy = &destroy_graphic;
  this->keycontrol = &key_control_graphic;
  this->reset = &reset_graphic;
  this->menu_box = &menu_box_graphic;
  this->content_box = &content_box_graphic;
}

bool		create_graphic(t_graphic *this)
{
  if ((this->win = newterm(NULL, stderr, stdin)) == NULL)
    return (false);
  nodelay(stdscr, TRUE);
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_RED);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  return (true);
}

void		destroy_graphic(t_graphic *this)
{
  endwin();
  delscreen(this->win);
}
