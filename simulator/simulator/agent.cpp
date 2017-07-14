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
	k = abs(dest.second-start.second)+abs(dest.first-start.first);
	now.first = start.first;
	now.second = start.second;
	ctx.dest.first = dest.first;
	ctx.dest.second = dest.second;
	id = _id;
}

pair<int,int> agent::move()
{

}