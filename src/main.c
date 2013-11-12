#include <stdio.h>
#include "circular_buffer.h"

// The function to call for each element
void my_function( const char* str )
{
  printf( "in function: %s\n", str );
}


int main( void )
{
  // initialize a buffer of size 10
  buffer bf = buffer_init( 10 );

  char tmp[64];
  int i;
  for ( i = 0; i < 15 ; i++ )        // add a string to the buffer 15 times
  {                                  // this will make the buffer go over itself
    sprintf( tmp, "%d", i );
    buffer_add( &bf, tmp  );
  }

  buffer_perform( bf, my_function ); // perform my_function on each element

  // clean up
  buffer_destroy( bf );
  return 0;
}
