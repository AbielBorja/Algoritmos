#include <iostream>
#include <vector>

using namespace std;

void printBoard(vector<int> b)
{
    cout << endl;
    int rows = b.size();

    for (int r = 0; r < rows; r++)
    {      
        cout << "Patron econtrado en: " << b[r] << endl;
    }
    cout << endl;
}

void computeLPPS(vector<int> lps, string pattern){
    for(int i = 1; i < pattern.length(); i++){
        int j = lps[i - 1];

        while(j > 0 && pattern[i] != pattern[j]){
            j = lps[j - 1];
        }
        if(pattern[i] == pattern[j]){
            lps[i] = j + 1;
        }
    }
}

vector<int> searchKMP(string txt, string pattern){

    vector<int> result;

    int n = txt.length();
    int m = pattern.length();
    vector<int> lps(m);
    computeLPPS(lps, pattern);

    int j = 0;
    int i = 0;

    while(i < n){
        if(txt[i] == pattern[j]){
            i++;
            j++;
        }

        if(j == m){
            result.push_back(i -j);
            j = lps[j - 1];
        } 
        else if(i < n && txt[i] != pattern[j]){
            if(j != 0){
                j = lps[j - 1];
            }else{
                i = i + 1;
            }
        }
    }
    return result;
}

int main(){
  
    string txt = "ABCABIJSABC";
    string pattern = "ABC";

    vector<int> result = searchKMP(txt, pattern);

    printBoard(result);

    return 0;
}