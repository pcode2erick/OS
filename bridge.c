#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char *card[52];
	int noOfPlayer=4,size=13,pid,i,j=1,k,z,a;
	int numCard[52],points[4]={0},adjPts[4]={0};
	char suit[4]={'S','D','H','C'};
	char rank[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
	//distribute the cards
	for(k=0;k<52;k++){
           card[k] = argv[j];
           j++;
        }
     //for(i=0;i<52;i++){
     //printf("%s, ",card[i]);
     //}
     //printf("\n");
             //Create process
             for(i=0;i<noOfPlayer;i++){
             pid = fork();
             if(pid<0){
             printf("Fork Fail!");
             exit(1); 
             }
             else if(pid == 0){  //child process
             char *hand[size];
	     int counter[4][2]={0};
             for(z=0;z<size;z++){
             hand[z] = card[noOfPlayer*z+i];
             }
             printf("Child %d, pid %d: ",i+1,getpid());
             for(z=0;z<size;z++){
             printf("%s ",hand[z]);      	
             }        
             printf("\n"); 
             //sort the card
	     for(z=0;z<13;z++){
		for(a=0;a<13;a++){
		    if(hand[z][0]==suit[0] && hand[z][1]==rank[a]){
			numCard[z]=a;
			}
		    if(hand[z][0]==suit[1] && hand[z][1]==rank[a]){
			numCard[z]=13+a;
			}
		     if(hand[z][0]==suit[2] && hand[z][1]==rank[a]){
			numCard[z]=2*13+a;
			}
		     if(hand[z][0]==suit[3] && hand[z][1]==rank[a]){
			numCard[z]=3*13+a;
			}
			}
			}
			char *temp;
			int temp1;	 
			for(z=0;z<13;z++){
			for(a=1;a<13;a++){
			    if(numCard[a]<numCard[a-1]){
			       temp1=numCard[a];
			       numCard[a]=numCard[a-1];
			       numCard[a-1]=temp1;
			       temp=hand[a];
			       hand[a]=hand[a-1];
			       hand[a-1]=temp;
				
			}
			}
			}
                 
	     printf("Child %d, pid %d: ",i+1,getpid());   
             for(z=0;z<size;z++){
	        if(hand[z][0]=='S'){
                counter[0][0]=z;
                counter[0][1]++;
             }
               if(hand[z][0]=='D'){
                 counter[1][0]=z;
                 counter[1][1]++;
             }
             if(hand[z][0]=='H'){
                 counter[2][0]=z;
                 counter[2][1]++;
             }
             if(hand[z][0]=='C'){
                 counter[3][0]=z;
                 counter[3][1]++;
             }
             }
	
	     for(z=0;z<4;z++){
              printf("<");
	      for(a=(counter[z][0]-counter[z][1]+1);a<=counter[z][0];a++){
                 printf("%s ",hand[a]);
                
             }
              printf(">");
	     }  
		 for(z=0;z<size;z++){
		         if(hand[z][1]=='A'){
                  points[i]=points[i]+4;                  
                  } 
                 if(hand[z][1]=='K'){
                  points[i]=points[i]+3;                  
                   }
                  if(hand[z][1]=='Q'){
                   points[i]=points[i]+2;
                  }
                   if(hand[z][1]=='J'){
                    points[i]=points[i]+1;
		         }
				
		 }
		 	 for(a=0;a<4;a++){
				   if(counter[a][1]==0 || counter[a][1]==7){   //void
					   adjPts[i]=adjPts[i]+3;
				   }
				   if(counter[a][1]==1){   //singleton 
				   adjPts[i]=adjPts[i]+2;
				      if(hand[counter[a][0]][1]=='K' || hand[counter[a][0]][1]=='Q'|| hand[counter[a][0]][1]=='J'|| hand[counter[a][0]][1]=='A'){
						  adjPts[i]=adjPts[i]-1;
				   }
				   }
				   if(counter[a][1]==6){ 
					   adjPts[i]=adjPts[i]+2;
				   }
				   if(counter[a][1]==2 || counter[a][1]==5){   //doubleton
					   adjPts[i]=adjPts[i]+1;
				   }
		 }			   
             printf("\n");
             //display Point
			 printf("Child %d, pid %d: ",i+1,getpid());
			 printf("%d points, %d adjusted points\n",points[i],(points[i]+adjPts[i]));
	     
             exit(0);                                 
             }
             else{ //parent process
             wait(NULL);          
             }                        
             }
             wait(NULL);                      
	}