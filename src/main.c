#include <stdio.h>
#include "circular_buffer.h"

// The function to call for each element
void print( const char* str )
{
  printf( "the value is: %s\n", str );
}


int main( void )
{
  // initialize a buffer of size 10
  circle_buffer bf = circle_buffer_init( 10 );

  char tmp[64];
  int i;
  for ( i = 0; i < 15 ; i++ )        // add a string to the buffer 15 times
  {                                  // this will make the buffer go over itself
    sprintf( tmp, "%d", i );
    circle_buffer_add( bf, tmp  );
  }

  circle_buffer_perform( bf, print ); // perform print on each element

  // clean up
  circle_buffer_destroy( bf );
  return 0;
}
