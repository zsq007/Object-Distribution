#include "agent.h"
#include "controller.h"
#include "stdlib.h"
#include "time.h"

agent::agent()
{
	srand((unsigned)time(NULL));
	start_x = rand() % controller.d;
	start_y = rand() % controller.d;
	ctx.x = start_x;
	ctx.y = start_y;

	//randomly generate orbit
	k = rand() % controller.d + (controller.d / 10);
	int i,j;
	bool flagx = rand() % 2;
	switch(rand()%4)
	{
	case 0:			//right & up
		{
			for (i = 0; i < k; i++)
			{
				if((rand() % 100 <= 80 && ctx.x < controller.d && (flagx || ctx.y >= controller.d)) || 
					(rand() % 100 >80 && ctx.x < controller.d && (!flagx || ctx.y >= controller.d))) 
						ctx.x = ctx.x + 1;
				else if (ctx.x >= controller.d && ctx.y >= controller.d) break;
				else {
					ctx.y = ctx.y + 1;
					flagx = !flagx;
				}
			}
			break;
		}
	case 1:			//right & down
		{
			for (i = 0; i < k; i++)
			{
				if((rand() % 100 <= 80 && ctx.x < controller.d && (flagx || ctx.y <= 0)) || 
					(rand() % 100 >80 && ctx.x < controller.d && (!flagx || ctx.y <= 0))) 
						ctx.x = ctx.x + 1;
				else if (ctx.x >= controller.d && ctx.y <= 0) break;
				else {
					ctx.y = ctx.y - 1;
					flagx = !flagx;
				}
			}
			break;
		}
	case 2:			//left & up
		{
			for (i = 0; i < k; i++)
			{
				if((rand() % 100 <= 80 && ctx.x > 0 && (flagx || ctx.y >= controller.d)) || 
					(rand() % 100 >80 && ctx.x > 0 && (!flagx || ctx.y >= controller.d))) 
						ctx.x = ctx.x - 1;
				else if (ctx.x <= 0 && ctx.y >= controller.d) break;
				else {
					ctx.y = ctx.y + 1;
					flagx = !flagx;
				}
			}
			break;
		}
	case 3:			//left & down
		{
			for (i = 0; i < k; i++)
			{
				if((rand() % 100 <= 80 && ctx.x > 0 && (flagx || ctx.y <= 0)) || 
					(rand() % 100 >80 && ctx.x > 0 && (!flagx || ctx.y <= 0))) 
						ctx.x = ctx.x - 1;
				else if (ctx.x <= 0 && ctx.y <= 0) break;
				else {
					ctx.y = ctx.y - 1;
					flagx = !flagx;
				}
			}
			break;
		}
	}

	ctx.n = 0;
}
