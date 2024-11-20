/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 03:07:19 by zqouri            #+#    #+#             */
/*   Updated: 2024/11/03 12:56:44 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_(const char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	dup = (char *)gb_malloc(sizeof(char) * (ft_strlen(s) + 1), 0);
	if (!dup)
		return (NULL);
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr_(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*dest;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	size = ft_strlen(s);
	i = 0;
	if (len == 0 || start >= size)
		return (ft_strdup_(""));
	if (len > size - start)
		len = size - start;
	dest = (char *)gb_malloc(sizeof(char) * (len + 1), 0);
	if (!dest)
		return (NULL);
	while (i < len && ptr[start])
		dest[i++] = ptr[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup_(s2));
	if (!s2 && s1)
		return (ft_strdup_(s1));
	i = 0;
	j = 0;
	dest = gb_malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1), 0);
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

void	ft_lst_clear_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}
