#include <bits/stdc++.h>

using namespace std;

int main()
{

    
    int N = 15, C = 5, E = N * (N-1);


    cout<<N<<" "<<C<<" "<<E<<"\n";
    long long tc1 = C * pow(3,N) + (E *log2(N)) * pow(2,N);
    long long tc2 = C * pow(3,N) + N*N * pow(2,N);
    long long tc3 = C * pow(4,N) + N*N * pow(2,N);
    long long tc4 = C * pow(3,N) + ((E/2) *log2(E/2)) * pow(2,N);

    cout<<"TC1 : "<<tc1<<"\n" ;
    cout<<"TC2 : "<<tc2<<"\n" ;
    cout<<"TC3 : "<<tc3<<"\n" ;
    cout<<"TC3 : "<<tc4<<"\n" ;
    
    return 0;
}