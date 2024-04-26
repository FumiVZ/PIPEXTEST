/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:04:48 by vincent           #+#    #+#             */
/*   Updated: 2024/04/26 10:05:42 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	check_re(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (ft_strlen(s1) == ft_strlen(s2))
		return (1);
	return (0);
}

static void	malloc_infiles(t_pipex *pipex, t_cmd *cmds, int j)
{
	cmds->infiles = malloc(sizeof(int) * j);
	if (!cmds->infiles)
		msg_error(ERR_MALLOC, pipex);
	cmds->infiles_name = malloc(sizeof(char *) * (j + 1));
	if (!cmds->infiles_name)
		msg_error(ERR_MALLOC, pipex);
}

static void	malloc_outfiles(t_pipex *pipex, t_cmd *cmds, int j)
{
	cmds->outfiles = malloc(sizeof(int) * j);
	if (!cmds->outfiles)
		msg_error(ERR_MALLOC, pipex);
	cmds->outfiles_name = malloc(sizeof(char *) * (j + 1));
	if (!cmds->outfiles_name)
		msg_error(ERR_MALLOC, pipex);
}

static void	get_infiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(check_re(cmd[i], "&&") || check_re(cmd[i], "||") || check_re(cmd[i], "|")))
		if (check_re(cmd[i], "<"))
			j++;
	if (j)
	{
		malloc_infiles(pipex, cmds, j);
		i = -1;
		j = 0;
		while (cmd[++i] && !(check_re(cmd[i], "&&") || check_re(cmd[i], "||") || check_re(cmd[i], "|")))
		{
			if (check_re(cmd[i], "<"))
			{
				cmds->infiles_name[j] = ft_strdup(cmd[i + 1]);
				cmds->infiles[j] = open(cmd[i + 1], flags(cmd[i + 1]), 0644);
				if (cmds->infiles[j++] < 0)
					msg_error_outfile(ERR_FILE, *pipex);
			}
			cmds->infiles_name[j] = NULL;
		}
	}
}

static void	get_outfiles(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(check_re(cmd[i], "&&") || check_re(cmd[i], "||") || check_re(cmd[i], "|")))
		if (check_re(cmd[i], ">") || check_re(cmd[i], ">>"))
			j++;
	if (j)
	{
		malloc_outfiles(pipex, cmds, j);
		i = -1;
		j = 0;
		while (cmd[++i] && !(check_re(cmd[i], "&&") || check_re(cmd[i], "||") || check_re(cmd[i], "|")))
		{
			if (check_re(cmd[i], ">") || check_re(cmd[i], ">>"))
			{
				cmds->outfiles_name[j] = ft_strdup(cmd[i + 1]);
				cmds->outfiles[j] = open(cmd[i + 1], flags(cmd[i + 1]), 0644);
				if (cmds->outfiles[j++] < 0)
					msg_error_outfile(ERR_FILE, *pipex);
			}
			cmds->outfiles_name[j] = NULL;
		}
	}
}

char **get_args(t_pipex *pipex, char **cmd)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	while (cmd[i] && (check_re(cmd[i], "<") || check_re(cmd[i], "||") \
		|| check_re(cmd[i], "&&") || check_re(cmd[i], "|")))
		i += 2;
	while (cmd[i + j] && !(check_re(cmd[i + j], "&&") \
		|| check_re(cmd[i + j], "||") || check_re(cmd[i + j], "|") || \
			check_re(cmd[i + j], ">") || check_re(cmd[i + j], ">>") || \
				check_re(cmd[i + j], "<")))
		j++;
	args = malloc(sizeof(char *) * (j + 1));
	if (!args)
		msg_error(ERR_MALLOC, pipex);
	args[j] = NULL;
	while (j--)
		args[j] = cmd[i + j];
	return (args);
}

// Create a struct s_cmd with all command until the end or untile "&&" or "||" each time
// the is a pipe create a new node in the struct s_cmd we can have multiple outfile and infile
void	parse_cmd(t_pipex *pipex, t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;
	
	i = 0;
	if (!cmds)
		msg_error(ERR_MALLOC, pipex);
	list_init(cmds);
	cmds->args = get_args(pipex, &pipex->cmd[i]);
	get_infiles(pipex, &pipex->cmd[i], cmds);
	get_outfiles(pipex, &pipex->cmd[i], cmds);
	cmds->next = NULL;
	while (pipex->cmd[i] && !(check_re(pipex->cmd[i], "&&") || \
		check_re(pipex->cmd[i], "||")) && !check_re(pipex->cmd[i], "|"))
		i++;
	i++;
	while (pipex->cmd[i] && !(check_re(pipex->cmd[i], "&&") || check_re(pipex->cmd[i], "||")))
	{
		while (cmds->next)
			cmds = cmds->next;
		tmp = malloc(sizeof(t_cmd));
		list_init(tmp);
		if (!tmp)
			msg_error(ERR_MALLOC, pipex);
		get_infiles(pipex, &pipex->cmd[i], tmp);
		tmp->args = get_args(pipex, &pipex->cmd[i]);
		get_outfiles(pipex, &pipex->cmd[i], tmp);
		tmp->next = NULL;
		cmds->next = tmp;
		i += ft_strstrlen(tmp->args) + (ft_strstrlen(tmp->infiles_name)  * 2) + (ft_strstrlen(tmp->outfiles_name) * 2);
	}
}
