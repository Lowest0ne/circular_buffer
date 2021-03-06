#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Declare the circular buffer
typedef struct circle_node *circle_buffer;

// Initialize the buffer to the desired size
circle_buffer circle_buffer_init( const size_t size );

// Free the memory associated with the buffer
void circle_buffer_destroy( circle_buffer );

// Add a string to the buffer
void circle_buffer_add( circle_buffer, const char* );

// Perform the passed in function on every element in the buffer
// In order that one would expect from a circular buffer
void circle_buffer_perform( circle_buffer, void(*)(const char*) );

#endif
