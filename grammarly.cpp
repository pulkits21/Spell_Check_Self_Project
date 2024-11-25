#include<bits/stdc++.h>
using namespace std;

vector<string> readCSV(string &filename)
{
    vector<string> data;
    ifstream file(filename);

    if (!file.is_open()) 
    cout<<"The file couldn't be opened."<<endl;

    string line;
    while(getline(file, line)) 
    {
        stringstream ss(line);
        vector<string> words{istream_iterator<string>{ss}, istream_iterator<string>{}};
        data.insert(data.end(), words.begin(), words.end());
    }
    file.close();
    return data;
}

int dist(string data, string &word, vector<vector<int>> &dp)
{
    int n = data.size();
    int m = word.size();
    for(int i=0; i<=n; i++) dp[i][0]=i;
    for(int j=0; j<=m; j++) dp[0][j]=j;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if (data[i-1]==word[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i][j-1],dp[i-1][j], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}

string edit(string &word, set<string> &dictionary) 
{
    int len=word.size();
    if (dictionary.count(word)) return word;
    string res=word; 
    int thresh,mind=len;
    if (len<=3) thresh = 1;
    else if(len<=7) thresh=2;
    else thresh=3;

    for (auto &data:dictionary) 
    {
        int n = data.size();
        int m = word.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1,0));
        int distance = dist(data, word, dp);
        if (distance<=thresh && distance<mind) 
        {
            res = data;
            mind = distance;
        }
    }
    return res;
}

int main()
{
    set<string> dictionary;
    string filename = "dictionary.csv";
    vector<string> words = readCSV(filename);
    dictionary.insert(words.begin(), words.end());

    cout<<"Input your paragraph here (empty line to end): "<<endl;

    vector<vector<string>> para;
    string line;
    while(getline(cin, line) && !line.empty())
    {
        stringstream ss(line);
        vector<string> v{istream_iterator<string>{ss}, istream_iterator<string>{}};
        para.push_back(v);
    }   

    cout << endl << "Corrected Paragraph:" << endl; 
    for (auto &line : para) 
    {
        for (auto &word : line) 
        {
            string corrected_word = edit(word, dictionary);
            cout << corrected_word << " ";
        }
        cout << endl;
    }

    return 0;
}