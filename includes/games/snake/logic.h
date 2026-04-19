#ifndef LOGIC_SNAKE_H
#define LOGIC_SNAKE_H

#define GRID_WIDTH 16
#define GRID_HEIGHT 16

#define SNAKE_MAX_LEN 40

typedef struct s_vec2
{
	int16_t	v1;
	int16_t	v2;
}	t_vec2;

typedef struct s_snake_state
{
	t_vec2		body[SNAKE_MAX_LEN];
	uint16_t	head;
	uint16_t	length;
	bool		alive;
	t_vec2		direction;
}	t_snake_state;

#endif
