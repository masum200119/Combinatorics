You are given two integers n
 and m
 and an array a
 of n
 integers. For each 1≤i≤n
 it holds that 1≤ai≤m
.

Your task is to count the number of different arrays b
 of length n
 such that:

1≤bi≤m
 for each 1≤i≤n
, and
gcd(b1,b2,b3,...,bi)=ai
 for each 1≤i≤n


Since this number can be too large, print it modulo 998244353
.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int const N = 2e5 + 5;

ll func(int m , int v1 , int v2){
 ll x  = v1/v2;
 ll ans = m/v2;
 ll total = ans;
 vector<ll > fac;
 for(ll j=2;j*j<=x;j++){
    if(x%j==0){
     fac.push_back(j);
    while(x%j==0){
        x= x/j;
       }
    }
    else continue;
 }
 if(x>1) fac.push_back(x);
//  for(auto i:fac) cout<<i<<" ";
//  cout<<endl;
  ll s  = fac.size();
 for(ll i=1 ; i< (1ll<<s) ; i++){
    ll par =  __builtin_popcount(i)&1;
    ll res=1;
    for(ll j=0;j<s;j++){
        if(  (i>>j) & 1 ){
            res *= fac[j];
        }
    }
    if(par) ans -=  total/res;
    else   ans +=  total/res;
 }
 return ans;
}

void solve()
{
   int n,m ; 
   cin>>n>>m;
   ll a[n];
   for(int i=0;i<n;i++) cin>>a[i];
   ll ans =1 , mod = 998244353;
   for(int i=1;i<n;i++){
     if(a[i-1]%a[i]) {
        cout<<0<<endl;
        return;
     }
   }
   for(int i=1;i<n;i++){
    if(a[i-1]==a[i]){
        ans *=(m/a[i]);
        ans %= mod;
    }
    else {
      ans  *= func(m,a[i-1],a[i]);
      ans %= mod;
    }
   }
   cout<<ans<<endl;
   return;

}
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        solve();
    }
}
