#include "agent.h"
#include "controller.h"
#include "stdlib.h"
#include "time.h"

agent::agent(int _id)
{
	srand((unsigned)time(NULL));
	start.first = rand() % controller.d;
	start.second = rand() % controller.d;
	dest.first = rand() % controller.d;
	dest.second = rand() % controller.d;
	while(dest.first == start.first)
	{
		dest.first = rand() % controller.d;
	}
	while(dest.second == start.second)
	{
		dest.second = rand() % controller.d;
	}
	s = abs(dest.second - start.second) + abs(dest.first - start.first);
	k = (dest.second - start.second) / (dest.first - start.first);
	b = dest.second - k * dest.first;
	current.first = start.first;
	current.second = start.second;
	ctx.dest.first = dest.first;
	ctx.dest.second = dest.second;
	id = _id;
	if(dest.second - start.second > 0 && dest.first - start.first == 0)
	{
		dir.first = 0;
		dir.second = 1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first == 0)
	{
		dir.first = 0;
		dir.second = -1;
	}
	else if(dest.second - start.second == 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = 0;
	}
	else if(dest.second - start.second == 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = 0;
	}
	else if(dest.second - start.second > 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = 1;
	}
	else if(dest.second - start.second > 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = 1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = -1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = -1;
	}
}

pair<int,int> agent::move()
{
	if(dir.first != 0 && dir.second != 0)
	{
		if(current.first == start.first && current.second == start.second & flagx)
		{
			if(dir.first == 1) 
			{
				current.first = current.first + 1;
				return;
			}
			else
			{
				current.first = current.first - 1;
				return;
			}
		}
		else
		{
			if(dir.second == 1)
			{
				current.second = current.second + 1;
				return;
			}
			else
			{
				current.second = current.second - 1;
				return;
			}
		}
	}

	if(dir.first == 0 && dir.second == 1)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 0;
			dir.second = -1;
			swap(start,dest);
		}
	}
	else if(dir.first == 1 && dir.second == 0)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 0;
			swap(start,dest);
		}
	}
	else if(dir.first == 0 && dir.second == -1)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 0;
			dir.second = 1;
			swap(start,dest);
		}
	}
	else if(dir.first == -1 && dir.second == 0)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 0;
			swap(start,dest);
		}
	}
	else if(dir.first == 1 && dir.second == 1 && k * current.first + b > current.second)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = -1;
			swap(start,dest);
			flagx = 0;
		}
	}
	else if(dir.first == 1 && dir.second == 1 && k * current.first + b <= current.second)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = -1;
			swap(start,dest);
			flagx = 1;
		}
	}
	else if(dir.first == 1 && dir.second == -1 && k * current.first + b >= current.second)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 1;
			swap(start,dest);
			flagx = 1;
		}
	}
	else if(dir.first == 1 && dir.second == -1 && k * current.first + b < current.second)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 1;
			swap(start,dest);
			flagx = 0;
		}
	}
	else if(dir.first == -1 && dir.second == 1 && k * current.first + b > current.second)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = -1;
			swap(start,dest);
			flagx = 0;
		}
	}
	else if(dir.first == -1 && dir.second == 1 && k * current.first + b <= current.second)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = -1;
			swap(start,dest);
			flagx = 1;
		}
	}
	else if(dir.first == -1 && dir.second == -1 && k * current.first + b >= current.second)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 1;
			swap(start,dest);
			flagx = 1;
		}
	}
	else if(dir.first == -1 && dir.second == -1 && k * current.first + b < current.second)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 1;
			swap(start,dest);
			flagx = 0;
		}
	}
}