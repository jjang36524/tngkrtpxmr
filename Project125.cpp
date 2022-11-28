#include <bits/stdc++.h>
using namespace std;
#define int long long
double arr[100001];
int N;
pair<double,double> ve(double a, double b)
{
	pair<double, double>x = { 0,0 };
	int i;
	double ca = 1;
	double cb = 0;
	for (i = N; i >=0; i--)
	{
		x.first += ca * arr[i];
		x.second += cb * arr[i];
		double nca = ca * a - cb * b;
		double ncb = ca * b + cb * a;
		ca = nca;
		cb = ncb;
	}
	return x;
}
pair<int,int>getsd(double n)
{
	pair<int, pair<int, int>>t = { 1LL << 30,{-1001LL,1LL} };
	int i;
	for (i = -100; i <= 100; i++)
	{
		double v = n - i;
		double v2 = v * v;
		if (v2 - floor(v2) <= pow(10, -7))
		{
			t = min(t, { i+ (int)floor(v2)*2 ,{ i,(v > 0 ? 1 : -1) * (int)floor(v2) } });
		}
		if (ceil(v2)-v2 <= pow(10, -7))
		{
			t = min(t, { i + (int)ceil(v2)*2 ,{ i,(v > 0 ? 1 : -1) * (int)ceil(v2) } });
		}
	}
	return t.second;
}
vector<pair<double, double>>t;
double getdist(pair<double, double> n)
{
	return n.first * n.first + n.second * n.second;
}
signed main()
{
	cout << "방정식의 차수를 입력해주세요 : ";
	
	cin >> N;
	int i;
	uniform_real_distribution<double>exp(-1.5, 1.5);
	uniform_real_distribution<double>exp2(-1, 1);
	random_device rd;
	mt19937 gen(rd());
	for (i = 0; i < N; i++)
	{
		cout << N - i << " 차 항의 계수를 입력해주세요: ";
		cin >> arr[i];
	}
	cout << "상수항의 계수를 입력해주세요 : ";
	cin >> arr[N];

	
	for (i = 0; i < 1000000/N; i++)
	{
		double x = pow(10, exp(gen))*exp2(gen);
		double y = pow(10, exp(gen)) * exp2(gen);
		if (i % 2)
		{
			x = exp(gen) * 10;
			y = exp(gen) * 10;
		}
		
		double v = pow(10,min(0.0,exp2(gen)));
		double div = 0.9;
		if (i % 10==7)
		{
			x *= 10;
			y *= 10;
			v *= 10;
			div = 0.99;
		}
		int c = 0;
		while (v > pow(10, -8))
		{
			c++;
			auto r = ve(x, y);
			double nx = x + v/100;
			double ny = y + v/100;
			auto r2 = ve(nx, y);
			auto r3 = ve(x, ny);
			auto d2 = getdist(r2) - getdist(r);
			auto d3 = getdist(r3) - getdist(r);
			if (c % 2)
			{
				x -= v * d2 / sqrt(d2 * d2 + d3 * d3);
			}
			else
			{
				y -= v * d3 / sqrt(d2 * d2 + d3 * d3);
			}
			v *= div;
		}
		auto r = ve(x, y);
		if (r.first * r.first + r.second * r.second < pow(10, -5))
		{
			
			int j;
			for (j = 0; j < t.size(); j++)
			{
				if (abs(t[j].first -x) + abs(t[j].second - y)<pow(10,-4))
				{
					break;
				}
			}
			if (j == t.size())
			{
				t.push_back({ x,y });
				
			}
		}
		if (t.size() == N)
			break;
	}
	sort(t.begin(), t.end());
	for (i = 0; i < t.size(); i++)
	{
		if (abs(t[i].first) < pow(10, -6))
			t[i].first = 0;
		if (abs(t[i].second) < pow(10, -6))
			t[i].second = 0;
		if (t[i].first == 0 && t[i].second == 0)
		{
			cout << 0 << '\n';
			continue;
		}
		if (t[i].first == 0)
			goto T;
		cout << "(";
		int j;
		for (j = 1; j <= 100; j++)
		{
			double v = t[i].first * j;
			auto r2 = getsd(v);
			if (r2.first != -1001)
			{
				if (r2.first != 0)
					cout << r2.first;
				if (r2.first && (r2.second > 0))
					cout << '+';
				else if (r2.second < 0)
					cout << '-';
				if (r2.second)
				{
					cout << "sqrt(";
					cout << abs(r2.second);
					cout << ")";
				}
				cout << ")";
				if (j!=1)
					cout << '/' << j;
				break;
			}

		}
		if (j == 101)
		{
			cout << t[i].first << ')';
		}
		T:
		if (t[i].second)
		{
			if (t[i].second > 0)
			{
				cout << "+";
				cout << "(";
				for (j = 1; j <= 100; j++)
				{
					double v = t[i].second * j;
					auto r2 = getsd(v);
					if (r2.first != -1001)
					{
						if (r2.first != 0)
							cout << r2.first;
						if (r2.first && (r2.second > 0))
							cout << '+';
						else if (r2.second < 0)
							cout << '-';
						if (r2.second)
						{
							cout << "sqrt(";
							cout << abs(r2.second);
							cout << ")";
						}
						cout << ")";
						if (j != 1)
							cout << '/' << j;
						break;
					}

				}
				if (j == 101)
				{
					cout << t[i].second << ')';
				}
			}
			else
			{
				cout << "-";
				t[i].second *= -1;
				cout << "(";
				for (j = 1; j <= 100; j++)
				{
					double v = t[i].second * j;
					auto r2 = getsd(v);
					if (r2.first != -1001)
					{
						if (r2.first != 0)
							cout << r2.first;
						if (r2.first && (r2.second > 0))
							cout << '+';
						else if (r2.second < 0)
							cout << '-';
						if (r2.second)
						{
							cout << "sqrt(";
							cout << abs(r2.second);
							cout << ")";
						}
						cout << ")";
						if (j != 1)
							cout << '/' << j;
						break;
					}

				}
				if (j == 101)
				{
					cout << t[i].second << ')';
				}
			}
			cout << "i";
		}
		cout << '\n';
	}
}