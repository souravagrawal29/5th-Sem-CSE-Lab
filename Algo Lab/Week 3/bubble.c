#include<stdio.h>
#include<stdlib.h>

int main() {
	int n;
	printf("Enter number of elements: \n");
	scanf("%d",&n);
	printf("Enter elements: \n");
	int a[n],i,j,temp;

	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	for(i=0; i<n-1; i++) {
		for(j=0; j<n-i-1; j++) {
			if(a[j]>a[j+1]) {
            	temp = a[j];
            	a[j] = a[j+1];
            	a[j+1] = temp;
			}
		}
	}

	for(i=0; i<n; i++)
		printf("%d ",a[i]);
	printf("\n");
}