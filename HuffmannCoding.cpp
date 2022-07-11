#include<bits/stdc++.h>
using namespace std;

void PrintM(map <char, int> M)
{
    for(auto it: M)
    {
        cout<<it.first<<", "<<it.second<<"\n";
    }
}

bool cmp(pair<char, int>& a, pair<char, int>& b)
{
	return a.second < b.second;
}

void Mapsort(map<char, int>& M)
{

	vector<pair<char, int> > A;

	for (auto& it : M)
    {
		A.push_back(it);
	}

	sort(A.begin(), A.end(), cmp);

	for (auto& it : A)
    {
		cout <<it.first<<" "<<it.second<<endl;
	}
}

map<char,int> Create_Map(string str)
{
    map <char, int> M;
    map <char, int>::iterator it;
    for(char ch: str)
    {
        it = M.find(ch);

        if(it == M.end())
        {
            M.insert(pair <char,int> (ch,1));
        }
        else
        {
            it->second++;
        }
    }
    return M;
}

int main()
{
    string str;
    ifstream inputFile("TextFile.txt");

    if(inputFile.good())
    {
        char ch;
        while(inputFile >> ch)
        {
            str += ch;
        }
    }

	map<char, int> M;

	M = Create_Map(str);
	PrintM(M);

	cout<<"\n";

	Mapsort(M);
	return 0;
}
