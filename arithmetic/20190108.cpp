#include<stdio.h>
#include<string.h>
#include<malloc.h> 

char* convert(char* s, int numRows) {
    int len = strlen(s),n = (numRows>len) ? len : numRows,i,curRow=0,goingDown = 0;
    char r[numRows][len] = {'\0'},a[len] = {'\0'};
    if(numRows==1||numRows>len) return s;
    for(i=0;i<len;i++){
        strncat(r[curRow],s+i,1);
        if(curRow == 0 || curRow == numRows - 1){
            goingDown = (goingDown == 0) ? 1 : 0; 
        }
        curRow += goingDown ? 1 : -1;
    }
    for(i = 0;i<n;i++){
        strcat(a,r[i]);
    }
    printf("%s\n",a);
    return a;  
}

int main(){ 
	char s[1000],*r = "sasas";
	int numRows = 3;
	scanf("%s",s);
	r = convert(s,numRows);
	printf("%s",r);
	return 0;
}

