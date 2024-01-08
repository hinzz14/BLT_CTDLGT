#include <bits/stdc++.h>
#include "dblist.cpp"
using namespace std;

int main() {
    int t;
    cout <<"Nhap so truong hop: ";
    cin >> t;

    for (int test = 1; test <= t; ++test) {
        int n;
        cout<<"Nhap so con chau truong hop thu " << test <<": ";
        cin >> n;
        Doublelist<string, string, int> familyList; 
        familyList.push(n);      
        familyList.sortdad();
        familyList.calcul();
        familyList.sort();
        cout << "DATASET " << test << endl;
        familyList.printf();
    }
}
