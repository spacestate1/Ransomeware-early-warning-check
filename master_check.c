#include <openssl/md5.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <inttypes.h>
#include "master_check.h"
#include <errno.h>
#include <stdbool.h>

#define LSIZ 500

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
///////////// array compare ////////////////////
bool array_c(char *a_string, char array[][LSIZ], size_t arraySize)
{
    for (int array_count = 0; array_count < arraySize; ++array_count) {
       //if (array[array_count] == a_string) 
       if (strcmp(array[array_count], a_string)== 0){

           return (true);
       }
    }

    return (false);
}
//////////////  Remove Blanks From array //////////////
size_t remove_blank( char ( *s )[10], size_t n )
{
    size_t blank_count = 0;

    while ( blank_count < n && !( s[blank_count][0] == '\0' ) ) ++blank_count;

    for ( size_t j = blank_count + 1; j < n; j++ )
    {
        if ( s[j][0] != '\0' )
        {
            strcpy( s[blank_count], s[j] );
            ++blank_count;
        }
    }

    for( size_t j = blank_count; j < n; j++ ) s[j][0] = '\0';

    return blank_count;
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
/////////////// Count lines in file one based on newline ///////////////
    int finalcount = 0; 
    int ret; 
    int ret2; 
    char finalc; 
    FILE *newfile01 = fopen("new_hashes.csv", "r"); 

    if (newfile01 == NULL)
    {
        printf("Could not open file\n");
        return 0;
    }

    for (finalc = getc(newfile01); finalc != EOF; finalc = getc(newfile01))
        if (finalc == '\n')
            finalcount = finalcount + 1;
         //printf("new file lines: %d\n", finalcount);  

    fclose(newfile01);
/////////////// Count lines in file two based on newline ///////////////
    int finalcount2 = 0;

    char finalc2;
    FILE *oldfile01 = fopen("old_hashes.csv", "r");

    if (oldfile01 == NULL)
    {
        printf("Could not open file\n");
        return 0;
    }

    for (finalc2 = getc(oldfile01); finalc2 != EOF; finalc2 = getc(oldfile01))
        if (finalc2 == '\n') 
            finalcount2 = finalcount2 + 1;

    fclose(oldfile01);

  /////////////// Create Array from file one  ///////////////



    char finalline[finalcount][LSIZ];
    int finali = 0;
    int tot = 0;
    FILE * fptr = fopen("new_hashes.csv", "r");
    while(fgets(finalline[finali], LSIZ, fptr)) 
	{
        finalline[finali][strlen(finalline[finali]) - 1] = '\0';
        finali++;
    }
    tot = finali;
/////////////// Create Array from file two  ///////////////
   char finalline2[finalcount2][LSIZ];
    int finali2 = 0;
    int tot2 = 0;
    FILE * fptr2 = fopen("old_hashes.csv", "r");
    while(fgets(finalline2[finali2], LSIZ, fptr2))
        {
        finalline2[finali2][strlen(finalline2[finali2]) - 1] = '\0';
        finali2++;
    }
    tot2 = finali2;
    
    
 ////////// Compare Files From two arrays //////////   
int matches = 0;
int mis_matches = 0; 
int mis_count = 0;
char mismatches_found[finalcount][LSIZ];
    for(finali2 = 0; finali2 < finalcount; ++finali2)
    {  
	if(!array_c(finalline[finali2],finalline2, finalcount2)) 
	{
	  strcpy(mismatches_found[mis_matches], finalline2[finali2]);
	  mis_matches++;
	   }
       for(finali = 0; finali < finalcount; ++finali)
          {
            if (strcmp(finalline2[finali2], finalline[finali]) == 0)
             { 
	       matches++;
            } 

	  else {
		 continue; 
	  } 
	}
    }
  printf("MAtches %d\n", matches); 
      
  if (matches ==  finalcount)
  {  printf("No Errors found\n"); 
     printf("%d out of %d Matches found.\n", matches, finalcount);
  }
  else 
  { 
    printf("ERROR %d matches out of %d found\n", matches, finalcount2); 

  }
  for (mis_count= 0; mis_count <  mis_matches; mis_count++){
	  printf("not matching %s\n", mismatches_found[mis_count]); 
  }
	
  
 ret = remove("old_hashes.csv");
 ret2 = remove("new_hashes.csv");
return 0; 
    

}
