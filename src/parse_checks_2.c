/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:46:15 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:56:54 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_empty(char *line);
int		is_valid_char(char c);
int		is_valid_str_clr_cntnt(char *str, char to_find);
int		ft_isspace2(char c);

int	ft_isspace2(char c)
{
	return (c == ' ' || c == '\n');
}

int	is_valid_str_clr_cntnt(char *str, char to_find)
{
	int	i;
	int	commas;
	int	digits;

	i = -1;
	commas = 0;
	digits = 0;
	while (str[++i])
	{
		if (str[i] != to_find && !ft_isspace2(str[i]) && !ft_isdigit(str[i])
			&& str[i] != ',')
			return (0);
		else if (str[i] == ',')
			commas++;
		else if (ft_isdigit(str[i]) && str[i - 1]
			&& !ft_isdigit(str[i - 1]))
			digits++;
	}
	if (commas != 2 || digits > 3)
		return (0);
	return (1);
}

int	is_empty(char *line)
{
	int	i;
	int	not_space;

	i = 0;
	not_space = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			not_space++;
		i++;
	}
	return (not_space == 0);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}
