#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <sstream>
#include <cctype>
#include <bits/stdc++.h>
using namespace std;

vector<char> genCharvectorBarsFromString(string s)
{
    vector<char> charsVector(s.begin(), s.end());
    vector<char> charsBarVector;
    charsBarVector.push_back('|');
    for(int i = 0; i < charsVector.size(); i++)
    {
        charsBarVector.push_back(toupper(charsVector[i]));
        charsBarVector.push_back('|');
    }
    return charsBarVector;

}

void printCharVector(vector<char>& v)
{
    for(const char &c: v)
    {
        if(c == '\n' || c == '\r') cout << setfill(' ') << setw(2) << '*';
        else cout << setfill(' ') << setw(2) << c;
    }
}

void findLongestPalindrome(vector<char>& s, int& start, int& end)
{
    int centro = 0;
    vector<char> palindrom;
    while (centro < s.size())
    {
        int radio = 0;
        while ((centro-(radio-1)) >= 0 && (centro+(radio+1)) < s.size() && s.at(centro-(radio-1)) == s.at(centro+(radio+1)))
        {
            radio = radio + 1;
        }
        
        centro = centro + 1;

    }
}


int main()
{
    string s = "Loop";
    vector<char> test = genCharvectorBarsFromString(s);
    printCharVector(test);

    int start = 0;
    int end = 0;
    findLongestPalindrome(test, start, end);

    cout << "Longest Palindrome, from " << to_string(start) << " to " << to_string(end) << "." << endl;

    return 0;
}