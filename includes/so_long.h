/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:39:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:40:13 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <time.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define MALLOC_ERROR "Malloc error.\n\0"
# define MALLOC_OVEFLOW "Malloc overflow.\n\0"
# define NO_VALID_ARGS_COUNT "Args count is no equal to 2.\n\0"
# define NO_VALID_ARG "Arg don't have .ber extension or dont have a valid path"
# define NO_VALID_MAP "Map is not valid.\n\0"
# define NO_VALID_MAP_LINE_LEN "Map line len is not equal to the first line len"
# define UNKNOW_MAP_SYMBOL "Unknow map symbol.\n\0"
# define MISSING_SYMBOL "There is missing symbols (start, exit or collectible)."
# define NO_VALID_PATH "Map have no valid path.\n\0"
# define MLX_ERROR "A problem has occured when using MLX.\n\0"
# define MLX_IMG_ERROR "A problem has occured when using MLX image.\n\0"
# define MLX_TEXTURE_ERROR "A problem has occured when using MLX texture.\n\0"
# define PLAYER_CREATION_ERROR "A problem has occured when creating player.\n\0"
# define SPRITES_CREATION_ERROR "A problem has occured when creating sprites.\n\0"
# define NPC_CREATION_ERROR "A problem has occured when creating npc.\n\0"

# define MLX_WIN_WIDTH 3860
# define MLX_WIN_HEIGHT 2100
# define MLX_IMG_WIDTH 150

# define PLAYER_SIZE_DIV 10
# define HITBOX_SIZE_DIV 10
# define SHOW_COLLISION_BOX 1

# define SPRITES_FRAME_RATE_PER_SEC 0.01
# define S_HANDGUN_IDLE_PATH "./src/textures/player/handgun/idle/survivor-idle_handgun_"
# define S_HANDGUN_IDLE_COUNT 19
# define S_HANDGUN_WALK_PATH "./src/textures/player/handgun/move/survivor-move_handgun_"
# define S_HANDGUN_WALK_COUNT 19
# define S_HANDGUN_SHOOT_PATH "./src/textures/player/handgun/shoot/survivor-shoot_handgun_"
# define S_HANDGUN_SHOOT_COUNT 2
# define S_HANDGUN_MELEE_PATH "./src/textures/player/handgun/meleeattack/survivor-meleeattack_handgun_"
# define S_HANDGUN_MELEE_COUNT 14

# define PLAYER_HEALTH 300
# define PLAYER_WALK_SPEED 500
# define PLAYER_RUN_SPEED 1000
# define PLAYER_DASH_SPEED 2500
# define PLAYER_DASH_DURATION 10

# define NPC_HEALTH 1
# define NPC_WALK_SPEED 10
# define MPC_RUN_SPEED 20
# define NPC_TICK_BEFORE_MODIFY_MOVEMENT 25
# define NPC_MIN_DELAY_BEFORE_SHOOT 10
# define NPC_MAX_DELAY_BEFORE_SHOOT 150

# define BULLET_TRACE_SLOWNESS 100
# define BULLET_TRACE_VANISHING_TIME 15000
# define BULLET_TRACE_COLOR 0x00FFFFFF

# define BULLET_IMPACT_SLOWNESS 500
# define BULLET_IMPACT_VANISHING_TIME 30000
# define BULLET_IMPACT_LINE_PER_SIDE 4
# define BULLET_IMPACT_LINE_SIZE 50
# define BULLET_IMPACT_COLOR 0x00FFFFFF

# define M_PI 3.14159265358979323846

typedef enum {
	INIT,
	ADD,
	ADD_TEXTURE,
	ADD_IMG,
	DELETE,
	CLEAR,
	DISPLAY,
} t_garbage_action;

typedef enum {
	LEFT,
	RIGHT,
	UPPER,
	BELOW,
} t_direction;

typedef enum s_sprite_types
{
	IDLE,
	WALK,
	SHOOT,
	RELOAD,
	MELEE,
} t_sprite_types;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_check_symbols
{
	int		is_exit_exist;
	int		is_start_exist;
	int		is_collectible_exist;
} t_check_symbols;

typedef struct s_collision
{
	int32_t			x_pivot;
	int32_t			y_pivot;
	int32_t			x_1;
	int32_t			y_1;
	int32_t			x_2;
	int32_t			y_2;
	mlx_image_t		*img;
} t_collision;

typedef struct s_map
{
	char			slot[2];
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*upper;
	struct s_map	*below;
	mlx_image_t		*img;
	mlx_image_t		*overlay;
	int32_t			x;
	int32_t			y;
	bool			on_remove;
} t_map;

typedef struct s_map_info
{
	t_map			*map;
	int				map_width;
	int				map_height;
	pthread_mutex_t	mutex;
} t_map_info;

typedef struct s_sprites
{
	mlx_image_t				*img;
	enum s_sprite_types		type;
	struct s_sprites		*prev;
	struct s_sprites		*next;
} t_sprites;

typedef struct s_player
{
	mlx_t			*mlx;
	t_map			*pos;
	mlx_image_t		*img;
	t_collision		*collision;
	t_sprites		*current_sprites;
	t_sprites		*idle_sprites;
	t_sprites		*walking_sprites;
	t_sprites		*shoot_sprites;
	t_sprites		*reload_sprites;
	t_sprites		*melee_sprites;
	struct s_player	**ennemies;
	pthread_mutex_t	anim_mutex;
	unsigned int	health;
	bool			can_dash;
	bool			on_remove;
	double			x_aiming;
	double			y_aiming;
	int				npc_move_x;
	int				npc_move_y;
	int				npc_move_count;
	int				npc_shoot_delay;
	int				npc_shoot_waited;
} t_player;

typedef struct s_point
{
	int32_t	x;
	int32_t	y;
} t_point;

typedef struct s_param {
		t_player	*player;
		t_point		start;
		t_point		end;
		mlx_image_t	*img;
		mlx_t		*mlx;
		int32_t		x;
		int32_t		y;
		uint32_t	delay;
} t_param;

//# define malloc(size) ft_malloc(size, 1)

ssize_t 	str_ptr_len(char **str);
void		*ft_malloc(size_t size, size_t nmemb);
void		raise_error(char *error, void *ptr);
void		garbage_collector(t_garbage_action action, void *ptr);
void		check_args(int argc, char **argv);
char		*ft_strjoin_enhanced(char *s1, char *s2);
char		*get_full_path(char *filename);
int			is_valid_symbol(char symbol[2]);
int			is_wall_valid(t_map *map);
int			is_char_missing(t_map *map, t_map *tmp);
int			is_valid_path_exist(t_map *map);

t_map_info	*map_parsing(char *filename);
t_map		*map_new(char slot[2]);
t_map		*copy_map(t_map *map);
t_map		*get_start_pos(t_map *map);
t_map		**find_symbols(t_map *map, char c);
int 		*get_map_len(t_map *map);
void		map_add_right(t_map **map, t_map *new);
void		map_add_below(t_map **map, t_map *new);
void		map_link_lines(t_map *first_line, t_map *second_line);
void		apply_func_on_map(t_map *map, void (*f)(t_map *map, mlx_t *mlx, int width, int height));
void		display_map(t_map *map, int display_link);
int			random_in_range(int range);

void		start_mlx(t_map_info *map_info);
void		close_mlx(void *mlx);
void		init_mlx_hooks(mlx_t *mlx, t_map_info *map_info);
void		ft_key_hook(mlx_key_data_t keydata, void* param);

t_player	*init_player(mlx_t *mlx, t_map_info *map);
t_map		*find_player_pos(t_map *map);
t_sprites	*create_animation_chain(t_player *player, t_map_info *map, bool is_loop, char *sprites_path);
bool		predict_player_pos(t_player	*player, int x, int y, int speed);
void		create_player_collision(t_player *player, t_map_info *map);

void		player_movement(void *param);
void		player_animation(void *param);
void		player_aiming(double x, double y, void *param);
void		set_animation(t_player *player, t_sprites *sprites, bool force);
void		remove_animation(t_player *player, t_sprites *sprites);
void		on_mouse_action(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void		shoot_bullet(t_player *player);
void		raycast(t_player *player, t_point start, t_point end, mlx_image_t *img);
mlx_image_t	*img_sharing(mlx_image_t *img);

void		init_all_npcs(mlx_t *mlx, t_map_info *map, t_player *player);
void		npc_movement(void *param);
void		npc_shooter(void *param);

void		kill_entity(t_player *ent, t_player *killer);
#endif
