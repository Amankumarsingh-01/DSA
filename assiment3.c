#include<stdio.h>

int main (){
    int n,min,temp;
    printf("Enter the number:");
    scanf("%d",&n);
    int a[n];
    printf("array\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }

    for(int i=0;i<n-1;i++){
        min=i;
        int p=0;
        for(int j=i+1;j<n;j++)
        {
        if(a[j]<a[min]){
            min=j;  

        }
        if(a[i]>a[i+1]){
            p++;
        }
    }
    // if(p>0)
    // break;
    temp=a[i];
    a[i]=a[min];
    a[min]=temp;
    }

    for(int i=0;i<n;i++){
        printf("%d",a[i]);
    }
    return 0;

}

/* lowest nikalana hn*/