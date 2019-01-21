/*
** core_graphic.c for core in /src/graphic/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue Mar 14 23:17:00 2017 Frederic ODDOU
** Last update Tue Mar 14 23:17:00 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <ncurses.h>
#include "philo.h"
#include "graphic.h"

static bool	if_is_finish_graphic(t_core *core)
{
  int		i;

  i = 0;
  while (i < core->nb_philo)
    {
      if (core->list[i].state != S_END)
	return (false);
      i++;
    }
  return (true);
}

void		print_state_graphic(t_state state, WINDOW *local_win)
{
  if (state == S_REST)
    {
      wattron(local_win, COLOR_PAIR(6));
      wprintw(local_win, "[REST]");
      wattroff(local_win, COLOR_PAIR(6));
    }
  else if (state == S_EAT)
    {
      wattron(local_win, COLOR_PAIR(2));
      wprintw(local_win, "[EAT]");
      wattroff(local_win, COLOR_PAIR(2));
    }
  else if (state == S_THINK)
    {
      wattron(local_win, COLOR_PAIR(3));
      wprintw(local_win, "[THINK]");
      wattroff(local_win, COLOR_PAIR(3));
    }
  else if (state == S_END)
    {
      wattron(local_win, COLOR_PAIR(1));
      wprintw(local_win, "[END]");
      wattroff(local_win, COLOR_PAIR(1));
    }
}

void		reset_graphic(t_core *core, t_graphic *this)
{
  erase();
  if (this->curs + this->first_elem >= core->nb_philo)
    this->curs--;
  if (this->curs < 0)
    {
      if (this->first_elem > 0)
	this->first_elem--;
      this->curs = 0;
    }
  if (this->curs >= LINES - 2)
    {
      this->first_elem++;
      this->curs = LINES - 3;
    }
  if (LINES - 2 >= core->nb_philo)
    this->first_elem = 0;

}

bool		key_control_graphic(t_core *core, t_graphic *this)
{
  int		c;

  c = getch();
  if (c == KEY_UP)
    this->curs--;
  if (c == KEY_DOWN)
    this->curs++;
  if (c == 'q' || c == KEY_EXIT)
    return (false);
  if (c == 'p')
    core->pause = core->pause ? false : true;
  return (true);
}

bool		core_graphic(t_core *core)
{
  bool		works;
  t_graphic	this;

  works = true;
  construct_graphic(&this);
  if (!this.create(&this))
    return (false);
  while (works && !if_is_finish_graphic(core))
    {
      works = this.keycontrol(core, &this);
      this.reset(core, &this);
      this.menu_box(core, &this);
      this.content_box(core, &this);
      usleep(0.1 * 1000000);
    }
  this.destroy(&this);
  return (true);
}
