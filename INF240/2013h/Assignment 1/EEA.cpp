//Succesfully compiled with Visual Studio 2012 C++ compiler and gcc4.8.1

#include <cstdio>
#include <vector>
#include <cmath>
#define LL long long

using namespace std;

//There is no normalization so x or y will be minus
pair<LL,LL> eea(LL a, LL b) {
    
    if(a<b) {
        pair<LL, LL> r = eea(b,a);
        return make_pair(r.second, r.first);
    }

    if(b == 0) return make_pair(1,0);

    pair<LL, LL> r = eea(b, a % b);
    //r.first and r.second are coefficients such that b*r.first + (a%b)*r.second divides b and (a%b)
    //res contains the solution pair (x,y)
    pair<LL, LL> res = make_pair(r.second, (r.first-r.second*(a/b)));

    return res;
}

int main(void) {
   LL a,b;
   
   //a is public exponent e, b is phi(n)
   while(scanf("%lld %lld", &a, &b) == 2) {
        pair<LL,LL> XY = eea(a,b);
        LL gcd = (a*XY.first)+(b*XY.second);

        printf("x: %lld y: %lld gcd(a,b): %lld\n", XY.first, XY.second, gcd); 
        printf("Private exponent d is: %lld\n", b + XY.first);

   }

   return 0;

}
