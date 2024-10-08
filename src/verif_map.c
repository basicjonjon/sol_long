/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-doua <jle-doua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:48:10 by jle-doua          #+#    #+#             */
/*   Updated: 2024/10/07 13:42:10 by jle-doua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	verif_validity_map(t_game game)
{
	int	verif;

	verif = 0;
	if (game.map_x < 5 || game.map_y < 3)
	{
		printf("%sERROR : map is to small\n%s", RED, NC);
		verif++;
	}
	if (verif_count_p_e_c(&game))
	{
		printf("%sERROR : no player, exit or collectible\n%s", RED, NC);
		verif++;
	}
	if (verif_shape(game))
	{
		printf("%sERROR : map is not rectangular\n%s", RED, NC);
		verif++;
	}
	if (verif_border(game))
	{
		printf("%sERROR : map border have problem\n%s", RED, NC);
		verif++;
	}
	verif_finishable(&game, game.player.plyr_x, game.player.plyr_y);
	if (game.verif.exit == 0 || game.verif.collectible != game.nb_collectible)
	{
		printf("%sERROR : map is not finishable\n%s", RED, NC);
		verif++;
	}
	ft_free_bidimentionnal((void **)game.verif.map);
	if (verif != 0)
		return (1);
	printf("%s[ MAP OK ]%s\n", GREEN, NC);
	return (0);
}

int	verif_border(t_game game)
{
	int	i;

	i = 0;
	while (i < game.map_x)
	{
		if (game.map[0][i] != '1' || game.map[game.map_y - 1][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < game.map_y)
	{
		if (game.map[i][0] != '1' || game.map[i][game.map_x - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	verif_count_p_e_c(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
				game->nb_player++;
			else if (game->map[y][x] == 'E')
				game->nb_exit++;
			else if (game->map[y][x] == 'C')
				game->nb_collectible++;
			x++;
		}
		y++;
	}
	if (game->nb_player != 1 || game->nb_exit != 1 || game->nb_collectible == 0)
		return (1);
	return (0);
}

int	verif_shape(t_game game)
{
	size_t	ref;
	int		y;

	y = 1;
	ref = ft_strlennojl(game.map[0]);
	while (y < game.map_y)
	{
		if (ft_strlennojl(game.map[y]) != ref)
			return (1);
		y++;
	}
	return (0);
}

int	verif_finishable(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	if (game->verif.map[y][x] == 'E')
		game->verif.exit = 1;
	else if (game->verif.map[y][x] == 'C')
		game->verif.collectible++;
	game->verif.map[y][x] = '2';
	while (++i <= 5)
	{
		if (i == 1 && (y + 1 < game->map_y) && game->verif.map[y + 1][x] != '1'
			&& game->verif.map[y + 1][x] != '2')
			verif_finishable(game, x, y + 1);
		else if (i == 2 && (x + 1 < game->map_x) && game->verif.map[y][x
			+ 1] != '1' && game->verif.map[y][x + 1] != '2')
			verif_finishable(game, x + 1, y);
		else if (i == 3 && (y - 1 >= 0) && game->verif.map[y - 1][x] != '1'
			&& game->verif.map[y - 1][x] != '2')
			verif_finishable(game, x, y - 1);
		else if (i == 4 && (x - 1 >= 0) && game->verif.map[y][x - 1] != '1'
			&& game->verif.map[y][x - 1] != '2')
			verif_finishable(game, x - 1, y);
	}
	return (0);
}
