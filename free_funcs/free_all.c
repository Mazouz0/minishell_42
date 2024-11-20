/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:18:45 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:18:46 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ft_free_all(void **ptrs_list, int *s)
{
	int	i;

	i = 0;
	if (!ptrs_list)
		return ;
	while (ptrs_list[i])
	{
		free(ptrs_list[i]);
		ptrs_list[i] = NULL;
		i++;
	}
	(*s) = 0;
	ptrs_list = NULL;
}

void	*ft_malloc(size_t size, int free)
{
	static void	*ptrs_list[INT_MAX];
	static int	i;
	void		*ptr;

	if (free)
	{
		ft_free_all(ptrs_list, &i);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("xmalloc: cannot allocate memory\n", STDERR_FILENO);
		exit(1);
	}
	ptrs_list[i++] = ptr;
	ptrs_list[i] = NULL;
	return (ptr);
}
