#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

static DIR* dir;
void show(struct dirent* dr, int i);
int main(int argc, char* argv[]){
  
  if(argc==1){
   
     dir = opendir(".");
     if(dir!=NULL){
       struct dirent* dr;
	while( (dr=readdir(dir))!=NULL){
	    show(dr, 1);
	}
	printf("\n");
     }
     
     closedir(dir);
  }
  
  
}

void show(struct dirent* dr, int i){
  switch(i){
    
    case 1:
       if(strcmp(dr->d_name,".")!=0 && strcmp(dr->d_name, "..")!=0)
	  printf("%s ", dr->d_name);
       
    
  }
   
}
