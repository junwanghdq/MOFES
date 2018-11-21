/*
 * Management Optimization File Experimental System (MOFES)
 *
 * This program is a FUSE simultaion filesystem designed as a practice project for class 519 Operating System Principles. The aims of the development of this filesystem are:
 * 1. Provide a platform for group members to learn about FUSE and filesystem simulation.
 * 2. Practice implementing basic infrastructure for file management.
 * 3. Explore possible optimization of the filesystem management methods (resource allocation procedures). The simulation will provide an environment to test optimization effects by experiments.
 * 4. Gain intuitive and hands-on understanding of differences among popular filesystems on market.
 */


/*
 * Runjia: In the following part, as a start, I provide a basic frame for the FUSE program. The rest of the work is to provide specific callback functions and register them in the entry dictionary. Consistency among workflows implemented by each group member is required. Collaboration is expected.
 */

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <stdlib.h>
#include <stdio.h>


struct fuse_operations mofes_oper = {
// register callback functions here
// Tesint commit pull request from JUN
// Test 2
};

//optional state struct, for security purpose or convenient data access
struct mofes_state {
   FILE *mofes_log;
   char *rootdir;
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
