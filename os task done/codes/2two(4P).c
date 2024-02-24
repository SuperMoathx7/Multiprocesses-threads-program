#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
//the second one.



void mulfun(int[100][100],int[100][100],int[100][100],int,int);

int main(){
	
	//pipes to comunicate between process.
	int fp[2],p[2],f[2];//1 for wirte and 0 for read.
	 pipe(fp);
	 pipe(p);
	 pipe(f);
	 int fp1[2],p1[2],f1[2],g1[2];//1 for wirte and 0 for read.
	 pipe(fp1);
	 pipe(p1);
	 pipe(f1);
	 pipe(g1);
	 int fp2[2],p2[2],f2[2];//1 for wirte and 0 for read.
	 pipe(fp2);
	 pipe(p2);
	 pipe(f2);
	clock_t start,end;
   start=clock();
	int id1=fork();
	int id2=fork();
	
	 if(id1==-1){
		 printf("an error occured while creating child.");
		 return 1;
	 }
          if(id2==-1){
		 printf("an error occured while creating child.");
		 return 1;
	 }
		 
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
	 
	 //every process will do a quarter of whole job.
	  if(id1==0&&id2==0){//the last child..
		  sta=0;en=25;counter1 =0;counter2=0;
	  }else if(id1!=0&&id2==0){//the second parent child...
		  sta=50;en=75;counter1 =5000;counter2=5000;
	 }else if(id1==0&&id2!=0){//the first parent child...
		  sta=25;en=50;counter1 =2500;counter2=2500;
	  }else if(id1!=0&&id2!=0){//parent process;
		  sta=75;en=100;counter1 =7500;counter2=7500;
	 }
	 
	 
	 
	 
	
	//generator....
	
	  for(int i=sta;i<en;i++){ //if(id==0)
		  for(int j=0;j<100;j++)
		  {
			 arr1[i][j]=num[counter1%7];//printf("%d ",arr1[i][j]);
			 arr2[i][j]=num2[counter2%10];
			 counter1++;
			 counter2++;
		  }
	  }
	 
	 
	  
       if(id1==0&&id2==0){
		   close(fp[0]);
		  write(fp[1],arr1,sizeof(int)*25*100);
		  write(fp[1],arr2,sizeof(int)*25*100);
		   close(fp[1]);
		   
	   } else if(id1==0&&id2!=0){
		   close(fp[1]);
		  read(fp[0],arr1,sizeof(int)*25*100);
		  read(fp[0],arr2,sizeof(int)*25*100);
		   close(fp[0]);
	   }
	   //the first half now is done...
	   //all😃️right.....
	   
	   
	   if(id1!=0&&id2==0){
		   close(f[0]);
		  write(f[1],arr1,sizeof(int)*75*100);
		  write(f[1],arr2,sizeof(int)*75*100);
		   close(f[1]);
		   
	   } else if(id1!=0&&id2!=0){
		   close(f[1]);
		  read(f[0],arr1,sizeof(int)*75*100);
		  read(f[0],arr2,sizeof(int)*75*100);
		   close(f[0]);
	   }
	   //the second half is ready in parent..
	   
	   if(id1==0&&id2!=0){
		   close(p[0]);
		  write(p[1],arr1,sizeof(int)*50*100);
		  write(p[1],arr2,sizeof(int)*50*100);
		   close(p[1]);
		   
	   } else if(id1!=0&&id2!=0){
		   close(p[1]);
		  read(p[0],arr1,sizeof(int)*50*100);
		  read(p[0],arr2,sizeof(int)*50*100);
		   close(p[0]);
	   }
	   //now the full matrix done in the parent..

//tranfer the full matrix back to childs..



      if(id1!=0&&id2!=0){
		   close(fp1[0]);
		  write(fp1[1],arr1,sizeof(int)*100*100);
		  write(fp1[1],arr2,sizeof(int)*100*100);
		   close(fp1[11]);
		   
	   } else if(id1!=0&&id2==0){
		   close(fp1[1]);
		  read(fp1[0],arr1,sizeof(int)*100*100);
		  read(fp1[0],arr2,sizeof(int)*100*100);
		   close(fp1[0]);
	   }
	   
	   if(id1!=0&&id2!=0){
		   close(p1[0]);
		  write(p1[1],arr1,sizeof(int)*100*100);
		  write(p1[1],arr2,sizeof(int)*100*100);
		   close(p1[1]);
		   
	   } else if(id1==0&&id2==0){
		   close(p1[1]);
		  read(p1[0],arr1,sizeof(int)*100*100);
		  read(p1[0],arr2,sizeof(int)*100*100);
		   close(p1[0]);
	   }
	   
           if(id1==0&&id2==0){
		   close(f1[0]);
		  write(f1[1],arr1,sizeof(int)*100*100);
		  write(f1[1],arr2,sizeof(int)*100*100);
		   close(f1[1]);
		   
	   } else if(id1==0&&id2!=0){
		   close(f1[1]);
		  read(f1[0],arr1,sizeof(int)*100*100);
		  read(f1[0],arr2,sizeof(int)*100*100);
		   close(f1[0]);
	   }
	    if(id1!=0&&id2!=0){
		   close(g1[0]);
		  
		  write(g1[1],arr2,sizeof(int)*100*100);
		   close(g1[1]);
		   
	   } else if(id1!=0&&id2==0){
		   close(g1[1]);
		  
		  read(g1[0],arr2,sizeof(int)*100*100);
		   close(g1[0]);
	   }
	  

    
 //now all childs have all things....


		mulfun(arr1,arr2,resarr,sta,en);//done correctly....
		
	
		 
		 if(id1==0&&id2==0){
		   close(fp2[0]);
		  write(fp2[1],resarr,sizeof(int)*25*100);
		 
		   close(fp2[1]);
		   
	   } else if(id1==0&&id2!=0){
		   close(fp2[1]);
		  read(fp2[0],resarr,sizeof(int)*25*100);
		  
		   close(fp2[0]);
	   }
	   //the first😃️ half now is done...
	   //all😃️right.....
	   
	   
	   if(id1!=0&&id2==0){
		   close(f2[0]);
		  write(f2[1],resarr,sizeof(int)*75*100);
		  
		   close(f2[1]);
		   
	   } else if(id1!=0&&id2!=0){
		   close(f2[1]);
		  read(f2[0],resarr,sizeof(int)*75*100);
		  
		   close(f2[0]);
	   }
	   //the 😃️second half is ready in parent..
	   
	   if(id1==0&&id2!=0){
		   close(p2[0]);
		  write(p2[1],resarr,sizeof(int)*50*100);
		 
		   close(p2[1]);
		   
	   } else if(id1!=0&&id2!=0){
		   close(p2[1]);
		  read(p2[0],resarr,sizeof(int)*50*100);
		  
		   close(p2[0]);
	   }
	   
	   
	  
	   
  //😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️😃️
   end=clock();
  if(id1!=0&&id2!=0){
	  wait(NULL);
	 
	  printf("the time it takes is : %fs.\n", ((double)(end-start))/CLOCKS_PER_SEC);
	    
	
  }
   

	return 0;
}

void mulfun(int arr1[100][100],int arr2[100][100],int resarr[100][100],int sta,int en){
	//every process will do a half of job.



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
