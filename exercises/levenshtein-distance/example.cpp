#include "levenshtein_distance.h"

#include <vector>
#include <algorithm>

int levenshtein::distance(const std::string& source, const std::string& target)
{
	std::vector<std::vector<int>> table(source.size() + 1
		, std::vector<int>(target.size() + 1, 0));
	
	for (size_t i = 0; i<source.size() + 1; i++) 
	{
		table[i][0] = i;
	}

	for (size_t j = 0; j<target.size() + 1; j++)
	{
		table[0][j] = j;
	}

	for (size_t i = 1; i<source.size() + 1; i++)
	{
		for (size_t j = 1; j<target.size() + 1; j++)
		{
			if (source.at(i - 1) == target.at(j - 1)) 
			{
				table[i][j] = table[i - 1][j - 1];
			}
			else 
			{
				table[i][j] = std::min(table[i - 1][j], table[i - 1][j - 1]);
				table[i][j] = std::min(table[i][j], table[i][j - 1]);
				table[i][j] += 1;
			}
		}
	}

	return table[source.size()][target.size()];
}
