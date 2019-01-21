/*
** philo.h for philo in /include
**
** Made by Fredoddou
** Login   <fredoddou>
**
** Started on  Mon Mar  6 19:54:26 2017 Fredoddou
** Last update Wed Mar 15 01:40:36 2017 Fredoddou
*/

#pragma once

#include <stdbool.h>
#include <pthread.h>

#define GET_SIZE(x) 	(sizeof(x) / sizeof(*x))
#define MIN_PHILO	2
#define MIN_EAT		1

/*
** T_REST, T_EAT and T_THINK are the time to execute each section
*/

#define T_REST		0
#define T_EAT		0
#define T_THINK		0
#define T_BREAK		2

/*
** If you wanna display the debug, you must add -D GRAPHIC on the compilation
*/

#ifdef GRAPHIC
# define GRAPHIC_MODE true
#else
# define GRAPHIC_MODE false
#endif

/*
** If you wanna display the debug, you must add -D DEBUG on the compilation
** You can't enable the DEBUG if the GRAPHIC_MODE is enable
*/

#ifdef DEBUG
# define DEBUG_MODE (GRAPHIC_MODE ? false : true)
#else
# define DEBUG_MODE false
#endif

typedef enum    e_state
  {
    S_REST,
    S_EAT,
    S_THINK,
    S_END
  }		t_state;

typedef enum    e_use
  {
    CHOP_FREE	= true,
    CHOP_USE	= false
  }		t_use;

/*
** Contains informations of a philosopher
*/

typedef struct		s_philo
{
  char			*name;
  char			*dish;
  char			*quote;
  pthread_t		pthread;
  pthread_mutex_t	lock;
  t_state		state;
  t_use			chopstick;
  int			id;
  int			eat;
}			t_philo;

/*
** Configuration of the program
*/

typedef struct	s_core
{
  char		*name;
  int		nb_philo;
  int		max_eat;
  bool		finish;
  bool		pause;
  t_philo	*list;
  bool		(*create)(struct s_core *core);
  bool		(*parser)(struct s_core *core, int ac, char **av);
  void		(*free)(struct s_core *core);
  bool		(*join)(struct s_core *core);
  void		(*take_chop)(t_philo *philo);
  void		(*release_chop)(t_philo *philo);
  void		(*philo_think)(struct s_core *core, t_philo *p, t_philo *n);
  void		(*philo_eat)(struct s_core *core, t_philo *p, t_philo *n);
  void		(*philo_rest)(struct s_core *core, t_philo *p, t_philo *n);
}		t_core;

/*
** Useful for the parser, we treat the parameters with an array of fptr
*/

typedef struct	s_param
{
  char		*flag;
  bool		(*func)(t_core *core, int ac, char **av, int *i);
}		t_param;

/*
** parser.c
*/

bool		parser_p(t_core *core, int ac, char **av, int *i);
bool		parser_e(t_core *core, int ac, char **av, int *i);
bool		parser(t_core *core, int ac, char **av);

/*
** philosophes_construct.c
*/

void		construct_philosophes(t_core *core);
bool		create_philosophes(t_core *core);
bool		join_philosophes(t_core *core);
void		free_philosophes(t_core *core);

/*
** philosophes.c
*/

void		*thread_philo(void *arg);
void		thread_philo_take_chop(t_philo *philo);
void		thread_philo_release_chop(t_philo *philo);
void    	thread_philo_rest(t_core	*core,
				  t_philo	*philo,
				  t_philo	*philo_right);

/*
** philosophes_utils.c
*/

void		thread_philo_eat(t_core		*core,
				 t_philo	*philo,
				 t_philo	*philo_right);
void		thread_philo_think(t_core	*core,
				   t_philo	*philo,
				   t_philo	*philo_right);
void		thread_try_to_lock(t_philo	*philo,
				   t_philo	*philo_right);

size_t		tab_len(char **tab);

extern char	*g_names[];
extern char	*g_repas[];
extern char	*g_citations[];
extern t_core	*g_core;
