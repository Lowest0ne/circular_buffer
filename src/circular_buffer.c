#include "circular_buffer.h"
/*******************************************************************************
 * buffer buffer_init( const size_t )
 *
 * initialize and return an empty buffer
 ******************************************************************************/
circle_buffer circle_buffer_init( const size_t size )
{
  if ( size == 0 ) return NULL;

  circle_buffer bf = malloc ( sizeof( struct circle_node ) );
  if ( !bf ) return NULL;

  // allocate memory and intialize contents of struct
  bf->begin = malloc( size * sizeof( char* ) );
  if ( !bf->begin )
  {
    free ( bf );
    return NULL;
  }

  bf->current = bf->begin;
  bf->end = bf->begin + size;

  // set all char* to NULL
  char **pointer = bf->begin;
  while ( pointer < bf->end )
    *pointer++ = NULL;

  return bf;
}
/*******************************************************************************
 * void buffer_destroy( buffer )
 *
 * free memory allocated from buffer
 ******************************************************************************/
void circle_buffer_destroy( circle_buffer bf )
{
  assert( bf->end > bf->begin );

  // free each char*
  char** current = bf->begin;
  while ( current < bf->end )
    free ( *current++ );

  // free the buffer
  free( bf->begin );
  free( bf );
}
/*******************************************************************************
 * void buffer_add( buffer, const char* )
 *
 * add a string to the buffer
 ******************************************************************************/
void circle_buffer_add( circle_buffer bf, const char* str)
{

  // free the memory for the new element to use
  if ( *(bf->current) )
  {
    free ( *( bf->current ) );
    *(bf->current) = NULL;
  }

  // allocate space and copy string into buffer
  *(bf->current) = malloc( strlen( str ) + 1 );
  strcpy( *(bf->current), str );

  // increment the current pointer
  if ( ++bf->current == bf->end ) bf->current = bf->begin;

}
/*******************************************************************************
 * void buffer_perform( buffer bf, void(*)(const char*) )
 *
 * call the passed in method once per item
 ******************************************************************************/
void circle_buffer_perform( circle_buffer bf, void(*func)(const char*) )
{
  assert ( bf->begin <= bf->current && bf->current < bf->end );

  char **pointer = NULL;

  if ( *(bf->current) )            // if the current pointer exists
  {                                // the buffer has been filled
    pointer = bf->current;         // set pointer to current
    while ( pointer != bf->end )
      func( *pointer++ );          // call func and incriment until end
  }

  pointer = bf->begin;             // set the pointer to the begin
  while ( pointer != bf->current ) // call func and incriment until current
    func( *pointer++ );

}
