/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_tasks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:19:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/04/21 19:12:26 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>

static void	ft_timer(t_philo *philo)
{
	philo->last_meal = ft_gettime();
	philo->start = philo->last_meal;
}

void	*ft_tasks(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_timer(philo);
	if (philo->id % 2 == 0)
		usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		ft_print_action(philo, FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		ft_print_action(philo, FORK);
		ft_print_action(philo, EAT);
		philo->last_meal = ft_gettime();
		philo->meal_count++;
		if (philo->meal_count == philo->data->max_meals)
			philo->data->ate++;
		ft_usleep(philo->data->time_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		ft_print_action(philo, SLEEP);
		ft_usleep(philo->data->time_sleep);
		ft_print_action(philo, THINK);
	}
	return (NULL);
}
