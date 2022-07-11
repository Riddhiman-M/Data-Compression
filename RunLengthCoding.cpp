#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

void Print1(vector<int> &v)
{
    int i=0;
    while(i < v.size())
    {
        cout<<v[i]<<" ";
        i++;
    }
    cout<<"\n";
}

void Print2(vector<vector<int>> &v)
{
    int r=v.size();
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<v[i].size(); j++)
            cout<<v[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

vector<int> RLEncoding(vector<vector<int>> &nums)
{
    vector <int> n;
    int r = nums.size(), c=nums[0].size();
    int cnt = 1, prev=nums[0][0], curr;

    for(int i=0; i<r; i++)
    {
        int j = i==0? 1: 0;
        for(; j<c; j++)
        {
            curr = nums[i][j];
            if(curr == prev)
                cnt++;
            else
            {
                n.push_back(prev);
                n.push_back(cnt);
                cnt = 1;
                prev = curr;
            }
        }
        if(i==r-1)
        {
            n.push_back(prev);
            n.push_back(cnt);
        }
    }
    Print1(n);

    return n;
}

vector<vector<int>> RLDecoding(vector <int> &n, int r, int c)
{
    int c_cnt=0;
    int r_ind=0, c_ind=0;
    vector<vector<int>> nums(r, vector<int>(c));

    for(int i=0; i<n.size()-1; i+=2)
    {
        int element = n[i];
        for(int j=0; j<n[i+1]; j++)
        {
            nums[r_ind][c_cnt%c] = element;
            c_cnt++;
            if(c_cnt%c == 0)
                r_ind++;
        }
    }
    Print2(nums);

    return nums;
}


int main()
{
    ifstream inputFile("DataDoc.txt");
    vector<int> num1;
    int rows, cols;

    if(inputFile.good())
    {
        int cnt=0;
        int curr = 0;
        while(inputFile >> curr)
        {
            if(cnt == 0)
                rows = curr;
            else if(cnt == 1)
                cols = curr;
            else
                num1.push_back(curr);
            cnt++;
        }
    }
    vector<vector<int>> nums(rows, vector<int>(cols));

    int k=0;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            nums[i][j] = num1[k++];
    }

    cout<<"Original Data:\n";
    Print2(nums);

    vector <int> compressed_num;
    compressed_num = RLEncoding(nums);

    cout<<"Compression Ratio = "<<100*(double)((nums.size()*nums[0].size())-compressed_num.size())/compressed_num.size()<<"\n";

    cout<<"\nDe-Compressed Data:\n";
    vector<vector<int>> ret_data;
    ret_data = RLDecoding(compressed_num, rows, cols);
}
