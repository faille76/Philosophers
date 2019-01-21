/*
** philosophes_utils.c for utils in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Mar 13 02:19:18 2017 Frederic ODDOU
** Last update Mon Mar 13 02:19:18 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <stdio.h>
#include "philo.h"
#include "extern.h"

void	thread_philo_take_chop(t_philo		*philo)
{
  philo->chopstick = CHOP_USE;
  lphilo_take_chopstick(&philo->lock);
}

void	thread_philo_release_chop(t_philo	*philo)
{
  philo->chopstick = CHOP_FREE;
  lphilo_release_chopstick(&philo->lock);
  if (pthread_mutex_unlock(&philo->lock) != 0)
    {
      fprintf(stdout, "pthread_mutex_unlock failed.\n");
      pthread_exit(NULL);
    }
}

void	thread_try_to_lock(t_philo	*philo,
			   t_philo	*philo_right)
{
  int	try1;
  int	try2;

  try1 = try2 = 1;
  while ((try1 = pthread_mutex_trylock(&philo->lock)) != 0 &&
	 (try2 = pthread_mutex_trylock(&philo_right->lock)) != 0)
    {
      if (try1 && !try2)
	{
	  if (pthread_mutex_unlock(&philo_right->lock) != 0)
	    {
	      fprintf(stdout, "pthread_mutex_unlock failed.\n");
	      pthread_exit(NULL);
	    }
	}
      else if (!try1 && try2)
	{
	  if (pthread_mutex_unlock(&philo->lock) != 0)
	    {
	      fprintf(stdout, "pthread_mutex_unlock failed.\n");
	      pthread_exit(NULL);
	    }
	}
    }
}
