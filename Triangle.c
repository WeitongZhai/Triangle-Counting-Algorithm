#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <omp.h>

unsigned long long TheFileSize(char const *filename)
{
   struct stat statbuf;
    int a = stat(filename, &statbuf);
    if (a == -1)
    {
        exit(-1);
     }
       
    
    unsigned long long filesize = statbuf.st_size;
 
    return filesize;
} 


int main(int argc, char const *argv[])
{
    char const *name;
    if (argc < 1)
    {
        printf("error\n");
        exit(1);
    }
    else if (argc == 2)
        name = argv[1];
    else if(argc == 3)
        name = argv[2];

unsigned long long outputsize = TheFileSize(name);

    printf("The file is %lld Bytes.\n", outputsize);
    time_t t0 = time(NULL);

int openfile = open(name, O_RDONLY);
    if (openfile == -1)
    {
        printf("error\n");
        exit(1);
} 

unsigned int *reflect;
    reflect = mmap(NULL, outputsize, PROT_READ, MAP_SHARED, openfile, 0);
    if (reflect == NULL || reflect == (void*)-1)
    {
        printf("error\n");
        close(openfile);
        exit(-2);
}

   unsigned long long numedge = outputsize/8;
   printf("There are %lld edges in the file.\n", numedge);

    long long i,j;
    unsigned int *front;
    unsigned int *behind;
    front = (unsigned int *)malloc(sizeof(unsigned int)*numedge);
    behind = (unsigned int *)malloc(sizeof(unsigned int)*numedge);
    #pragma omp parallel for
    for (i = 0; i < numedge; i++)
    {
        if (reflect[2*i] < reflect[2*i+1])
        {
            front[i] = reflect[2*i];
            behind[i] = reflect[2*i+1];
        }
        else
        {
            front[i] = reflect[2*i+1];
            behind[i] = reflect[2*i];
        }
}

   munmap(reflect, outputsize);
   close(openfile);

   
    unsigned long long count=0;
       //#pragma omp parallel for
   // for (i = 0; i < n_edge; i++)
     //  {for(j=i; j< n_edge; j++)
       //  {
           //   if(front[i] == front[j]&& behind[i] == behind[j])
           //           {front[j] = behind[j]=0;}
       //  }
      //  }
    
       #pragma omp parallel for
    for (i = 0; i < numedge; i++)
     { if(front[i]=front[i+1])
         {
            //sumbehind= behind[i]+behind[i+1];
      
     // }      
      // #pragma omp parallel for      
             for(j=0; j< numedge; j++)
               {
                 if(front[j] == behind[i])
                     
                       {if(behind[j] == behind[i+1])
                             {count++;
                              printf("processing");}
                      }
               }
          }

      }
       if(count&2 == 0)
          printf("The triangles are %lld.\n", count/2 );
       else
          printf("The triangles are %lld.\n", 1+count/2 );
   
printf("Time costs %ld sec.\n", time(NULL) - t0 );
}
