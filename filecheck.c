#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include "filecheck.h"

int filecheck (void) {
///////////// Get list of files to hash ////////////////////
     char * filelist_buf6;
     long length6;
     snprintf(file_list6, sizeof(file_list6), "file_list"); 
     FILE* filelist6 = fopen(file_list6, "r");
     FILE* filelist7 = fopen(file_list6, "r");

	if(filelist6 == NULL)
   {     printf("\n");
         printf("ERROR: \n");
         perror("Unable to open list of files!");
	 printf("Create a full path list of files in Ransom Check directoy to hash\n");
         printf("List must be named 'file_list'\n");
         exit(1);
   }

	while (EOF != (c6 = fgetc(filelist6)))
   {
        if (c6 == '\n' && last6 != '\n') {
        ++count6;
   }
        last6 = c6;
   }
//////// Read List of files ////////	 
        cycle_count6 = 0;
        while (fgets(files06, sizeof(files06), filelist7))
        {
           if (cycle_count6 <= count6)
           {
              snprintf(read_file6, sizeof(read_file6), "%s",files06);
              read_file6[strlen(read_file6) - 1] = 0;
	      FILE *read_file7 = fopen(read_file6, "r");
	      if(read_file7 == NULL)
              {
		 printf("\n"); 
		 printf("ERROR: \n"); 
                 perror("Unable to open a file in file_list");
		 printf("Line %d in file_list: %s cannot be opened\n", cycle_count6, read_file6);          
		continue;  
                 //exit(1);
	      
              }
	      //else { 
		 //     printf("File  %d %s is in place\n", cycle_count6, read_file6);
	      //} 
	         
	
//////// MD5 Hash files in list, print to file ////////	      

		 fclose(read_file7);
		 cycle_count6++;
           }

        }
	printf("File check completed. If no errors were shown, all file are in place.\n");


}
