#include "agent.h"

vector<pair <int,int> > agent::naive_decision(int to_id)
{
	int j, k;
	vector<pair <int, int> > object_coordinate;

	// Naive method: send all objects
	for(j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for(k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if (!public_mem_map[to_id][j][k] && private_mem_map[j][k])
			{
				object_coordinate.push_back(make_pair(j, k));
			}				
		}
	}

	return object_coordinate;
}