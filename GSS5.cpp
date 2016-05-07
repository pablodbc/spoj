// Todos los intervalos son semi abiertos [a,b), la raiz representa [0,N)
#include <stdio.h>
#include <algorithm>
using namespace std;
//INPUT:
#define MAXN 50002
int N, A[MAXN];
 
struct STN{
	int pS,sS,rS,mS;
	void merge(STN& L, STN& R){
		pS = max(L.pS,L.rS + R.pS);
		sS = max(R.sS, R.rS + L.sS);
		rS = L.rS + R.rS;
		mS = max(pS,max(sS,max(rS,max(L.sS + R.pS,max(L.mS,R.mS)))));
	}
	void operator =(int x){pS = sS = rS = mS = x;}
};
 
STN ST[4*MAXN];
void STB(int id = 1, int l = 0, int r = N){
	if(r - l < 2){
		ST[id] = A[l];
		return;
	}
	int M = (l+r)>>1, L=id<<1, R=L|1;
	STB(L, l, M);
	STB(R, M, r);
	ST[id].merge(ST[L],ST[R]);
}
 
STN STQ(int x,int y,int id = 1,int l = 0,int r = N){
	if(x == l && y == r)	return ST[id];
	int M = (l+r)>>1, L=id<<1, R=L|1;
	if(x>=M)	return STQ(x,y,R,M,r);
	if(y<=M)	return STQ(x,y,L,l,M);
 
	STN res,ln=STQ(x, M, L, l, M),rn=STQ(M, y, R, M, r);
	return res.merge(ln, rn), res;
}
int main(){
	scanf("%d",&N);
	for(int i = 0; i< N; i++) scanf("%d",&A[i]);
	STB();
	int M;scanf("%d",&M);
	while(M--){
		int x1,y1,x2,y2;scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(y1<x2){
			STN p = STQ(x1-1,y1), k = STQ(y1,x2-1), j = STQ(x2-1,y2);
			printf("%d\n",p.sS + k.mS + j.pS);
		}
		else{
			STN p = STQ(x1-1,x2-1),k = STQ(x2-1,y1),j = STQ(y1,y2),i = STQ(x1-1,y1),l=STQ(x2-1,y2);
			int res = max(k.mS,p.sS + l.pS);
			res = max(res,j.pS + i.sS);
			printf("%d\n",res);
		}
	}
} 