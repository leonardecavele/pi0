#ifndef LOGIC_SNAKE_H
#define LOGIC_SNAKE_H

#define GRID_WIDTH 16
#define GRID_HEIGHT 16

#define SNAKE_MAX_LEN 40

typedef struct s_pos
{
	uint16_t	x;
	uint16_t	y;
}	t_pos;

typedef struct s_snake_state
{
	t_pos	body[SNAKE_MAX_LEN];
}	t_snake_state;

#endif
