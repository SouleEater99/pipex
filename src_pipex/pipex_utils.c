/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:05:42 by ael-maim          #+#    #+#             */
/*   Updated: 2024/03/28 22:42:55 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_get_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*new_cmd;

	while (*cmd == ' ')
		cmd++;
	if (ft_check_path(cmd))
		return (ft_strdup(cmd));
	while (cmd[i] && cmd[i] != ' ')
		if (cmd[i++] == '/')
			j = i;
	if ((ft_strlen_delimiter(cmd + j, ' ') + 1) == 1)
		return (NULL);
	new_cmd = malloc(ft_strlen_delimiter(cmd + j, ' ') + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[j] && cmd[j] != ' ')
		new_cmd[i++] = cmd[j++];
	new_cmd[i] = '\0';
	return (new_cmd);
}

size_t	ft_strlen_delimiter(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_path(char const *s1, char const *s2, char c)
{
	size_t	i;
	size_t	s1_len;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1) + 1;
	d = (char *)malloc(s1_len + ft_strlen_delimiter(s2, ' ') + 1);
	if (d == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		d[i] = s1[i];
	d[i] = c;
	i = 0;
	while (s2[i] && s2[i] != ' ')
	{
		d[s1_len + i] = s2[i];
		i++;
	}
	d[s1_len + i] = '\0';
	return (d);
}

int	ft_check_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != ' ')
		if (cmd[i++] == '/')
			return (0);
	return (1);
}

char	*ft_get_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	**tab;

	while (cmd && *cmd == ' ')
		cmd++;
	i = 0;
	if (ft_check_path(cmd) == 0)
		return (ft_strdup(cmd));
	while (envp[i] && (ft_strnstr(envp[i], "PATH=", 6) == NULL))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	tab = ft_split(envp[i] + 6, ':');
	i = 0;
	while (tab[i])
	{
		path = ft_strjoin_path(tab[i], cmd, '/');
		if (access(path, X_OK) == 0)
			return (ft_free_tab(tab), path);
		free(path);
		i++;
	}
	return (ft_free_tab(tab), NULL);
}
