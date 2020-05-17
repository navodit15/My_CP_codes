const int NN = 101;
class matrix{
public:
    ll mat[NN][NN];
    int r, c;
    matrix(){
        fr(i, 0, NN - 1)
            fr(j, 0, NN - 1)
                mat[i][j] = 0;
    }
    void setsize(int _r, int _c){ r = _r, c = _c; }
    inline matrix operator * (const matrix &a){
        assert(c == a.r);
        matrix temp;
        temp.setsize(r, a.c);
        fr(i, 0, r - 1)
            fr(j, 0, a.c - 1){
                fr(k, 0, a.r - 1){
                temp.mat[i][j] += (mat[i][k] * a.mat[k][j]) % mod;
                if(temp.mat[i][j] >= mod)
                    temp.mat[i][j] -= mod;
                }
            }
        return temp;
    }
    inline matrix operator + (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        fr(i, 0, r - 1)
            fr(j, 0, c - 1){
                temp.mat[i][j] = mat[i][j] + a.mat[i][j] ;
                if(temp.mat[i][j] >= mod)
                    temp.mat[i][j] -= mod;
            }
        return temp;
    }
    inline matrix operator - (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        fr(i, 0, r - 1)
            fr(j, 0, c - 1){
                temp.mat[i][j] = mat[i][j] - a.mat[i][j];
                if(temp.mat[i][j] < 0)
                    temp.mat[i][j] += mod;
            }
        return temp;
    }
    inline void operator = (const matrix &a){
        fr(i, 0, r - 1)
            fr(j, 0, c - 1)
                mat[i][j] = a.mat[i][j];
        r = a.r, c = a.c;
    }
    inline void print(){
        fr(i, 0, r - 1){
            fr(j, 0, c - 1)
                cout << mat[i][j] << " ";
            cout << endl;
        }
    }
};
matrix pow(matrix a,ll k){
    assert(a.r == a.c);
    matrix ans;
    fr(i, 0, a.r - 1)
        ans.mat[i][i] = 1;
    ans.r = a.r;
    ans.c = a.r;
    while(k){
        if(k & 1)
            ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}
