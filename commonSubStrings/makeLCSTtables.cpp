#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <sstream>
using namespace std;

void printStringMatrix(vector<vector<string>>& vectorStrings)
{
    int m = vectorStrings.size();
    int n = vectorStrings[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << vectorStrings[i][j] << ' ';
        }
        cout << endl;
    }
}

void printIntMatrix(vector<vector<int>>& vectorInt)
{
    int m = vectorInt.size();
    int n = vectorInt[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << vectorInt[i][j] << ' ';
        }
        cout << endl;
    }
}

void makeLCSTables(string x, string y, vector<vector<string>>& B, vector<vector<int>>& C)
{
    int m = x.length();
    int n = y.length();

    for (int i = 0; i <= m; i++)
    {
        vector<int> rowC(n + 1, 0);
        C.push_back(rowC);
        
        vector<string> rowB(n+1,"*");
        B.push_back(rowB);
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i-1] == y[j-1])
            {
                C[i][j] = C [i - 1][j - 1] + 1;
                B[i][j] = "D";
            }
            else
            {
                if (C[i - 1][j] > C[i][j -1])
                {
                    C[i][j] = C[i - 1][j];
                    B[i][j] = "U";
                }
                else
                {
                    C[i][j] = C[i -1][j];
                    B[i][j] = "L";
                }
                
            }
        }
    }
}

void printLCS(vector<vector<string>> B, string X, int i, int j)
{
    if(i == 0 || j == 0) return;
    if (B[i][j].compare("B") == 0)
    {
        printLCS(B, X, i - 1, j - 1);
        cout << X[i - 1];
    }
    else if (B[i][j].compare("U") == 0)
    {
        printLCS(B, X, i - 1, j);
    }
    else
    {
        printLCS(B, X, i, j-1);
    }
    
}


void searchIndex(vector<vector<string> > B, int first, int last)
{
    for (int i = 0; i <= first; i++)
    {
        for (int i = 0; i < last; i++)
        {
            
        }
        
    }
    
}


int main()
{
    string s1 = "THEGREENPRAIRE";
    string s2 = "TOMTHEGREENALIEN";
    vector<vector<string> > B;
    vector<vector<int> > C;
    makeLCSTables(s1, s2, B, C);
    printStringMatrix(B);
    cout << endl;
    cout << endl;
    printIntMatrix(C);
    cout << endl;
    cout << endl;
    printLCS(B, s1, s1.length(),s2.length());
    return 0;
}