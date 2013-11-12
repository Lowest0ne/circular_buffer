#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// The buffer is implemented as an array of char*
// a user of the buffer should not alter the contents of the struct directly
typedef struct {
  char**   begin;
  char** current;
  char**     end;
} buffer;

// Initialize the buffer to the desired size
buffer buffer_init( const size_t size );

// Free the memory associated with the buffer
void buffer_destroy( buffer );

// Add a string to the buffer
void buffer_add( buffer*, const char* );

// Perform the passed in function on every element in the buffer
// In order that one would expect from a circular buffer
void buffer_perform( buffer, void(*)(const char*) );

#endif
