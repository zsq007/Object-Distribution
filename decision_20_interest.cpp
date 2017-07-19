#include "agent.h"

vector<pair <int,int> > agent::_20_interest_decision(int to_id)
{
	int i, j, k;
	int temp_rand, round_left;
	vector<pair <int, int> > temp_object_coordinate, object_coordinate;

	// 20 objects send to each agent, judging by the Interest table
	for (j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for (k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if (!public_mem_map[to_id][j][k] & private_mem_map[j][k])
			{
				temp_object_coordinate.push_back(make_pair(j, k));
			}
		}
	}

	if (temp_object_coordinate.size() < 20)
		return temp_object_coordinate;

	for (i = 0; i < temp_object_coordinate.size(); i++)
	{
		if (I[to_id][temp_object_coordinate[i].first][temp_object_coordinate[i].second])
		{
			object_coordinate.push_back(temp_object_coordinate[i]);

			if (object_coordinate.size() >= 20)
				return object_coordinate;

			temp_object_coordinate.erase(temp_object_coordinate.begin() + i);
			i--;
		}
	}

	round_left = 20 - object_coordinate.size();
	
	for (i = 0; i < round_left; i++)
	{
		temp_rand = rand() % temp_object_coordinate.size();
		object_coordinate.push_back(temp_object_coordinate[temp_rand]);

		if (object_coordinate.size() >= 20)
			return object_coordinate;

		temp_object_coordinate.erase(temp_object_coordinate.begin() + temp_rand);
	}
}