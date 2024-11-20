/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utilis_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:21:43 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:21:44 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

void	close_fd(int fd_in, int fd_out)
{
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
}

char	*ft_strtrim_(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*new_str;

	i = 0;
	j = ft_strlen(str) - 1;
	if (!str)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (j >= i && (str[j] == ' ' || str[j] == '\t'))
		j--;
	new_str = (char *)ft_malloc(j - i + 2, 0);
	k = 0;
	while (i <= j)
		new_str[k++] = str[i++];
	new_str[k] = '\0';
	return (new_str);
}
