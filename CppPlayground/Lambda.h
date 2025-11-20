#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

class Lambda
{
public:
    std::string testLambda()
    {
        std::string s{""};

        std::vector<int> v{ 1,2,3,4,5 };
        int x = 2;
        int y = 5;
        std::vector<int> results;
        std::copy_if(v.begin(), v.end(), std::back_inserter(results), [=](int i) { return i > x && i < y; });

        for (int val : results)
        {
            s += std::to_string(val) + " ";
        }

        if (!results.empty())
            return s;

        return "Nothing found!"; 
    }
};
