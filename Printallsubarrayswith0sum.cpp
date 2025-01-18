#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "Nhap n: ";
	cin >> n;
	cout << "Nhap mang: ";
	int a[n];
	for (int i=0; i<n; i++) cin >> a[i];
	int s[n+1];
	s[0]=0;
	for (int i=0; i<n; i++)
	{
		s[i+1]=s[i]+a[i];
	}
	int t=0;
	for (int i=1; i<=n; i++)
	{
		for (int j=i; j<n+1; j++)
		{
			t=s[j]-s[i-1];
			if (t==0)
			{
				for (int k=i; k<=j; k++)
				{
					cout << a[k-1] << " ";
				}
				cout << endl;
			}
		}
	}
	return 0;
}
