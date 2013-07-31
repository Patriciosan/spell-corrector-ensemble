//calculates the Frequency of each word from the dictionary file.

#include <iterator>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>

std::string getNextToken(std::istream &in)
{
    char c;
    std::string ans="";
    c=in.get();
    while(!std::isalpha(c) && !in.eof())//cleaning non letter charachters
    {
        c=in.get();
    }
    while(std::isalpha(c))
    {
        ans.push_back(std::tolower(c));
        c=in.get();
    }
    return ans;
}

int main()
{
    std::map<std::string,int> words;
    std::ifstream fin("big.txt");
    std::ofstream fout("out.txt");

    std::string s;
    std::string empty ="";
    while((s=getNextToken(fin))!=empty )
            ++words[s];

    for(std::map<std::string,int>::iterator iter = words.begin(); iter!=words.end(); ++iter)
        fout<<iter->first<<' '<<iter->second<<std::endl;
}
