// 139. 单词拆分
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// 对于 i 而言，  如果存在 j < i，使得 s[0, j) 可拆分，
// 并且 s[j, i-1) 在 wordDict 中，则 s[0, i)   可拆分。  
bool wordBreak(string s, vector<string>& wordDict)
{
	std::unordered_set<std::string> wordDictSet = std::unordered_set<std::string>();
	
	for (auto word : wordDict)
	{
		wordDictSet.insert(word);
	}

	const int n = s.size();
	std::vector<bool> dp(n + 1, false);
	dp[0] = true;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end())
			{
				dp[i] = true;
				break;
			}
		}
	}
	return dp[n];
}

