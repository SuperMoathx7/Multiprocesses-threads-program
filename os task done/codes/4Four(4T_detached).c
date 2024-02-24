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

int main(){
	 pthread_t t[8];//initalize four threads.
	//eight threads, but divided to do two tasks half by half, so it is the same as four threads.
                         	
	 //arr={sta,counter1,counter2}
	 int arr1[3]={0,0,0},arr2[3]={25,2500,2500},arr3[3]={50,5000,5000},arr4[3]={75,7500,7500};
	  //creating the threads, which every thread will do the quarter of work.
	  pthread_create(&t[0],NULL,mulfun,(void*)arr1);
	  pthread_create(&t[1],NULL,mulfun,(void*)arr2);
	  pthread_create(&t[2],NULL,mulfun,(void*)arr3);
	  pthread_create(&t[3],NULL,mulfun,(void*)arr4);
	   pthread_detach(t[0]);
	  pthread_detach(t[1]);
	  pthread_detach(t[2]);
	  pthread_detach(t[3]);
	  

	 
	 // four theads, every thread will do a quarter.
	  int sta=0,f=25,a=50,g=75;
	  pthread_create(&t[4],NULL,mulfun,(void*)&sta);
	  pthread_create(&t[5],NULL,mulfun,(void*)&f);
	  pthread_create(&t[6],NULL,mulfun,(void*)&a);
	  pthread_create(&t[7],NULL,mulfun,(void*)&g);
	   pthread_detach(t[4]);
	  pthread_detach(t[5]);
	  pthread_detach(t[6]);
	  pthread_detach(t[7]);
	  //here the threads are detached, no join after create the theads.
	  //the main thread will not wait these threads, so we cant actully calculate 
	  //the time taken by these threads. when we use clock start end, this will 
	  //calculate the main thread time without these detached threads....

   
      printf("The main thread is done, but the detached threads, we don't know about them...");
	return 0;
}

void* mulfun(void* sta){

//casting the sta from void* (pointer to void) to int*(pointer to int) to use it in for loop.
       int index=*(int*)sta;
	   
	 for(int i=index;i<index+25;i++)    
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