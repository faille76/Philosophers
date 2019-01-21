/*
** main.c for main in /src
**
** Made by Fredoddou
** Login   <fredoddou>
**
** Started on  Mon Mar  6 19:54:39 2017 Fredoddou
** Last update Mon Mar 13 02:44:33 2017 Fredoddou
*/

#include <stdlib.h>
#include "philo.h"
#include "graphic.h"
#include "extern.h"

t_core		*g_core = NULL;

int		main(int ac, char **av)
{
  t_core	core;

  construct_philosophes(&core);
  core.name = av[0];
  if (!core.parser(&core, ac, av))
    return (EXIT_FAILURE);
  RCFStartup(ac, av);
  if (!core.create(&core))
    return (EXIT_FAILURE);
  if (GRAPHIC_MODE)
    core_graphic(&core);
  if (!core.join(&core))
    {
      core.free(&core);
      return (EXIT_FAILURE);
    }
  core.free(&core);
  RCFCleanup();
  return (EXIT_SUCCESS);
}
