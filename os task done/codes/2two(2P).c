#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
//the second one.



void mulfun(int[100][100],int[100][100],int[100][100],int,int);

int main(){
	 //these three pipes to write and read from other process, pipe is a way to communicate between processes.
	int fp[2],p[2],f[2];//1 for wirte and 0 for read.
	 pipe(fp);
	 pipe(p);
	 pipe(f);
	 //"start" is for get the start time, end to get the end time.
	clock_t start,end;
   start=clock();
    //fork, is using to get child process by the parent process.
	int id=fork();
	
	
	 if(id==-1){
		 printf("an error occured while creating child.");
		 return 1;
	 }

		 //these counters are used to fill the two arrays.
	long counter1 =0,counter2=0;
	int num[7]={1,2,1,0,1,2,5};
	int num2[10]={2,4,2,3,8,8,0,3,7,5};
	//the first matrix;
	 int arr1[100][100];
	//second one.
	 int arr2[100][100];
	 
	 //res arr
	 int resarr[100][100]={0};
	int sta,en;
	    //the child process will fill the first half of two arrays.
	  if(id==0){//child process;
		  sta=0;en=50;
	  }else{//the parent process will fill the second half of two arrays.
		  sta=50;en=100;
	 }
	 
	 
	
		 
		  if(id!=0){
		 counter1=5000;
		 counter2=5000;
	         
	//generator....

	  for(int i=sta;i<en;i++){//if(id==0)
		  for(int j=0;j<100;j++)
		  {
			 arr1[i][j]=num[counter1%7];//printf("%d ",arr1[i][j]);
			 arr2[i][j]=num2[counter2%10];
			 counter1++;
			 counter2++;
		  }
	  }
		  }
	  
	  //write the whole array to the pipe to make communication between child and parent
       if(id!=0){
		   close(fp[0]);
		  write(fp[1],arr1,sizeof(int)*100*100);
		  write(fp[1],arr2,sizeof(int)*100*100);
		   close(fp[1]);
		   
	   } else{
		   close(fp[1]);
		  read(fp[0],arr1,sizeof(int)*100*100);
		  read(fp[0],arr2,sizeof(int)*100*100);
		   close(fp[0]);
	   }
	   
	   if(id==0){
		 counter1=0;
		 counter2=0;
	         
	//generator....

	  for(int i=sta;i<en;i++){//if(id==0)
		  for(int j=0;j<100;j++)
		  {
			 arr1[i][j]=num[counter1%7];//printf("%d ",arr1[i][j]);
			 arr2[i][j]=num2[counter2%10];
			 counter1++;
			 counter2++;
		  }
	  }
		  }
	   //write the whole array to the pipe to make communication between child and parent
	   if(id==0){
		   close(f[0]);
		  write(f[1],arr1,sizeof(int)*100*100);
		  write(f[1],arr2,sizeof(int)*100*100);
		   close(f[1]);
		   
	   } else{
		   close(f[1]);
		  read(f[0],arr1,sizeof(int)*100*100);
		  read(f[0],arr2,sizeof(int)*100*100);
		   close(f[0]);
	   }
	  
	  
	   //the matrices now is done....


		mulfun(arr1,arr2,resarr,sta,en);//done correctly....
		 //wait is to wait a child from parent.
		if(id!=0)wait(NULL);
		
		
		
		
		if(id==0){
		   close(p[0]);
		  write(p[1],resarr,sizeof(int)*50*100);
		   close(p[1]);
		   
	   }
	   else{
		   close(p[1]);
		  read(p[0],resarr,sizeof(int)*50*100);
		   close(p[0]);
	   }
	   // now the resarr is done.
  
   end=clock();
 if(id!=0){
          //to print this one time, i put it in if statment.
	  printf("the time it takes is : %fs.\n", ((double)(end-start))/CLOCKS_PER_SEC);
  }
   

	return 0;
}

void mulfun(int arr1[100][100],int arr2[100][100],int resarr[100][100],int sta,int en){

//also here, the child will calculate the first half and the parent the second half.

	 for(int i=sta;i<en;i++)    
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
