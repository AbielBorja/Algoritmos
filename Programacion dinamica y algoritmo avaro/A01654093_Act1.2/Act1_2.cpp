//Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937

#include <iostream>
#include <vector>
using namespace std;


vector<float> Greedy(vector<float> coinList, float P, float Q)
{
    for(int i = 0; i < coinList.size(); i++)
    {
        float change = 0;
        vector<float> changeCoins;
        for(int j = i; j >= 0; j--)
        {
            float coin = coinList.at(j);
            change += coin;
            changeCoins.push_back(coin);
        }
        if(change == Q-P)
        {
            return changeCoins;
        }
    }
    vector<float> noChangeCoins;
    return noChangeCoins;
}


vector<float> dinamicProgramming(vector<float> coinList, float P, float Q)
{
    float change = 0;
    vector<float> changeCoins;
    for(int i = 0; i < coinList.size(); i++)
    {
        float coin = coinList.at(i);
        change += coin;
        changeCoins.push_back(coin);
        if(change == Q-P)
        {
            return changeCoins;
        }
    }
    vector<float> noChangeCoins;
    return noChangeCoins;
}


int main()
{
    int N;
    cout << "Write N:";
    cin >> N;
    vector<float> coinList;
    float c;
    for(int i=1;i < N+1; i++)
    {
        cout << "Coin " << i << ":";
        cin >> c;
        coinList.push_back(c);
    }
    sort(coinList.begin(), coinList.end());

    float P;
    cout << "Write P:";
    cin >> P;

    float Q;
    cout << "Write Q:";
    cin >> Q;

    vector<float> finalDinamicChange;

    finalDinamicChange = dinamicProgramming(coinList, P, Q);

    if(finalDinamicChange.size() != 0)
    {
        cout << "The dinamic exact change is: " << endl;
        for(int i=0; i < coinList.size() - 1;i++)
        {
            
            cout << finalDinamicChange.at(i) << endl;
        }
    }else{
        cout << "No dinamic exact change found" << endl;
    }


    vector<float> finalGreedyChange;

    finalGreedyChange = dinamicProgramming(coinList, P, Q);

    if(finalGreedyChange.size() != 0)
    {
        cout << "The greedy exact change is: " << endl;
        for(int i=0; i < coinList.size() - 1;i++)
        {
            
            cout << finalGreedyChange.at(i) << endl;
        }
    }else{
        cout << "No greedy exact change found" << endl;
    }

    return 0;
}