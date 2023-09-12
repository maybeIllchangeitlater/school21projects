#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned* vertex_index;
  unsigned vertexes_per_faceline;
} Face;

typedef struct Gigachad {
  double* vertices;
  int numVertices;
  Face* faces;
  int numFaces;
} Gigachad;

/**
 * @brief Parses an OBJ file and populates a Gigachad structure with the data.
 *
 * This function reads the contents of the specified OBJ file and extracts
 * the vertex and face data. The resulting data is stored in the provided
 * Gigachad structure.
 *
 * @param filename The name of the OBJ file to parse.
 * @param bigstructarray A pointer to the Gigachad structure to populate.
 */
void parseObjFile(const char* filename, Gigachad* bigstructarray);
/**
 * @brief Parses a line containing vertex data and updates the Gigachad
 * structure.
 *
 * This function takes a line of vertex data from an OBJ file and extracts the
 * vertex information. The extracted vertex information is stored in the
 * provided Gigachad structure.
 *
 * @param big A pointer to the Gigachad structure to update.
 * @param line The line containing vertex data.
 */
void parseline_vertex(Gigachad* big, char* line);
/**
 * @brief Parses a line containing face data and updates the Face structure.
 *
 * This function takes a line of face data from an OBJ file and extracts the
 * face information. The extracted face information is stored in the provided
 * Face structure.
 *
 * @param face A pointer to the Face structure to update.
 * @param line The line containing face data.
 */
void parseline_faces(Face* face, char* line);
/**
 * @brief Destroys a linked list of Gigachad structures.
 *
 * This function frees the memory allocated for each Gigachad structure in
 * the linked list. It should be called to release the memory when the data
 * is no longer needed.
 *
 * @param tail A pointer to the tail of the linked list.
 */
void destroy_gigachads(Gigachad* tail);
/**
 * @brief Checks if a character is a digit.
 *
 * This function determines whether a character represents a digit or not.
 *
 * @param ch The character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
int is_digit(char ch);

#endif
