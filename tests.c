/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:10:28 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 13:51:45 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_all(void);
void	test_is_v1_equal_v2(void);

void	test_all(void)
{
	test_is_v1_equal_v2();
}

void	test_is_v1_equal_v2(void)
{
	pthread_mutex_t	lock;
	long			*v1;
	long			*v2;
	bool			result;

	v1 = malloc(sizeof(long));
	v2 = malloc(sizeof(long));
	pthread_mutex_init(&lock, NULL);
	*v1 = 33;
	*v2 = 33;
	result = is_v1_equal_v2(&lock, v1, v2);
	if (result != true)
		printf("Result is %d, instead of %d\n", result, true);
	*v1 = 0;
	*v2 = 55;
	result = is_v1_equal_v2(&lock, v1, v2);
	if (result == true)
		printf("Result is %d, instead of %d\n", result, true);
	free(v1);
	free(v2);
}
