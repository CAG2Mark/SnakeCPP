#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<vector>
#include<unistd.h>
#include<conio.h>
#include<cstdlib>
using namespace std;vector<int*>A;void clear(){system("cls");}int X,Y;int B[]={0,0};int D[4][2]={{0,-1},{1,0},{0,1},{-1,0}};void C(int pos=-1){if(pos==-1)pos=abs(rand())%X*Y;for(auto i : A){if(*(i)+*(i+1)*X==pos){C(++pos);return;}}B[0]=pos%X;B[1]=pos/X;}int main(int argc,char**argv){X=70,Y=20;char E=0;int F=10;int G=F;A=vector<int*>(G,NULL);for(int i=0;i<G;++i){A[i]=(int*)malloc(sizeof(int)*2);A[i][0]=X/2,A[i][1]=Y/2+i;}C();for(;;){if(_kbhit()&&getch()==224){switch(getch()){case 72:E=0;break;case 77:E=1;break;case 80:E=2;break;case 75:E=3;break;}}for(int i=G-1;i>0;--i){A[i][0]=A[i-1][0];A[i][1]=A[i-1][1];}A[0][0]+=D[E][0];A[0][1]+=D[E][1];int H=A[0][0],I=A[0][1];if(H<0||H>=X||I<0||I>=Y){break;}else{char J=0;for(int i=1;i<G;++i){if(H==A[i][0]&&I==A[i][1]){J=1;}}if(J)break;}if(H==B[0]&&I==B[1]){C();A.push_back((int*)malloc(sizeof(int)*2));A[G][0]=A[G-1][0];A[G][1]=A[G-1][1];++G;}clear();char*K=(char*)malloc((X+1)*(Y+2)*sizeof(char));for(int i=0;i<Y;++i){for(int j=0;j<X;++j){K[(X+1)*i+j]='.';}K[(X+1)*i+X]=10;}for(int i=0;i<G;++i){K[(A[i][1])*(X+1)+A[i][0]]='X';}K[(B[1])*(X+1)+B[0]]='O';printf("%s\nScore:%d|Fruit:(%d,%d)\n",K,G-F,B[0],B[1]);usleep(130000);}return 0;}