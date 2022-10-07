// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937


#ifndef actIntegradora_H_included
#define actIntegradora_H_included

#include <iostream>
#include <vector>
#include <streambuf>
#include <iterator>
#include <fstream>
#include <chrono>
using namespace std;

class actIntegradora{
    public:
    
        static vector<char> genCharVectorFromString(string s)
        {
            vector<char> charsVector(s.begin(), s.end());
            return charsVector;
        }

        static vector<char> genCharVectorFromFile(string filename)
        {
            ifstream t(filename);
            string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());


            return genCharVectorFromString(str);
        }

        static string genStringFromFile(string filename)
                {
                    ifstream t(filename);
                    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());


                    return str;
                }

        static void printCharVector(vector<char>& v)
        {
            for(int i = 0; i < v.size(); i++) 
            {
                cout << v[i] << " ";
            }
            cout << endl;
        }
        
        //O(n)
        static vector<int> computeLPPS(vector<char>& pattern)
        {
            auto start1 = std::chrono::high_resolution_clock::now();
            int i = 0;
            int j = 1;
            int counter = 0;
            vector<int> lpps(pattern.size());
            lpps.at(0) = 0;

            while(j < pattern.size())
            {
                if(pattern[i] == pattern[j])
                {
                    i++;
                    lpps.at(j) = i;
                    j++;
                }
                else{
                    if(i == 0)
                    {
                        lpps.at(0);
                        j++;
                    }else
                    {
                        i = lpps.at(i-1);
                    }
                }
                
            }

            auto stop1 = std::chrono::high_resolution_clock::now();

            auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
            cout << "Tiempo de procesamiento de la tabla lpps: " << to_string(duration1.count()) << " microseconds" << endl;

            return lpps;
            
        }

        // O(n+n)
        static vector<int> KMP(vector<char> pattern,vector<char> text){
            int n = text.size();
            int m = pattern.size();
            vector<int> result;
            vector<int> Lps = computeLPPS(pattern);
            
            int i=0,j=0;
            while(i<n){
                if(pattern[j]==text[i]){i++;j++;} 
                if (j == m) { 
                    //cout<<i - m <<' '; 
                    result.push_back(i-m);   
                                        
                    j = Lps[j - 1]; 
                } 
                else if (i < n && pattern[j] != text[i]) {  
                    if (j == 0)          
                        i++;
                    else
                        j = Lps[j - 1];  
                }
            }
            return result;
        }

        // O(n^3n)
        static void longestPalSubstr(string str, int& start, int& end)
        {
            int n = str.size(); 
            int low, high;
            for (int i = 0; i < n; i++) {
                low = i - 1;
                high = i + 1;
                while (high < n
                    && str[high] == str[i]) 
                    high++;
        
                while (low >= 0
                    && str[low] == str[i]) 
                    low--;
        
                while (low >= 0 && high < n
                    && str[low] == str[high]) {
                    low--;
                    high++;
                }
        
                int length = high - low - 1;
                if (end < length) {
                    end = length;
                    start = low + 1;
                }
            }


        }
        
        // O(n^2)
        static void searchIndex(vector<vector<string>> B, int first, int last)
        {
            vector<int> indexPos;
            for (int i = 0; i < last; i++)
            {
                for (int j = 0; j < first; j++)
                {
                    if (B[j][i+1] == "D")
                    {
                        indexPos.push_back(i);
                    }
                    
                }
            }
            cout << "Posicion Inicial de substring comun mas largo entre archivos de transmision: " << indexPos[0] << endl;
            cout << "Posicion Final de substring comun mas largo entre archivos de transmision: " << indexPos[indexPos.size()-1];
        }

        //O(n+n^2)
        static void makeLCSTables(string x, string y, vector<vector<string>>& B, vector<vector<int>>& C)
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

};

#endif