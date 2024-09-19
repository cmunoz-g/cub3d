/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:28:43 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/19 13:22:51 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_empty(char *line);

int	check_file_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (ft_strncmp((file + i - 4), ".cub", 4))
		return (1);
	else
		return (0);
}

void	free_arr(char **arr)
{
	int	pos;

	if (!arr)
		return ;
	pos = -1;
	while (arr[++pos])
		free(arr[pos]);
	free(arr);
}

void	ft_arrdup(char **dst, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}

int	get_line_nbr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**append_str(char **map, char *buf)
{
	char	**new_map;
	int		line_nbr;

	line_nbr = get_line_nbr(map);
	new_map = ft_calloc(sizeof(char *), line_nbr + 2);
	if (!(*map))
	{
		new_map[0] = ft_strdup(buf);
		new_map[1] = NULL;
	}
	else
	{
		ft_arrdup(new_map, map);
		new_map[line_nbr] = ft_strdup(buf);
		new_map[line_nbr + 1] = NULL;
	}
	free_arr(map);
	return (new_map);
}

char	**get_file_contents(int fd)
{
	char	**map;
	char	*buf;

	buf = get_next_line(fd);
	if (!buf)
		return (NULL);
	map = ft_calloc(sizeof(char *), 1);
	map[0] = NULL;
	while (buf)
	{
		map = append_str(map, buf);
		free(buf);
		buf = get_next_line(fd);
	}
	free(buf);
	return (map);
}

char	*get_text(char **read, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (read[i])
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i] + j, to_find, ft_strlen(to_find)) == 0)
			return (read[i] + j);
		i++;
	}
	return (NULL);
}

int	*get_rgb_int_arr(char *line)
{
	int		*rgb;
	char	*hold;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rgb = ft_calloc(sizeof(int), 3);
	if (!rgb)
		return (NULL);
	while (j < 3)
	{
		while (*line && !(*line >= 48 && *line <= 57))
			line++;
		while (line[i] && (line[i] >= 48 && line[i] <= 57))
			i++;
		hold = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(hold, line, i + 1);
		rgb[j] = ft_atoi(hold);
		if (rgb[j] < 0 || rgb[j] > 255 || is_empty(hold))
			return (free(rgb), free(hold), NULL);
		free(hold);
		line += i;
		i = 0;
		j++;
	}
	return (rgb);
}

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

int	*get_color_parse(char **read, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	while (read[i])
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i] + j, to_find, ft_strlen(to_find)) == 0
			&& is_valid_str_clr_cntnt(read[i] + j, to_find[0]))
			return (get_rgb_int_arr(read[i] + j));
		i++;
	}
	return (NULL);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

bool	is_empty(char *line)
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

char	**get_map(char **read)
{
	char	**clean_map;
	int		lines_in_file;
	int		tex_lines;
	int		blank_lines;

	lines_in_file = ft_arrlen(read);
	tex_lines = 0;
	blank_lines = 0;
	while (*read && tex_lines != 6)
	{
		if (is_empty(*read))
			blank_lines++;
		else
			tex_lines++;
		read++;
	}
	while (*read && is_empty(*read))
	{
		read++;
		blank_lines++;
	}
	clean_map = ft_calloc(sizeof(char *),
			(lines_in_file - tex_lines - blank_lines + 1));
	if (!clean_map)
		return (NULL);
	ft_arrdup(clean_map, read);
	return (clean_map);
}

char	*trim_path(char *path, char *prefix)
{
	char	*new_path;
	char	*helper;
	char	*ref;		

	if (!path)
		return (NULL);
	while (ft_isspace2(*path))
		path++;
	helper = ft_strtrim(path, "\n");
	ref = helper;
	while (*helper == *prefix)
	{
		helper++;
		prefix++;
	}
	while (ft_isspace2(*helper))
		helper++;
	new_path = ft_strtrim(helper, " ");
	return (free(ref), new_path);
}

t_map	*fill_map_info(t_mlx *mlx, char **read)
{
	t_map	*ret;

	ret = ft_calloc(sizeof(t_map), 1);
	ret->no_path = trim_path(get_text(read, "NO "), "NO");
	ret->so_path = trim_path(get_text(read, "SO "), "SO");
	ret->we_path = trim_path(get_text(read, "WE "), "WE");
	ret->ea_path = trim_path(get_text(read, "EA "), "EA");
	if (!ret->no_path || !ret->so_path || !ret->ea_path || !ret->we_path)
		ft_error("Texture paths are incorrect", mlx);
	ret->floor_color = get_color_parse(read, "F ");
	ret->ceiling_color = get_color_parse(read, "C ");
	if (!ret->floor_color || !ret->ceiling_color)
		ft_error("Colors are incorrect", mlx);
	ret->map = get_map(read);
	free_arr(read);
	return (ret);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	check_spaces(char c)
{
	(void)c;
	return (0);
}

int	check_row(char *line)
{
	char	tmp;

	while (*line && *line == ' ')
		line++;
	if (*line && *line != '1')
		return (1);
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			tmp = *line;
		line++;
	}
	if (tmp != '1')
		return (1);
	return (0);
}

int	get_width(char **map)
{
	int	max_row_len;
	int	current_row;
	int	current_row_len;

	max_row_len = 0;
	current_row = 0;
	while (map[current_row])
	{
		current_row_len = ft_strlen(map[current_row]);
		if (current_row_len > max_row_len)
			max_row_len = current_row_len;
		current_row++;
	}
	return (max_row_len);
}

void	check_valid_map(t_map *map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	map->height = get_line_nbr(map->map);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] && map->map[i][j] != '\n')
		{
			if ((i == 0 || i == map->height - 1
					|| check_spaces(map->map[i][j])) && map->map[i][j] != '1')
				ft_error("Map is not enclosed.", mlx);
			else if (!is_valid_char(map->map[i][j]))
				ft_error("Wrong Character.", mlx);
			else if (check_row(map->map[i]))
				ft_error("Issue reading map.", mlx);
			j++;
		}
		i++;
	}
	map->width = get_width(map->map);
}

void	replace_spaces_with_ones(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	check_zeros_out_of_bounds(char **map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && map[i - 1]
			&& map[i + 1])
			{
				if (!map[i - 1][j] || !map[i + 1][j])
					ft_error("Map not enclosed.", mlx);
			}
			j++;
		}
		i++;
	}
}

void	check_map_is_together(char **map, t_mlx *mlx)
{
	int	i;
	int	last_empty;

	i = 0;
	last_empty = 0;
	while (map[i])
	{
		if (is_empty(map[i]))
			last_empty = 1;
		if (!is_empty(map[i]) && last_empty)
			ft_error("Map is not together.", mlx);
		i++;
	}
}

void	parse_map(char *file, t_mlx *mlx)
{
	int		fd;
	char	**read;

	fd = open(file, O_RDONLY);
	if (fd < 0 || check_file_extension(file))
		(printf("Issue with the file"), exit(1));
	read = get_file_contents(fd);
	if (!read)
		(printf("Empty map"), exit(1));
	mlx->map = fill_map_info(mlx, read);
	check_valid_map(mlx->map, mlx);
	replace_spaces_with_ones(mlx->map);
	check_zeros_out_of_bounds(mlx->map->map, mlx);
	check_map_is_together(mlx->map->map, mlx);
}
