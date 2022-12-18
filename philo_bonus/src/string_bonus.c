/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:49:01 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 19:55:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;
	int		size;

	size = ft_strlen(s);
	dup = (char *) malloc(sizeof(char) * (size + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls1;
	size_t	ls2;
	char	*s;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	s = (char *) malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (s == NULL)
		return (NULL);
	i = -1;
	while (++i < ls1)
		s[i] = s1[i];
	i = -1;
	while (++i < ls2)
		s[i + ls1] = s2[i];
	s[i + ls1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	size_t	i;
	int		nsave;
	char	s[12];

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	nsave = n;
	if (n < 0)
		n = n * -1;
	s[11] = '\0';
	i = 11;
	while (n != 0)
	{
		i--;
		s[i] = (n % 10) + '0';
		n = n / 10;
	}
	if (nsave < 0)
	{
		i--;
		s[i] = '-';
	}
	return (ft_strdup(&s[i]));
}
