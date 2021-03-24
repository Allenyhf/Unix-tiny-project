#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

static DIR* dir;
void do_ls_1(char* ls_dir, int showDir);
void do_ls_2(char* ls_dir);


int main(int argc, char* argv[]){
  
  switch(argc){
    case 1:
	  do_ls_1(".", 0);
	  break;
    case 2:
	  if(strcmp(argv[1],"-a")==0)
	     do_ls_1(".", 1);
	  else if(strcmp(argv[1],"-l")==0)
	     do_ls_2(".");
	  else if(*argv[1]=='-')
	     printf("only option: -a provided!\n");
	  else
	    do_ls_1(argv[1], 0);
	  break;
    case 3:
	  break;
  }
  
  
  
}

void do_ls_1(char *ls_dir, int showDir){
    DIR* dir;
    dir = opendir(ls_dir);
    if(dir==NULL){
	fprintf(stderr,"open directory error: %s", ls_dir);
	exit(1);
    }
    
    struct dirent* ent;
    
    while((ent = readdir(dir))!=NULL){
      if(showDir)
	printf("%s ", ent->d_name);
      else if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)
	continue;
      else printf("%s ", ent->d_name);
    }
   printf("\n");
}


void do_ls_2(char* ls_dir)
{
    DIR* dir;
    dir = opendir(ls_dir);
    if(dir==NULL){
	fprintf(stderr, "open directory error: %s\n", ls_dir);
	exit(1);
    }
    int ret = 0;
    struct dirent* ent;
    struct stat* buff;
    buff = (struct stat*)malloc(sizeof(struct stat*));
    time_t tm;
    char* time = (char *)malloc(sizeof(char)*20);
    char* tmp = (char *)malloc(sizeof(char)*16);
    memset(time, 0, sizeof(time));
    memset(tmp, 0, sizeof(tmp));
    while( (ent=readdir(dir))!=NULL){
      if(strcmp(ent->d_name, ".")==0||strcmp(ent->d_name, "..")==0)
	continue;
      ret = stat(ent->d_name, buff);
      if(ret==-1){
	perror(ent->d_name);
	exit(1);
      }
      //mode
      printf("%d ", buff->st_nlink);
      printf("%d ",buff->st_uid);
      printf("%d ", buff->st_gid);
      printf("%ld ", buff->st_size);
      tmp = ctime(&buff->st_atim);
      strncpy(time, tmp, 16);
      //strncpy(time+16,' ', 2);
      printf("%s", tmp);
      printf("\t");
      printf("%s\n", ent->d_name);
    }
  
}

