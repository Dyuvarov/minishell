/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shellsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:22:45 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/24 12:40:22 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_shellsort(int v[], int n)
{
	int gap;
	int i;
	int j;

	gap = n / 2;
	while (gap > 0)
	{
		i = gap;
		while (i < n)
		{
			j = i - gap;
			while (j >= 0 && v[j] > v[j + gap])
			{
				ft_swap(v, j, j + gap);
				j -= gap;
			}
			i++;
		}
		gap /= 2;
	}
}
