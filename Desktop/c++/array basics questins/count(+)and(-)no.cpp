#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter Array Size: "<<endl;
    cin>>n;
    int arr[n];
    cout<<"Enter Array Elements: "<<endl;
    for (int i = 0; i < n; i++)
    {
     cin>>arr[i];
    }
    int negative =0;
    int positive = 0;
    for (int i = 0; i < n; i++)
    {

        if (arr[i]>0)
        {
             positive = positive  +1;
        }
        else if (arr[i]<0)
        {
          negative = negative +1;
        }
    }
    cout<<"The Postive count is: "<<positive<<" ";
    cout<<"The negative count is: "<<negative;

    
    

}