#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
//the second one.
//the first matrix;
	 int arr1[100][100];
	//second one.
	 int arr2[100][100];
	 //res arr
	 int resarr[100][100];
	 
	
	int num[7]={1,2,1,0,1,2,5};
	int num2[10]={2,4,2,3,8,8,0,3,7,5};
	

//the function that will be used in threads.
void* mulfun(void*);
//the function that will be used to fill the array.
void* fillarr(void*);

int main(){//initalize two threads.
	 pthread_t t[2];
	clock_t start,end;
   start=clock();
   
         //arr={sta,counter1,counter2}
	 int arr1[3]={0,0,0},arr2[3]={50,5000,5000};
	 //these threads are to fill the arrays concuruntly.
	  pthread_create(&t[0],NULL,fillarr,(void*)arr1);
	  pthread_create(&t[1],NULL,fillarr,(void*)arr2);
	  
	  for(int i=0;i<2;i++){
	  pthread_join(t[i],NULL);
	  }
	
                        
	  int f=50,sta=0;
	   //creating the threads, which every thread will do the half of work.
	  pthread_create(&t[0],NULL,mulfun,(void*)&sta);
	  pthread_create(&t[1],NULL,mulfun,(void*)&f);
	  
	  for(int i=0;i<2;i++){
	  pthread_join(t[i],NULL);
	  }
	  
	  	  
    end=clock();
printf("the time it takes is : %fs.\n", ((double)(end-start))/CLOCKS_PER_SEC);
	return 0;
}

void* mulfun(void* sta){

         //casting the sta from void* (pointer to void) to int*(pointer to int) to use it in for loop.
       int index=*(int*)sta;
	   
	 for(int i=index;i<index+50;i++)    
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

void* fillarr(void* arr){
	//casting the void array to int
int *ar=(int*)arr;
int sta=ar[0],counter1=ar[1],counter2=ar[2];
 for(int i=sta;i<sta+50;i++){ 
		  for(int j=0;j<100;j++)
		  {
			 arr1[i][j]=num[counter1%7];
			 arr2[i][j]=num2[counter2%10];
			 counter1++;
			 counter2++;
		  }
	  }


}
