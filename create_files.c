#include <stdio.h> 
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include "create_files.h"

#include <unistd.h>
#include <fcntl.h>
#define MAX_SIZE 256

int create_file(void) { 
//////// Get list of files ////////
     char * filelist_buf1;
     long length1;
     snprintf(file_list3, sizeof(file_list3), "file_list");
     FILE* filelist3 = fopen(file_list3, "r");
     FILE* filelist4 = fopen(file_list3, "r");

        if(filelist3 == NULL)
   {     printf("\n");
         printf("ERROR: \n");
         perror("Unable to open list of files!");
         printf("Create a full path list of files in Ransom Check directoy to hash\n");
         printf("List must be named 'file_list'\n");
         exit(1);
   }

        while (EOF != (c1 = fgetc(filelist3)))
   {
        if (c1 == '\n' && last1 != '\n') {
        ++count1;
   }
        last1 = c1;
   }
//////// Read List of files and create them ////////     
        cycle_count1 = 0;
	int t2;
        while (fgets(files02, sizeof(files02), filelist4))
        {
           if (cycle_count1 <= count1)
           {
              snprintf(read_file1, sizeof(read_file1), "%s",files02);
              read_file1[strlen(read_file1) - 1] = 0;
	      if (remove(read_file1) == 0)
                  printf("Old %s removed successfully\n", read_file1);
              printf("File %s created.\n",read_file1);
	      FILE *newfile = fopen(read_file1, "ab+");
              int num01;
              FILE *fp;
              fp = fopen("/dev/urandom", "r");
              fread((char*)(&num01),sizeof(num01),2,fp);
	      fprintf(newfile, "%d\n", num01);
              fclose(fp);
              fclose(newfile); 
              cycle_count1++;
	   }
}
}


