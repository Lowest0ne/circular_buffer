#include "circular_buffer.h"
/*******************************************************************************
 * buffer buffer_init( const size_t )
 *
 * initialize and return an empty buffer
 ******************************************************************************/
buffer buffer_init( const size_t size )
{
  buffer bf;

  // allocate memory and intialize contents of struct
  bf.begin = malloc( size * sizeof( char* ) );
  bf.current = bf.begin;
  bf.end = bf.begin + size;

  // set all char* to NULL
  size_t i;
  for ( i = 0; i < size; ++i ) *(bf.begin + i) = NULL;

  return bf;
}
/*******************************************************************************
 * void buffer_destroy( buffer )
 *
 * free memory allocated from buffer
 ******************************************************************************/
void buffer_destroy( buffer bf )
{
  // free each char*
  size_t i;
  for ( i = 0; i < bf.end - bf.begin; ++i )
    free( *(bf.begin + i ) );

  // free the buffer
  free( bf.begin );
}
/*******************************************************************************
 * void buffer_add( buffer, const char* )
 *
 * add a string to the buffer
 ******************************************************************************/
void buffer_add( buffer* bf, const char* str)
{

  // free the memory for the new element to use
  if ( *(bf->current) )
  {
    free ( *( bf->current ) );
    *(bf->current) = NULL;
  }

  // allocate space and copy string into buffer
  size_t length = strlen( str );
  *(bf->current) = malloc( length + 1 );
  strcpy( *(bf->current), str );

  // increment the current pointer
  ++bf->current;
  if ( bf->current == bf->end ) bf->current = bf->begin;

}
/*******************************************************************************
 * void buffer_perform( buffer bf, void(*)(const char*) )
 *
 * call the passed in method once per item
 ******************************************************************************/
void buffer_perform( buffer bf, void(*func)(const char*) )
{
  char **pointer = NULL;

  if ( *(bf.current) )               // if the current pointer exists
  {                                  // the buffer has been filled
    pointer = bf.current;            // set pointer to current
    while ( pointer != bf.end )
      func( *pointer++ );            // call func and incriment until end
  }

  pointer = bf.begin;                // set the pointer to the begin
  while ( pointer != bf.current )    // call func and incriment until current
    func( *pointer++ );

}





