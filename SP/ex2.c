#include <stdio.h>
#define MAX 100

int main(){
    char a[MAX][MAX];
    int m,n,x_igrac,y_igrac,x_topka,y_topka,x1_gol,y1_gol,x2_gol,y2_gol,x_shut,y_shut;
    scanf("%d%d",&m,&n);
    scanf("%d%d",&x_igrac,&y_igrac);
    scanf("%d%d",&x_topka,&y_topka);
    scanf("%d%d",&x1_gol,&y1_gol);
    scanf("%d%d",&x2_gol,&y2_gol);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i==x_igrac&&j==y_igrac)a[i][j]='i';
            else if(i==x_topka&&j==y_topka)a[i][j]='o';
            else if(i==x1_gol&&j==y1_gol)a[i][j]=']';
            else if(i==x2_gol&&j==y2_gol)a[i][j]=']';
            else a[i][j]='-';
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%c ",a[i][j]);
        }printf("\n");
    }
    scanf("%d%d",&x_shut,&y_shut);
    if((x_topka+x_shut)==x1_gol&&(y_topka+y_shut)==y1_gol||(x_topka+x_shut)==x2_gol&&(y_topka+y_shut)==y2_gol)printf("GOAL!");
    else if((x_topka+x_shut)<m &&(y_topka+y_shut)<n){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i==x_topka&&j==y_topka)a[i][j]='-';
                if(i==x_topka+x_shut&&j==y_topka+y_shut)a[i][j]='o';
            }
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    printf("%c ",a[i][j]);
                }printf("\n");
            }
        }
    }
    else printf("OUT");

}