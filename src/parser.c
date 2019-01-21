/*
** parser.c for parser in /src
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Mar  6 20:43:28 2017 Frederic ODDOU
** Last update Mon Mar 13 02:45:09 2017 Fredoddou
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "philo.h"

static t_param g_param[] = {
  {"-p", &parser_p},
  {"-e", &parser_e}
};

bool		parser_p(t_core *core, int ac, char **av, int *i)
{
  if ((*i + 1) >= ac)
    return (false);
  *i += 1;
  if ((core->nb_philo = atoi(av[*i])) <= 0)
    return (false);
  return (true);
}

bool		parser_e(t_core *core, int ac, char **av, int *i)
{
  if ((*i + 1) >= ac)
    return (false);
  *i += 1;
  if ((core->max_eat = atoi(av[*i])) <= 0)
    return (false);
  return (true);
}

static bool	parser_help(t_core *core)
{
  if (DEBUG_MODE)
    {
      printf("Usage: %s [option(s)]\n", core->name);
      printf("\t-p followed by the number of philosophers. (min. 3)\n");
      printf("\t-e followed by the max eat occurence for a philosopher ");
      printf("before exiting the program. (min. 1)\n");
    }
  return (false);
}

static short	parser_get_fptr(char *str)
{
  short		i;

  i = 0;
  while (i < (short)GET_SIZE(g_param))
    {
      if (!strcmp(str, g_param[i].flag))
	return (i);
      i++;
    }
  return (-1);
}

bool		parser(t_core *core, int ac, char **av)
{
  int		i;
  short		value;

  i = 1;
  if (ac <= 1)
    return (parser_help(core));
  while (i < ac)
    {
      if ((value = parser_get_fptr(av[i])) == -1)
	return (parser_help(core));
      if (!((g_param[value].func)(core, ac, av, &i)))
	return (parser_help(core));
      i++;
    }
  if (core->max_eat < MIN_EAT || core->nb_philo < MIN_PHILO)
    return (parser_help(core));
  return (true);
}
