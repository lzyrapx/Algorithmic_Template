
/*
  link: https://www.ams.org/journals/mcom/1996-65-213/S0025-5718-96-00674-6/S0025-5718-96-00674-6.pdf
  main ideal come from a paper by M.DELEGLISE ADN J.LAGARIAS
  "COMPUTING PI(x): THE MEISSEL, LEHMER, LAGARIAS, MILLER, ODLYZKO METHOD"
  a = PI(y); (y >>= x^(1/3) and y <= x^(1/2))
  PI(x)         = phi(x, a) + a - 1 - P2Xa(x,a);
  phi(x, a)     = S0 + S
  = S0  + S1 + S3 + S2
  = S0  + S1 + S3 + U + V
  = S0  + S1 + S3 + U + V1 + V2
  = S0  + S1 + S3 + U + V1 + W1 + W2 + W3 + W4 + W5
  it need O(n^2/3) space and MAXN > 10 and MAXN <= 1e11
*/
#include <bits/stdc++.h>

using namespace std;

#define COMP 4
#define MASKN(n) (1 << ((n >> 1) & 7))
#define min(a, b) (a) < (b) ? (a) : (b)

typedef unsigned int uint;

typedef long long int64;

int *Prime;
int *PI;

int64 MAXN = (int64)1e11;
// int pt[130000];   // MAXN < 1e11, size = np

int *phiTable;
int *minfactor;

int x23, x12, x13, x14, y;
int64 x;

int ST = 7, Q = 1, phiQ = 1;
// Q    = 2*3*5*7*11*13 = 30030
// phiQ = 1*2*4*6*10*12 = 5760

int phi(int x, int a)
{
    if (a == ST)
        return (x / Q) * phiQ + phiTable[x % Q];
    else if (a == 0)
        return x;
    else if (x < Prime[a])
        return 1;
    else
        return phi(x, a - 1) - phi(x / Prime[a], a - 1);
}

int freememory(int alloc)
{
    int memsize = (x / y) + 100;
    if (alloc == 0)
    {
        int psize = (int)(memsize / log(memsize));
        PI = new int[memsize + 100];
        Prime = new int[(int)(psize * 1.2) + 100];
    }
    else
    {
        delete phiTable;
        delete minfactor;
        delete Prime;
        delete PI;
    }
    return alloc;
}

void init_phiTable()
{
    int p, i, j;
    // phiQ = Q = 1;

    if (x < 1e10)
        ST = 6;
    if (ST > PI[y])
        ST = PI[y];

    for (i = 1; i <= ST; ++i)
    {
        Q *= Prime[i];
        phiQ *= Prime[i] - 1;
    }

    phiTable = new int[Q + 10];
    for (i = 0; i < Q; ++i)
        phiTable[i] = i;

    for (i = 1; i <= ST; ++i)
    {
        p = Prime[i];
        for (j = Q - 1; j >= 0; --j)
            phiTable[j] -= phiTable[j / p];
    }
}

void init_minFactor()
{
    int i, j, maxy = y + 10;
    int sqrty = (int)sqrt(maxy) + 1;

    minfactor = new int[maxy + 10];
    for (i = 0; i < maxy; i++)
        minfactor[i] = i;

    for (i = 1; Prime[i] <= maxy; i++)
    {
        for (j = Prime[i]; j <= maxy; j += Prime[i])
        {
            if (minfactor[j] == -j || minfactor[j] == j)
                minfactor[j] = -Prime[i];
            else
                minfactor[j] = -minfactor[j];
        }
    }

    for (i = 1; Prime[i] <= sqrty; i++)
    {
        int powp = Prime[i] * Prime[i];
        for (j = powp; j <= maxy; j += powp)
            minfactor[j] = 0;
    }
}

int sieve()
{
    int primes = 1;
    int maxp = (x / y) + 10;
    Prime[1] = 2;

    unsigned char *bitMask = (unsigned char *)PI;
    memset(bitMask, 0, (maxp + 64) >> COMP);

    for (int p = 3; p < maxp; p += 2)
    {
        if (!(bitMask[p >> COMP] & MASKN(p)))
        {
            Prime[++primes] = p;
            if (p > maxp / p)
                continue;
            for (int j = p * p; j < maxp; j += p << 1)
                bitMask[j >> COMP] |= MASKN(j);
        }
    }
    Prime[0] = primes;
    Prime[primes] = 0;
    return primes;
}

void init_x()
{
    x = (int64)MAXN;
    x23 = (int)(pow(x, 2.0 / 3) + 0.01);
    x12 = (int)(pow(x, 1.0 / 2) + 0.01);
    x13 = (int)(pow(x, 1.0 / 3) + 0.01);
    x14 = (int)(pow(x, 1.0 / 4) + 0.01);

    y = x13;
    freememory(0);
}

int64 cal_S0()
{
    int64 S0 = x;
    for (int j = 2; j <= y; j++)
    {
        if (minfactor[j] > 0)
            S0 += x / j;
        else if (minfactor[j] < 0)
            S0 -= x / j;
    }

    return S0;
}

// so bad performance in this function
int64 cal_S3()
{
    int i, p, a;
    int np = 1;
    int64 S3 = 0;

    for (i = 1; i <= PI[x14]; i++)
    {
        p = Prime[i];
        a = PI[p] - 1;
        for (int m = y / p + 1; m <= y; m++)
        {
            int xx = x / (int64)(m * p);
            if (minfactor[m] > p)
                S3 -= phi(xx, a);
            else if (minfactor[m] < -p)
                S3 += phi(xx, a);
        }
    }

    return S3;
}
int pi[105] = {0};
bool nprim[105] = {1, 1};
void init_PI()
{
    int Px = 1;
    PI[0] = PI[1] = 0;
    for (int i = 1; Prime[i]; i++, Px++)
    {
        for (int j = Prime[i]; j <= Prime[i + 1]; j++)
        {
            PI[j] = Px;
        }
    }
}
void init_2()
{
    memset(pi, 0, sizeof(pi));
    for (int i = 2; i < 100; i++)
    {
        if (!nprim[i])
        {
            for (int j = i; j < 100; j++)
            {
                pi[j]++;
            }
            for (int j = i + i; j < 100; j += i)
            {
                nprim[j] = true;
            }
        }
    }
}

int64 cal_P2xa()
{
    int64 phi2 =
        (int64)PI[y] * (PI[y] - 1) / 2 - (int64)PI[x12] * (PI[x12] - 1) / 2;

    for (int i = PI[y] + 1; i <= PI[x12] + 0; i++)
    {
        int p = Prime[i];
        phi2 += PI[x / p];
    }
    return phi2;
}

int64 cal_S1()
{
    int64 temp = PI[y] - PI[x13];
    int64 S1 = temp * (temp - 1) / 2;

    return S1;
}

int64 cal_U()
{
    int64 p, U = 0;
    int sqrt_xdivy = (int)sqrt(x / y);
    for (int i = PI[sqrt_xdivy] + 1; i <= PI[x13]; i++)
    {
        p = Prime[i];
        U += PI[y] - PI[x / (p * p)];
    }

    return U;
}

int64 cal_V1()
{
    int64 V1 = 0;
    int MINq, p;
    for (int i = PI[x14] + 1; i <= PI[x13]; i++)
    {
        p = Prime[i];
        MINq = min((uint)y, x / ((int64)p * p));

        V1 += (int64)(2 - PI[p]) * (PI[MINq] - PI[p]);
    }

    return V1;
}

int64 cal_V2()
{
    int64 V2 = 0;
    int i, sqrt_xdivy = (int)sqrt(x / y);

    int xdivy2 = x / (y * y);

    for (i = PI[x14] + 1; i <= PI[sqrt_xdivy]; i++)
    {
        int64 p = Prime[i];

        for (int j = PI[p] + 1; j <= PI[y]; j++)
        {
            int q = Prime[j];

            V2 += PI[x / (p * q)];
        }
    }

    for (i = PI[sqrt_xdivy] + 1; i <= PI[x13]; i++)
    {
        int64 p = Prime[i];

        xdivy2 = x / (p * p);
        for (int j = PI[p] + 1; j <= PI[xdivy2]; j++)
        {
            int q = Prime[j];
            V2 += PI[x / (p * q)];
        }
    }
    return V2;
}

int main()
{
    cin >> MAXN; // 11 <= MAXN <= 1e11
    init_2();
    ST = 7, Q = 1, phiQ = 1;
    init_x();
    sieve();
    init_PI();
    init_minFactor();
    init_phiTable();

    int64 pix = PI[y] - 1;
    pix += cal_S3();
    pix -= cal_P2xa();
    pix += cal_S0();
    if (y != x13)
    {
        pix += cal_S1();
        pix += cal_U();
    }
    pix += cal_V2();
    pix += cal_V1();
    printf("%lld\n", pix);
    freememory(1);
    return 0;
}