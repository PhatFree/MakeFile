#include <sys/types.h>
#include <sys/stat.h>
#include<cerrno>
#include<cstdlib>
#include<iostream>

/*  Function "timestamp" returns one of the following values:
    
    a non-zero value
    -1

   a non-zero value means it did not encounter any "bad" errors.  A
   zero value means an error occured.

   When the function returns a non-zero value (1 in this case), the
   value of 'time' is -1 if the file whose name is in 'fname' did not
   exist.  Otherwise, 'time' contains the time-stamp of 'name' in
   terms of number seconds elapsed  since January 1, 1997 (the Unix epoch!)

*/

bool timestamp( const char *fname, long *time )
{
  struct stat finfo;

  if( stat( fname, &finfo ) == 0 ) {
    *time = finfo.st_mtime;
    return true;
  } else if( errno == ENOENT ) {
    *time = -1L;
    return true;
  } else {
    return false;
  }
}


//  Executes the commond 'cmnd' and returns its status.
//  A return value of zero means that the command terminated 
//    successfully.

bool executeCommand( const char *cmnd ) {
    std::cout << cmnd << std::endl;
    return 0 == system( cmnd ); 
}
