char file_list5[40];
char file_list6[40];
char read_file5[100]; 
char hash05[MD5_DIGEST_LENGTH]; 
char files05[100];
int count5 = 0; 
int c5;
int cycle_count5;
int new_cycle; 
int last5 = '\n';
unsigned char ml5[MD5_DIGEST_LENGTH];
int bytes5;
unsigned char data5[1024];
MD5_CTX mdContext5;
const char* find_column(char* line, int num); 