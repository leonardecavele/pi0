#include "helpers/random.h"

static uint32_t	g_random_state = 1u;

extern void	random_seed(uint32_t seed)
{
	g_random_state = seed;
}

extern uint32_t	random_32u(void)
{
	uint32_t i = g_random_state;

	i ^= i << 13;
	i ^= i >> 17;
	i ^= i << 5;
	g_random_state = i;

	return (i);
}
