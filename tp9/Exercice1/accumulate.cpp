#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>

std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::toupper(c); } // correct
                  );
    return s;
}

std::string concat_in_caps(const std::vector<std::string>& words)
{
    const auto res = std::accumulate(words.begin(), words.end(), std::string(), 
    [](const auto& v1, const auto& v2){return v1 + str_toupper(v2);});
    return res;
}

int main()
{
    std::vector<std::string> words { "ARRETE", "De", "criEr", "steuplAIt" };
    std::cout << concat_in_caps(words) << std::endl;
    return 0;
}

