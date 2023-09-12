#include "parser.h"

void parseObjFile(const char* filename, Gigachad* bigstructarray) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Failed to open file: %s\n", filename);
    return;
  }
  char line[256];
  Gigachad* head = bigstructarray;
  head->vertices = NULL;
  head->numVertices = 0;
  head->faces = NULL;
  head->numFaces = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == 'v' && line[1] == ' ') {
      head->vertices =
          realloc(head->vertices, (head->numVertices + 4) * sizeof(double));
      parseline_vertex(head, line);
    } else if (line[0] == 'f') {
      Face face = {0};
      parseline_faces(&face, line);
      head->faces = realloc(head->faces, (head->numFaces + 1) * sizeof(Face));
      head->faces[head->numFaces] = face;
      head->numFaces++;
    }
  }
  fclose(file);
}

void parseline_vertex(Gigachad* big, char* line) {
  int sign = 1, atof_counter = 0;
  char to_atof[255] = {0};
  while (*line != '\0' && *line != '\n') {
    if (*line == '-') {
      sign = -1;
      line++;
    }
    if (is_digit(*line) || *line == '.') {
      while (is_digit(*line) || *line == '.') {
        to_atof[atof_counter++] = *line++;
      }
      to_atof[atof_counter] = '\0';
      big->vertices[big->numVertices] = atof(to_atof);
      big->vertices[big->numVertices] *= sign;
      big->numVertices++;
    }
    sign = 1;
    atof_counter = 0;
    while (!is_digit(*line) && *line != '-' && *line != '\0' && *line != '\n')
      line++;
  }
}

void parseline_faces(Face* face, char* line) {
  int counter = 0, was_space = 0, sign = 1;
  while (*line != '\0' && *line != '\n') {
    if (*line == '-') {
      sign = -1;
      line++;
    }
    if (is_digit(*line) && was_space) {
      face->vertex_index =
          realloc(face->vertex_index, ((counter + 1) * 2) * sizeof(double));
      face->vertex_index[counter] = atoi(line);
      face->vertex_index[counter] *= sign;
      if (counter != 0) {
        counter++;
        face->vertex_index[counter] = face->vertex_index[counter - 1];
      }
      counter++;
      line++;
      was_space = 0;
    }
    while (*line != ' ' && *line != '\0' && *line != '\n') line++;
    if (*line == ' ') {
      was_space = 1;
      line++;
    }
    sign = 1;
  }
  face->vertex_index[counter] = face->vertex_index[0];
  counter++;
  face->vertexes_per_faceline = counter;
}

int is_digit(char ch) { return (ch <= '9' && ch >= '0'); }

void destroy_gigachads(Gigachad* tail) {
  for (int i = 0; i < tail->numFaces; i++) free(tail->faces[i].vertex_index);
  free(tail->faces);
  free(tail->vertices);
}
