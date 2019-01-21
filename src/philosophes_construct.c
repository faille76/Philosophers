/*
** philosophes_construct.c for construct in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Mar 13 02:05:47 2017 Frederic ODDOU
** Last update Tue Mar 14 10:26:39 2017 Fredoddou
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "philo.h"
#include "extern.h"

void	construct_philosophes(t_core	*core)
{
  memset(core, 0, sizeof(t_core));
  g_core = core;
  core->create = &create_philosophes;
  core->parser = &parser;
  core->free = &free_philosophes;
  core->join = &join_philosophes;
  core->take_chop = &thread_philo_take_chop;
  core->release_chop = &thread_philo_release_chop;
  core->philo_rest = &thread_philo_rest;
  core->philo_eat = &thread_philo_eat;
  core->philo_think = &thread_philo_think;
}

static bool	init_philosophes(t_core		*core)
{
  int   	i;

  if ((core->list = calloc(1, sizeof(t_philo) * core->nb_philo)) == NULL)
    {
      perror("Calloc failed.\n");
      return (false);
    }
  srand((unsigned int)((size_t)core));
  i = 0;
  while (i < core->nb_philo)
    {
      core->list[i].id = i;
      core->list[i].state = S_REST;
      core->list[i].name = g_names[rand() % tab_len(g_names)];
      core->list[i].dish = g_repas[rand() % tab_len(g_repas)];
      core->list[i].quote = g_citations[rand() % tab_len(g_citations)];
      pthread_mutex_init(&core->list[i].lock, NULL);
      core->list[i++].chopstick = CHOP_FREE;
    }
  return (true);
}

bool	create_philosophes(t_core	*core)
{
  int   i;
  int	err;

  if (!init_philosophes(core))
    return (false);
  i = 0;
  while (i < core->nb_philo)
    {
      if ((err = pthread_create(&(core->list[i].pthread), NULL, thread_philo,
				(void *)&core->list[i])) != 0)
	{
	  errno = err;
	  perror("pthread_create failed.\n");
	  return (false);
	}
      i++;
    }
  return (true);
}

bool	join_philosophes(t_core		*core)
{
  int	i;
  int	err;

  i = 0;
  while (i < core->nb_philo)
    {
      if ((err = pthread_join(core->list[i++].pthread, NULL)) != 0)
	{
	  errno = err;
	  perror("pthread_join failed.\n");
	  return (false);
	}
    }
  return (true);
}

void	free_philosophes(t_core		*core)
{
  int   i;

  i = 0;
  while (i < core->nb_philo)
    pthread_mutex_destroy(&core->list[i++].lock);
  if (core->list)
    {
      free(core->list);
      core->list = NULL;
    }
}
