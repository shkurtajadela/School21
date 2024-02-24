#ifndef DDD_VIEWER_H
#define DDD_VIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.1415926535897932384626433832795028841971693993751

typedef struct data {
  unsigned int count_of_vertexes;
  unsigned int count_of_edges;
  double **array_of_vertexes;
  int **array_of_facets;
  int *vertexes;
  unsigned int numbers_of_vertexes_in_facets;
  int *single_array_for_facets;
  double *single_array_for_vertexes;
} data_t;

int parse_obj_file(char *file_name, struct data *obj);
int allocate_memory_for_array_vertexes_in_facets(char *file_name,
                                                 struct data *obj);
int allocate_memory_for_array_of_vertexes(char *file_name, struct data *obj);
int allocate_memory_for_array_of_facets(char *file_name, struct data *obj);
void centering(double *vertexes, int count_vertexes);
void move_object(data_t *A, double mov_x, double mov_y, double mov_z);
void rotate_object(data_t *A, double angle_x, double angle_y, double angle_z);
void scale_object(data_t *A, double scale);
void free_struct(data_t *A);

#endif  // DDD_VIEWER_H