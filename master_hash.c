#include <openssl/md5.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <inttypes.h>
#include "master_hash.h"
#include <errno.h>

int master_hash (void) {
///////////// Get list of files to hash ////////////////////
//
     if (remove("master_hash.csv") == 0); 
     char * filelist_buf;
     long length;
     snprintf(file_list, sizeof(file_list), "file_list"); 
     FILE* filelist = fopen(file_list, "r");
     FILE* filelist2 = fopen(file_list, "r");

	if(filelist == NULL)
   {     printf("\n");
         printf("ERROR: \n");
         perror("Unable to open list of files!");
	 printf("Create a full path list of files in Ransom Check directoy to hash\n");
         printf("List must be named 'file_list'\n");
         exit(1);
   }

	while (EOF != (c = fgetc(filelist)))
   {
        if (c == '\n' && last != '\n') {
        ++count;
   }
        last = c;
   }
//////// Read List of files ////////	 
        cycle_count = 0;
        while (fgets(files01, sizeof(files01), filelist2))
        {
           if (cycle_count <= count)
           {
              snprintf(read_file, sizeof(read_file), "%s",files01);
              read_file[strlen(read_file) - 1] = 0;
	      FILE *read_file2 = fopen(read_file, "r");
	      if(read_file2 == NULL)
              {
		 printf("\n"); 
		 printf("ERROR: \n"); 
                 perror("Unable to open a file in file_list");
		 printf("Line %d in file_list: %s cannot be opened\n", cycle_count, read_file); 
                 exit(1);
              }
//////// MD5 Hash files in list, print to file ////////	      
              int p; 
	     //////// Get current time ////////  
	      time_t t;
	      char t_buffer[30];
	      struct tm  * tm_date;
	      t = time(NULL); 
	      tm_date = localtime(&t); 
	      strftime(t_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_date);
              
              MD5_Init (&mdContext);
              while ((bytes = fread (data, 1, 1024, read_file2)) != 0)
              MD5_Update (&mdContext, data, bytes);
              MD5_Final (ml,&mdContext);
              for(int p = 0; p <  MD5_DIGEST_LENGTH; ++p)
                   sprintf(&hash01[p*2], "%02x", (unsigned int)ml[p]);
	           printf ("%s: %s\n",hash01, read_file); 
                 FILE *outfile  = fopen("master_hash.csv", "a");
              fprintf(outfile, "%d,%s,%s,%s\n",cycle_count,hash01,read_file,t_buffer);
		 fclose(read_file2);
		 memset(hash01, 0, sizeof(hash01));
		 cycle_count++;
		 fclose(outfile); 
           }

        }

}
