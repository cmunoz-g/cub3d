/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:09:45 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/12 15:52:30 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TILE_SIZE 30
# define FOV 60

/*	Buttons & Keys	*/
# define CLOSE_BUTTON 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 3
# define MOUSE_BTN 1
# define MOUSE_BTN_2 3
# define KEY_K 107

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	char	**map;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	// int		*floor_color;
	// int		*ceiling_color;
	int		width;
	int		height;	
}				t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	int		rot_dir;
	float	plyr_x;
	float	plyr_y;
	float	fov_rd;
	float	angle;
}			t_player;

typedef struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		is_horizontal;
}			t_ray;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void		*mlx;
	t_img		*img;
	void		*win;
	void		*mlx_p;
	t_map		*map;
	t_ray		*ray;
	t_player	*plyr;
}			t_mlx;

/* init_player */
int		init_player(t_mlx *mlx);
void	display_player(t_player *plyr);

/* utils */
int		free_mlx(t_mlx *mlx);
int		ft_error(char *errormsg, t_mlx *mlx);
double	normalize(double angle);

/* parse_map */
void	parse_map(char *file, t_mlx *mlx);

/* raycasting */
void	cast_rays(t_mlx *mlx);

/* render */
void	render(t_mlx *mlx, int x);

/* clean_init */
void	init_empty_player(t_player *plyr);
void	init_mlx(t_mlx *mlx, char **argv);

/* mlx_loop */
void	start_game(t_mlx *mlx);

#endif