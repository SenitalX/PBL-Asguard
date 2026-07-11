#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter array size: "<<endl;
    cin>>n;
    int arr[n];
    cout<<"Enter array Element: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    for (int i = 0; i < n-1; i++)
    {
        arr[i]= arr[i+1];
    }
    for (int i = 0; i < n-1; i++)
    {
        arr[n-1]=0;
    }
    for (int i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }
    
    return 0;
    
}