#include <openssl/md5.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <inttypes.h>
#include "master_check.h"
#include <errno.h>




///////////// CSV parser ////////////////////
const char* find_column(char* line, int num)
{
    const char* FS;
    for (FS = strtok(line, ",");
            FS && *FS;
            FS = strtok(NULL, ",\n"))
    {
        if (!--num)
            return FS;
    }
    return NULL;
}



int master_check(void) {


///////////// Get list of files to hash ////////////////////
     char * filelist_buf5;
     
     long length5;
     snprintf(file_list5, sizeof(file_list5), "file_list"); 
     FILE* filelist5 = fopen(file_list5, "r");
     FILE* filelist6 = fopen(file_list5, "r");

	if(filelist5 == NULL)
   {     printf("\n");
         printf("ERROR: \n");
         perror("Unable to open list of files!");
	 printf("Create a full path list of files in Ransom Check directoy to hash\n");
         printf("List must be named 'file_list'\n");
         exit(1);
   }

	while (EOF != (c5 = fgetc(filelist5)))
   {
        if (c5 == '\n' && last5 != '\n') {
        ++count5;
   }
        last5 = c5;
   }
//////// Read List of files ////////	 
        cycle_count5 = 0;
	while (fgets(files05, sizeof(files05), filelist6))
        {
           if (cycle_count5 <= count5)
           {
              snprintf(read_file5, sizeof(read_file5), "%s",files05);
              read_file5[strlen(read_file5) - 1] = 0;
	      FILE *read_file6 = fopen(read_file5, "r");
	      if(read_file6 == NULL)
              {
		 printf("\n"); 
		 printf("ERROR: \n"); 
                 perror("Unable to open a file in file_list");
		 printf("Line %d in file_list: %s cannot be opened\n", count5, read_file5); 
                 exit(1);
              }

//////// MD5 Hash files in list again for comparison ////////	      
              int p5; 
              MD5_Init (&mdContext5);
              while ((bytes5 = fread (data5, 1, 1024, read_file6)) != 0)
            
              MD5_Update (&mdContext5, data5, bytes5);
              MD5_Final (ml5,&mdContext5);

	      fclose(read_file6);
              cycle_count5++;
         }
	   for(int p5 = 0; p5 <  MD5_DIGEST_LENGTH; ++p5) {
                   sprintf(&hash05[p5*2], "%02x", (unsigned int)ml5[p5]);
              }
         
	   FILE *new_hashes = fopen("new_hashes.csv", "a");
             if (new_hashes == NULL)
              {
               printf("Error opening file!\n");
               exit(1);
               }

               fprintf(new_hashes, "%s\n", hash05);
	       fclose(new_hashes); 
	}
//////// Open original master_hash csv file and compare newest hash////////


              FILE* hashfile = fopen("master_hash.csv", "r");
	         if (hashfile == NULL)
                 {
                    printf("Error opening master_hash.csv file!\n");
                    exit(1);
                 }
	      FILE *old_hashes = fopen("old_hashes.csv", "a");
              char line[1024];
              new_cycle=0;
              char orig_hash[100];
              while (fgets(line, 1024, hashfile))
              {

                   
	             char* tmp = strdup(line);
	             snprintf(orig_hash, sizeof(orig_hash),"%s", find_column(tmp, 2));
              if (old_hashes == NULL)
              {
               printf("Error opening file!\n");
               exit(1);
               }
                
               fprintf(old_hashes, "%s\n", orig_hash);
        
	             new_cycle++;
	             free(tmp);
	       }
	     fclose(old_hashes);
//////////////// Compare Output files ////////////////
void compareFiles(FILE *fp1, FILE *fp2) 
{ 
    char ch1 = getc(fp1); 
    char ch2 = getc(fp2); 
  
    // error keeps track of number of errors 
    int error = 0, pos = 0, line = 0; 
  
    // iterate loop till end of file 
    while (ch1 != EOF && ch2 != EOF) 
    { 
        pos++; 
        if (ch1 == '\n' && ch2 == '\n') 
        { 
            line++; 
            pos = 0; 
        } 
        // error is incremented 
        if (ch1 != ch2) 
        { 
            error++; 
            printf("Line Number : %d \tError"
               " Position : %d \n", line, pos); 
        } 
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
    } 
  
    printf("Total Errors : %d\n", error); 
}

    int ret; 
    int ret2; 

    FILE *fp1 = fopen("old_hashes.csv", "r");
    FILE *fp2 = fopen("new_hashes.csv", "r");

    if (fp1 == NULL || fp2 == NULL)
    {
       printf("Error : Files not open");
       exit(0);
    }

    compareFiles(fp1, fp2);

    fclose(fp1);
    fclose(fp2);
    ret = remove("old_hashes.csv"); 
    ret2 = remove("new_hashes.csv");
    return 0;
      
}
