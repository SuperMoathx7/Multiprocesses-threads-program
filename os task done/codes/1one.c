#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
//the first one.

//the result array
int resarr[100][100];
//multiplication function
void mulfun(int[100][100],int[100][100]);

int main(){
	 //"start" is to get the start time, where "end" is to get the end time.
   clock_t start,end;
   start=clock();
     //these counters are to be used in filling the arrays.
	long counter1 =0,counter2=0;
	int num[7]={1,2,1,0,1,2,5};
	int num2[10]={2,4,2,3,8,8,0,3,7,5};
	//the first matrix;
	 int arr1[100][100];
	//second one.
	 int arr2[100][100];
	//generator....
	  for(int i=0;i<100;i++)
		  for(int j=0;j<100;j++)
		  {
			 arr1[i][j]=num[counter1%7];
			 arr2[i][j]=num2[counter2%10];
			 counter1++;
			 counter2++;
		  }
		  //the matrices now is done....

		 mulfun(arr1,arr2);
        
   end=clock();                               //to get the time taken by the code in seconds.
   printf("the time it takes is : %fs.\n", ((double)(end-start))/CLOCKS_PER_SEC);

	return 0;
}

void mulfun(int arr1[100][100],int arr2[100][100]){

	 for(int i=0;i<100;i++)    
       {    
          for(int j=0;j<100;j++)    
            {    
             resarr[i][j]=0;    
              for(int k=0;k<100;k++)    
               {    
                  resarr[i][j]+=arr1[i][k]*arr2[k][j];    
                }    
             }    
        }   

}
