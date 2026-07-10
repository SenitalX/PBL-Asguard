#include<iostream>
using namespace std;
int main()
{
 
    int n;
    cout<<"Enter array size: "<<endl;
    cin>>n;
    int arr1[n];
    cout<<"Enter array elemts: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>arr1[i];
    }
    int m;
    cout<<"Enter array size: "<<endl;
    cin>>m;
    int arr2[m];
    cout<<"Enter array elemts: "<<endl;
    for (int i = 0; i < m; i++)
    {
        cin>>arr2[i];
    }
    int arr3[n+m];
    for (int i = 0; i < n; i++)
    {
        arr3[i] =arr1[i];
    }
    for (int j = 0; j < m; j++)
    {
        arr3[j+n]=arr2[j];
    }
 for (int i = 0; i < n+m; i++)
{
    cout<<arr3[i]<<" ";
}

    
   
    


    
   
}