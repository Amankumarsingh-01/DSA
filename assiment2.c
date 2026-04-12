#include<stdio.h>

void marge(int A[],int low,int hight)
{   
    if(low<hight){

        int mid =(low +hight) /2;
        mergesort(A,low,mid);
        mergesort(A,mid+1,hight);
    }
}

int main(){
    int A[] ={40,20,60,10,50,30,80,70};
    int n=8;
    margesort(A,0,n-1);
    return 0;
}