/*    DLX   O(?)   */


const int maxn=110;
const int maxnode=110;
const int maxr=110;

struct DLX{
    int n,sz;
    int S[maxn];

    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];

    int ansd,ans[maxr];

    void init(int n){
        this->n = n;
        for(int i =  0 ; i <= n ;i++){
            U[i] = i;
            D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[n] = 0;
        L[0] = n;
        sz = n+1;
        mem(S,0);
    }

    void addRow(int r , vector<int> columns){
        int first = sz;
        for(int i = 0 ; i < columns.size() ; i++){
            int c= columns[i];
            L[sz] = sz - 1;
            R[sz] = sz +1;
            D[sz] = c;
            U[sz] = U[c];
            D[U[c]] = sz ;
            U[c] = sz;
            row[sz] = r;
            col[sz] = c;
            S[c]++;
            sz++;
        }
        R[sz-1] = first;
        L[first] = sz - 1;
    }
    #define FOR(i,A,s) for(int i = A[s] ; i != s; i = A[i])
    void remove(int c){
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i,D,c){
            FOR(j,R,i){
                  U[D[j]] = U[j];
                  D[U[j]] = U[j] ;
                  D[U[j]] = D[j] ;
                  --S[col[j]];
            }
        }
    }

    void restore(int c){
        FOR(i,U,c){
            FOR(j,L,i){
                ++S[col[j]];
                U[D[j]] = j;
                D[U[j]] = j;
            }
        }
        L[R[c]] = c;
        R[L[c]] = c;
    }

    bool dfs(int d){
        if(R[0] == 0){
            ansd = d;
            return true;
        }
        int c= R[0];
        FOR(i,R,0) if(S[i] < S[c]) c = i;
        remove(c);
        FOR(i,D,c){
            ans[d] = row[i];
            FOR(j,R,i) remove(col[j]);
            if(dfs(d+1)) return true;
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);
        return false;
    }

    bool solve(vector<int> & v){
        v.clear();
        if(!dfs(0)) return false;
        for(int i = 0 ; i < ansd ; i++) v.push_back(ans[i]);
        return true;
    }
}solver;
