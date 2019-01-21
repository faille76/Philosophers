/*
** philosophes.c for  in /src/
**
** Made by dabard_k
** Login   <kilian.dabard@epitech.eu@epitech.REN>
**
** Started on  Wed Mar  8 16:53:35 2017 dabard_k
** Last update Sun Mar 19 16:10:38 2017 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"
#include "extern.h"

int			g_philo_nb = -1;

void    thread_philo_rest(t_core	*core,
			  t_philo	*philo,
			  t_philo	*philo_right)
{
  (void)core;
  (void)philo_right;
  lphilo_sleep();
  philo->state = S_REST;
  if (DEBUG_MODE)
    printf("Philosopher #%d is resting.\n", philo->id);
  usleep(T_REST * 1000000);
}

void	thread_philo_eat(t_core		*core,
			 t_philo	*philo,
			 t_philo	*philo_right)
{
  thread_try_to_lock(philo, philo_right);
  core->take_chop(philo);
  core->take_chop(philo_right);
  lphilo_eat();
  philo->state = S_EAT;
  philo->eat++;
  if (DEBUG_MODE)
    printf("Philosopher #%d is eating.\n", philo->id);
  usleep(T_EAT * 1000000);
  core->release_chop(philo);
  core->release_chop(philo_right);

}

void	thread_philo_think(t_core	*core,
			   t_philo	*philo,
			   t_philo	*philo_right)
{
  int	right;

  if (!(right = pthread_mutex_trylock(&philo_right->lock)))
    core->take_chop(philo_right);
  else
    {
      if (pthread_mutex_lock(&philo->lock))
	{
	  fprintf(stdout, "pthread_mutex_lock failed.\n");
	  pthread_exit(NULL);
	}
      core->take_chop(philo);
    }
  lphilo_think();
  philo->state = S_THINK;
  if (DEBUG_MODE)
    printf("Philosopher #%d is thinking.\n", philo->id);
  usleep(T_THINK * 1000000);
  if (!right)
    core->release_chop(philo_right);
  else
    core->release_chop(philo);
}

void		thread_philo_loop(t_core	*core,
				  t_philo	*philo,
				  t_philo	*philo_right)
{
  if (!core->pause)
    {
      if (philo->state == S_THINK)
	core->philo_eat(core, philo, philo_right);
      else if (philo->state == S_REST)
	core->philo_think(core, philo, philo_right);
      else
	core->philo_rest(core, philo, philo_right);
    }
  else
    usleep(2 * 1000000);
}

void		*thread_philo(void	*arg)
{
  t_core	*core;
  t_philo	*philo;
  t_philo       *philo_right;

  core = g_core;
  philo = (t_philo *)arg;
  philo_right = &(core->list[(philo->id + 1) % core->nb_philo]);
  if (DEBUG_MODE)
    printf("Philosopher #%d came to the table.\n", philo->id);
  while (philo->eat < core->max_eat &&
	 !(philo->eat + 1 == core->max_eat && core->finish))
    thread_philo_loop(core, philo, philo_right);
  philo->state = S_END;
  core->finish = true;
  pthread_exit(NULL);
}
