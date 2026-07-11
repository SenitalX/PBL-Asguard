#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter size of array: "<<endl;
    cin>>n;
    int arr1[n];
    cout<<"Enter array elemets: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>arr1[i];
    }
    int m;
    cout<<"Enter size of array"<<endl;
    cin>>m;
    int arr2[m];
    cout<<"Enter array elements: "<<endl;
    for (int i = 0; i < m; i++)
    {
        cin>>arr2[i];
    }
    for (int i = 0; i < n; i++)
    {
        cout<<arr1[i];
    }
    for (int i = 0; i < m; i++)
    {
        int found = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr1[j]==arr2[i])
            {
                found = 1;
                break;
            }
            
        }
        if (found == 0)
        {
          cout << arr2[i];
        }
    }
}