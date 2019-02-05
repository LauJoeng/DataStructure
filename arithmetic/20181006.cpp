#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>

using namespace std;

typedef struct edgedata{
	int beg,end;
	double length;
}edge;

typedef struct point{
	double x,y;
}point;

void getEdges(point* points,edge* edges,int n){
	double xl,yl,t;
	int k=0,i=0,j=0;
	for(;i<n-1;i++){
		for(j=i+1;j<n;j++){
			edges[k].beg=i;
			edges[k].end=j;
			xl = points[i].x-points[j].x;
			yl = points[i].y-points[j].y;
			t = xl*xl+yl*yl;
			edges[k++].length = sqrt(t);			
		}
	}
}

void sortEdges(edge* edges,int n){
	int i=0,j=0;
	edge temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i;j++){
			if(edges[j].length>edges[j+1].length){
				temp=edges[i];
				edges[i]=edges[j];
				edges[j]=temp;	
			}
		}
	}
}

edge* solve(edge* edges,int n){
	edge tree[n-1];
	int cnvx[n],i,j,k=0,ltfl;
	for(i=0;i<n;i++){
		cnvx[i]=i; 
	}
	for(i=0;i<n-1;i++){
		while(cnvx[edges[k].beg]==cnvx[edges[k].end])k++;
		tree[i]=edges[k];
		ltfl=cnvx[edges[k].end];
		for(j=0;j<n;j++){
			if(cnvx[j]==ltfl){
				cnvx[j]=cnvx[edges[k].beg];
			}
		}
		k++;
	}
	return tree;
	
}

int main(){
	int n,i,count;
	double result=0;
	edge* tree;
	scanf("%d",&n);
	count = (n*n-n)/2;
	edge* edges = (edge*)malloc(sizeof(edge)*count);
	point* points = (point*)malloc(sizeof(point)*n);
	for(i=0;i<n;i++){
		scanf("%lf%lf",&points[i].x,&points[i].y);
	}
	getEdges(points,edges,n);
	sortEdges(edges,count);
	tree = solve(edges,n);
	
	for(i=0;i<n-1;i++){
		result+=tree[i].length;
	}
	int temp = (int)(result*100);
	result=temp/100.0;
	printf("%.2lf",result);
	return 0;
} 
