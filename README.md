This program is intended to help with the detection of crypto-malware. 

It creates files containing random text from a manually generated list containing file paths and names. Once the files are created, an MD5 hash is taken of each file and recorded in a master list text file. The original hash is then compared to new hashes taken for each file based on a manual execution, cron or other scheduler, if differences are found between old and hashes and new ones, they are reported. 

The random files are placed based on a plain text list which needs to be manually created named file_list.

To compile and use on Linux: 

./Makefile

./ransom_check

Ransomware Check Menu and cli flags

1. Create files from file_list -f WARNING: removes previous created files!
2. Create initial file hash -i    WARNING: removes old file hash!
3. Check and compare file hashes to originals -c
4. Check random files exist -e 
5. EXIT
