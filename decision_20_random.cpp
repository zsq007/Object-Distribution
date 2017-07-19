#include "agent.h"

vector<pair <int,int> > agent::_20_random_decision(int to_id)
{
	int j, k;
	vector<pair <int, int> > object_coordinate;
	// Random method: send at most 20 random objects
	vector<pair <int,int> > obj_temp;
	for(j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for(k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if(!public_mem_map[to_id][j][k] && private_mem_map[j][k])
			{
				obj_temp.push_back(make_pair(j,k));
			}
		}
	}
	int i;
	int temp;
	if(obj_temp.size() <= 20)
	{	
		object_coordinate = obj_temp;
	}
	else
	{
		for(i = 0; i < 20; i++)
		{
			temp = rand()%obj_temp.size();
			object_coordinate.push_back(obj_temp[temp]);
			obj_temp.erase(obj_temp.begin()+temp);
		}
	}
	return object_coordinate;
}