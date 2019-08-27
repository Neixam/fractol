/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 23:09:38 by anboilea          #+#    #+#             */
/*   Updated: 2019/06/07 23:09:45 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		*ft_int_insert(int *tab, int pos, int val, int size)
{
	int i;
	int *ret;
	int j;

	j = 0;
	i = 0;
	if (!(ret = (int *)malloc(sizeof(int) * size + 1)))
		return (NULL);
	while (i < pos)
	{
		ret[i] = tab[i];
		i++;
	}
	j = i;
	ret[i] = val;
	i++;
	while (i <= size)
	{
		ret[i] = tab[j];
		i++;
		j++;
	}
	return (ret);
}
