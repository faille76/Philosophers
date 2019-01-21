/*
** menu_box_graphic.c for box graphic in /src/graphic/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Mar 15 01:15:55 2017 Frederic ODDOU
** Last update Wed Mar 15 01:15:55 2017 Frederic ODDOU
*/

#include <ncurses.h>
#include "philo.h"
#include "graphic.h"

static void	display_menu_line(t_core	*core,
				  t_graphic	*this,
				  WINDOW	*local_win,
				  int		i)
{
  int		philo_nb;

  philo_nb = this->first_elem + i;
  wmove(local_win, 1 + i, 1);
  if (i == this->curs)
    wattron(local_win, A_REVERSE);
  wprintw(local_win, "%s ", core->list[philo_nb].name);
  print_state_graphic(core->list[philo_nb].state, local_win);
  if (i == this->curs)
    wattroff(local_win, A_REVERSE);
}

void		menu_box_graphic(t_core *core, t_graphic *this)
{
  int		i;
  WINDOW	*local_win;

  i = 0;
  local_win = newwin(LINES, COLS / 4, 0, 0);
  box(local_win, 0 , 0);
  while (i < LINES - 2 && this->first_elem + i < core->nb_philo)
    {
      display_menu_line(core, this, local_win, i);
      i++;
    }
  wrefresh(local_win);
  delwin(local_win);
}
