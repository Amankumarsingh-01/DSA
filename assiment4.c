#include<stdio.h>
int main(){
    // int n;
    int n=3;
    int m,missing;
    int sum =0;
    int a[]={0,2,3,4,5.7,8,9};
    // scanf("%d",&n);

    for(int i=0; i<n; i++){
        sum = sum+a[i];
    }
    m = (n+1)*(n+2)/2;
    missing =m-sum;
    printf("missing is:%d\n",missing); 
}