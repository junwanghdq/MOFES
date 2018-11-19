/*
 * Management Optimization File Experimental System (MOFES)
 *
 * This program is a FUSE simultaion filesystem designed as a practice project for class 519 Operating System Principles. 
   The aims of the development of this filesystem are:
 * 1. Provide a platform for group members to learn about FUSE and filesystem simulation.
 * 2. Practice implementing basic infrastructure for file management.
 * 3. Explore possible optimization of the filesystem management methods (resource allocation procedures). 
      The simulation will provide an environment to test optimization effects by experiments.
 * 4. Gain intuitive and hands-on understanding of differences among popular filesystems on market.
 */


/*
 * Runjia: In the following part, as a start, I provide a basic frame for the FUSE program. 
   The rest of the work is to provide specific callback functions and register them in the entry dictionary. 
   Consistency among workflows implemented by each group member is required. Collaboration is expected.
 */

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <stdlib.h>
#include <stdio.h>


struct fuse_operations mofes_oper = {
// register callback functions here
};

//optional state struct, for security purpose or convenient data access
struct mofes_state {
   FILE *mofes_log;
   char *rootdir;
}

/*------------------------------------------------------------------------------------------------------------------------------------------
* writeDir
* 		write the directory to either an open spot or append it
*------------------------------------------------------------------------------------------------------------------------------------------*/
int writeDir(COSC519_directory_entry* entry){
	int index = 0;
	COSC519_directory_entry directory;
	
	//search thorugh each direcotry
	for(getDirAt(index,&directory); getDirAt(index,&directory) != -1; index++)
	{
		//if the current directory is invalid (nFiles == -1) overwrite it
		if(directory.nFiles == -1){
			writeDirAt(index, entry);
			return index;
		}
	}
	
	//if no free directory was found, append the desired directory
	writeDirAt(index, entry);
	return index;
}
/*------------------------------------------------------------------------------------------------------------------------------------------
* writeDirAt
* 		write the directory to the directory index into the file
*------------------------------------------------------------------------------------------------------------------------------------------*/
int writeDirAt(int index, COSC519_directory_entry* entry){
	FILE * dir = getDirectories();
		
	//seek to the directory
	int retcode = fseek(dir, index*sizeof(COSC519_directory_entry), SEEK_SET);

	//write to that location
	int sizeCheck = fwrite(entry, sizeof(COSC519_directory_entry), 1, dir);

	fclose(dir);
	
	//if the write failed, return failure
	if(sizeCheck != 1)return -1;
	return 0;
}

int main(int argc, char* argv [])
{
   int fuse_stat;
   struct mofes_state* mofes_data;
   mofes_data = malloc(sizeof(struct mofes_state));
   if(mofes_data == NULL){
      perror("main calloc");
      abort();
   }
   fuse_stat = fuse_main(argc, argv, &mofes_oper, mofes_data);
   return fuse_stat;
}
