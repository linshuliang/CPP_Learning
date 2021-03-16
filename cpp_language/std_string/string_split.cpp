#include <iostream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

vector<string> testSplit(const string& in, const string& delim)
{
    vector<string> ret;
    try
    {
        regex re{ delim };
        return vector<string>{
            sregex_token_iterator(in.begin(), in.end(), re, -1),
                sregex_token_iterator()
        };
    }
    catch (const std::exception& e)
    {
        cout << "error:" << e.what() << std::endl;
    }
    return ret;
}

int main()
{
    string fileNmae = "14_30_25_906.bmp";
    fileNmae = fileNmae.substr(0, fileNmae.find(".bmp"));

    vector<string> ret = testSplit(fileNmae, "_");
    for (int i = 0; i < ret.size(); ++i)
    {
        cout << ret[i] << endl;
    }

    return 0;
}