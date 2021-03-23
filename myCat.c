#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFSIZE 1024
#define NR_BUF 5

void Oops(char* s1, char* s2){
  
  fprintf(stderr, "error:%s \n", s1);
  perror(s2);
  _exit(1);
}

static int fd = 0;
static char buff[BUFFSIZE * NR_BUF];
static int nr_read = 0;
static int nr_write = 0;
static int bufEnd = 0;
static int pos = 0;

void openFile(char *filename);
int readFile();
void show();

int main(int argc, char* argv[]){
  
  if(argc!=2){
     fprintf(stderr, "Please input command like this: cat file\n", *argv);
    _exit(1);
  }
  openFile(argv[1]);
  int ret;
  while( (ret=readFile(argv[1]))>0 )
    show(); 
  if(ret==-1)
    Oops("read error ", argv[1]);
  else
    printf("\n");
}


void openFile(char* filename)
{
    fd = open(filename, O_RDONLY);
    if(fd==-1)
      Oops("File cannot open",filename);
}

int readFile(char* filename)
{
    *buff = '\0';
    bufEnd = read(fd, buff, BUFFSIZE*NR_BUF);
    nr_read = bufEnd/BUFFSIZE;
    return bufEnd;
}

void show(){
  long int pos = 0;
  while(pos!=nr_read){
    write(1, buff, bufEnd);
    ++pos;
  }
  //pos = bufEnd-pos*BUFFSIZE;
  if(pos<nr_read)
    write(1, buff, BUFFSIZE);
  
}