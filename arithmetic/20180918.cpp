#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>

using namespace std;

typedef struct{
	int weight;
	char color[10];
} rat;

bool compare(rat a,rat b){
	return a.weight>b.weight;
}

int main()
{
	int N;
	while(scanf("%d",&N)!=EOF){
		rat data[N];
		for(int i=0;i<N;i++){
			scanf("%d %s",&data[i].weight,&data[i].color);
		}
//		for(int i=0;i<N;i++){
//			printf("%d\n",data[i].weight);
//		}
//		printf("\n\n\n\n\n");
//		printf("ssssssssssssssss\n");
		sort(data,data+N,compare);
		for(int i=0;i<N;i++){
			printf("%s\n",data[i].color);
		}	
	}
	return 0;
} 
