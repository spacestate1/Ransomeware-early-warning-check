#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "ransom_check.h"


void menu01(void)
{
int selection;
 printf("\n\t       Ransomware Check");
  printf("\n\t ");
 printf("\n\tMake Selection");
 printf("\n\t------------------------------");
 printf("\n\t 1. Create files from file_list -f WARNING: removes previous created files!  ");
 printf("\n\t 2. Create initial file hash -i    WARNING: removes old file hash!");
 printf("\n\t 3. Check and compare file hashes to originals -c");
 printf("\n\t 4. Check random files exist -e  ");
 printf("\n\t 5. EXIT");
 printf("\n\n Enter your Choice: ");

///////////////// Main Menu Selection /////////////////
if(scanf("%d",&selection) >=0 && selection <=4)  {
    switch(selection) {
      case 1:
        printf("Files hashed:\n");
	create_file();
        break;

      case 2:
        printf("Checking for filelist...\n");
	master_hash();
        break;

      case 3:
	master_check(); 
        break;

      case 4:
          printf("Checking file locations from file_list \n");
	  filecheck(); 
        break;

      case 5:
          printf("Exit\n");
        break;
      case 6:
        break;

      default:
        printf("Input correct option\n");
        break;
}
}
else { printf("Input correct option\n");
           }

}

///////////////// CLI Select /////////////////
int main(int argc, char* argv[]) {
   int input01 = 0;
   int index;
if(argc == 1) { 

menu01(); 
return 1; 
} 
while ((input01 = getopt(argc, argv, "cifeh")) != -1){ 
    switch(input01)
    {
     case 'i':
     master_hash();
     break; 
     case 'c':
     printf("Checking for filelist\n"); 
     //if (remove("new_hashes.csv.txt") == 0)
     master_check(); 
     break;
     case 'f':
     create_file(); 
     break; 
     case 'e':
     printf("Checking file locations from file_list \n");
     filecheck(); 
     break;
     case 'h':
     printf("Options:\n");
     printf("-c check hashes\n"); 
     printf("-i take initial hashes\n");
     break; 

      default:
        menu01();
     
     
}
    return 0; 
 
}



}



