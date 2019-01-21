/*
** content_box_graphic.c for content box in /src/graphic/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Mar 15 01:21:10 2017 Frederic ODDOU
** Last update Wed Mar 15 01:21:10 2017 Frederic ODDOU
*/

#include <ncurses.h>
#include "philo.h"
#include "graphic.h"

void		content_box_graphic(t_core *core, t_graphic *this)
{
  WINDOW	*local_win;
  int		philo_nb;

  philo_nb = this->first_elem + this->curs;
  local_win = newwin(LINES, COLS / 4 * 3 - 2, 0, COLS / 4 + 2);
  box(local_win, 0 , 0);
  wmove(local_win, 1, 1);
  wprintw(local_win, "Name: %s [#%d]", core->list[philo_nb].name, philo_nb);
  wmove(local_win, 2, 1);
  wprintw(local_win, "State: ");
  print_state_graphic(core->list[philo_nb].state, local_win);
  wmove(local_win, 3, 1);
  wattron(local_win, COLOR_PAIR(3));
  wprintw(local_win, "Meditate about: %s", core->list[philo_nb].quote);
  wattroff(local_win, COLOR_PAIR(3));
  wmove(local_win, 5, 1);
  wprintw(local_win, "The philosopher ate %d time(s).",
	  core->list[philo_nb].eat);
  wmove(local_win, 6, 1);
  wprintw(local_win, "%s likes %s.", core->list[philo_nb].name,
	  core->list[philo_nb].dish);
  wmove(local_win, 7, 1);
  wprintw(local_win, "He have to eat at least %d.", core->max_eat);
  wrefresh(local_win);
  delwin(local_win);
}
