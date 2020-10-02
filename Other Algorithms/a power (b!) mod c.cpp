#include<bits/stdc++.h>

using namespace std;

typedef long long int li;
typedef long double ld;
typedef vector<li> vi;
typedef pair<li,li> pi;
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define B begin()
#define E end()
#define f(i,l,r) for(li i=l;i<=r;++i)
#define fr(i,l,r) for(li i=l;i>=r;--i)
#define u_map unordered_map
#define endl "\n"
#define debug(x) cout<<#x<<" = "<<x<<endl;

li fastpow(li base,li exp,li M) 
{
    li res=1;
    while(exp>0) {
        if(exp&1)
            res=(res*base)%M;

        base=(base*base)%M;
        exp>>=1;
    }
    return res;
}

vi m,primes,rem;
li p,q,r;
li sz;

tuple<li,li,li> extended_euclid(li a,li b)
{
	if(a==0)
	{
		return {b,0,1};
	}
	else
	{
		tuple<li,li,li> tp = extended_euclid(b%a,a);

		li g,x,y;

		g=get<0>(tp);
		y=get<1>(tp);
		x=get<2>(tp);

		return {g,x-(b/a)*y,y};
	}
}

li inv(li a,li m)
{
	tuple<li,li,li> tp = extended_euclid(a,m);

	return get<1>(tp)%m;
}

void factorize(li x)
{
	li tp=1;

	while(x%2==0)
	{
		tp*=2;
		x/=2;
	}

	if(tp>1)
	{
		primes.PB(2);
		m.PB(tp);
	}

	for(li i=3;i*i<=x;i+=2)
	{
		li tp=1;

		while(x%i==0)
		{
			tp*=i;
			x/=i;
		}

		if(tp>1)
		{
			primes.PB(i);
			m.PB(tp);
		}
	}

	if(x>2)
	{
		primes.PB(x);
		m.PB(x);
	}
}

void fill_rem()
{
	for(li tp:primes)
	{
		if(tp==2)
		{
			if(p%2==0)
			{
				rem.PB(0);
			}
			else
			{
				rem.PB(1);
			}
			continue;
		}

		li exp=1;

		f(i,2,q)
		{
			exp*=i;
			exp%=(tp-1);
		}	

		li ans=fastpow(p,exp,tp);

		// debug(ans);

		rem.PB(ans);
	}
}

void solve()
{
   	cin>>p>>q>>r;

   	if(r==1)
   	{
   		cout<<0;
   		return;
   	}

   	if(p==1)
   	{
   		cout<<1;
   		return;
   	}

   	factorize(r);

   	fill_rem();

   	li i=0;

   	sz=primes.size();

   	while(i<sz-1)
   	{
   		li tp1=(inv(m[i+1],m[i])*rem[i]*m[i+1])+(inv(m[i],m[i+1])*rem[i+1]*m[i]);
   		li tp2=m[i]*m[i+1];

   		rem[i+1]=(tp1+tp2)%tp2;
   		m[i+1]=tp2;

   		i++;
   	}

   	cout<<rem[sz-1];
}

int main()
{    
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    li t=1;

    // cin>>t;

    while(t--)
    {
        solve();
    }

    return 0;
}