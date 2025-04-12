#include "cub.h"

int	main(void)
{
	t_cub cub;
	cub.win_res.x = 16 * 100;
	cub.win_res.y = 9 * 100;
	cub.ploc.x = 0;
	cub.ploc.y = 0;
	cub.forwardpress = false;
	cub.backwardpress = false;
	cub.leftpress = false;
	cub.rightpress = false;

	cub.map = malloc(sizeof(char *) * 12);
    cub.map[0] = "001101000100000000100";
    cub.map[1] = "100000000100000100000";
    cub.map[2] = "000000000000000000000";
    cub.map[3] = "100000000100000000000";
    cub.map[4] = "001000010000001000100";
    cub.map[5] = "000000000000000000000";
    cub.map[6] = "000000000000100000000";
	cub.ploc.x = 3;
	cub.ploc.y = 3;
	cub.mheight = 7;
	cub.mwidth = 20;

	initgraph(&cub);
}