#include <fstream>
#include <algorithm>
#define NMAX 100
#define BMAX 10
using namespace std;
ifstream fin("bazeasc.in");
ofstream fout("bazeasc.out");
struct numar
{
	int val, ord, bmin, vb[BMAX+1];
};
int cifraMaxima(int);
int bazaMinima(int);
bool compar(numar, numar);
int numarInBazaZece(int, int);
int cbi(int [], int, int, int, int);
int main()
{
	int n, i, j, a, b, k;
	int x[NMAX], bz[NMAX];
	numar nr[NMAX];
	fin >> n;
	for (i = 0; i < n; i++)
	{
		fin >> x[i];
		nr[i].val = x[i];
		nr[i].ord = i;
		nr[i].bmin = bazaMinima(nr[i].val);
		for (j = nr[i].bmin; j <= BMAX; j++)
		{
			nr[i].vb[j] = numarInBazaZece(nr[i].val, j); 
		}
	}
	fin.close();
	sort(nr, nr+n, compar);
	bz[nr[0].ord] = nr[0].bmin;
	a = b = nr[0].vb[nr[0].bmin];
	for (i = 1; i < n; i++)
	{
		k = cbi(nr[i].vb, nr[i].bmin, BMAX, a, b);
		if (k < 0)
		{
			if (nr[i].vb[BMAX] < a)
			{
				bz[nr[i].ord] = BMAX;
				a = nr[i].vb[BMAX];
			}
			else
			{
				bz[nr[i].ord] = nr[i].bmin;
				b = nr[i].vb[nr[i].bmin];
			}
		}
		else
		{
			bz[nr[i].ord] = k;
		}
	}
	for (i = 0; i < n; i++)
	{
		fout << x[i] << " in baza " << bz[i] << '\n';
	}
	fout << "a = " << a << ", b = " << b << '\n';
	fout.close();
	return 0;
}
int cifraMaxima(int n)
{
	int cifmax = 0;
	while (n)
	{
		int cif = n%10;
		if (cif > cifmax)
		{
			cifmax = cif;
		}
		n /= 10;
	}
	return cifmax;
}
int bazaMinima(int n)
{
	return cifraMaxima(n) + 1;
}
bool compar(numar a, numar b)
{
	return (BMAX - a.bmin) < (BMAX - b.bmin);
}
int numarInBazaZece(int n, int b)
{
	// converteste numarul n din baza b in baza 10
	int nr = 0, p = 1;
	while (n)
	{
		nr += n%10 * p;
		p *= b;
		n /= 10;
	}
	return nr;
}
int cbi(int v[], int st, int dr, int a, int b)
{
	// cauta binar in vectorul sortat crescator v intre pozitiile st si dr
	// un numar care sa apartina intervalului [a, b] si
	// returneaza pozitia numarului in vectorul v daca il gasesti sau -1
	st--, dr++;
	while (dr-st > 1)
	{
		int mij = st + (dr-st)/2;
		if (v[mij] < a)
		{
			st = mij;
		}
		else if (v[mij] > b)
		{
			dr = mij;
		}
		else
		{
			return mij;
		}
	}
	return -1;
}
