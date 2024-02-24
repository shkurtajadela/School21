#include "ddd_viewer.h"

void move_object(data_t *A, double mov_x, double mov_y, double mov_z) {
  for (unsigned int i = 0; i < A->count_of_vertexes * 3; i += 3) {
    A->single_array_for_vertexes[i] += mov_x;
    A->single_array_for_vertexes[i + 1] += mov_y;
    A->single_array_for_vertexes[i + 2] += mov_z;
  }
}

static double sin_cos(char function, double degrees) {
  return (function == 's') ? sin(degrees * M_PI / 180)
                           : cos(degrees * M_PI / 180);
}

void rotate_object(data_t *A, double angle_x, double angle_y, double angle_z) {
  double sin_x = sin_cos('s', angle_x), cos_x = sin_cos('c', angle_x);
  double sin_y = sin_cos('s', angle_y), cos_y = sin_cos('c', angle_y);
  double sin_z = sin_cos('s', angle_z), cos_z = sin_cos('c', angle_z);
  for (unsigned int i = 0; i < A->count_of_vertexes * 3; i += 3) {
    double x = A->single_array_for_vertexes[i];
    double y = A->single_array_for_vertexes[i + 1];
    double z = A->single_array_for_vertexes[i + 2];
    double temp_y = cos_x * y - sin_x * z;
    double temp_z = sin_x * y + cos_x * z;
    double temp_x = cos_y * x + sin_y * temp_z;
    z = -sin_y * x + cos_y * temp_z;
    x = cos_z * temp_x - sin_z * temp_y;
    y = sin_z * temp_x + cos_z * temp_y;
    A->single_array_for_vertexes[i] = x;
    A->single_array_for_vertexes[i + 1] = y;
    A->single_array_for_vertexes[i + 2] = z;
  }
}

void scale_object(data_t *A, double scale) {
  for (unsigned int i = 0; i < A->count_of_vertexes * 3; i++) {
    A->single_array_for_vertexes[i] *= scale;
  }
}

void free_struct(data_t *A) {
  if (A) {
    if (A->single_array_for_facets) {
      free(A->single_array_for_facets);
      A->single_array_for_facets = NULL;
    }
    if (A->vertexes) {
      free(A->vertexes);
      A->vertexes = NULL;
    }
    if (A->single_array_for_vertexes) {
      free(A->single_array_for_vertexes);
      A->single_array_for_vertexes = NULL;
    }
    for (unsigned int i = 0; i < A->count_of_vertexes; i++) {
      if (A->array_of_vertexes[i]) {
        free(A->array_of_vertexes[i]);
        A->array_of_vertexes[i] = NULL;
      }
    }
    if (A->array_of_vertexes) {
      free(A->array_of_vertexes);
      A->array_of_vertexes = NULL;
    }
    for (unsigned int i = 0; i < A->count_of_edges; i++) {
      if (A->array_of_facets[i]) {
        free(A->array_of_facets[i]);
        A->array_of_facets[i] = NULL;
      }
    }
    if (A->array_of_facets) {
      free(A->array_of_facets);
      A->array_of_facets = NULL;
    }
    if (A) {
      free(A);
      A = NULL;
    }
  }
}

int parse_obj_file(char *file_name, struct data *obj) {
  int status = -1;
  FILE *file = NULL;
  char buffer[1000000];
  obj->count_of_vertexes = 0;
  obj->count_of_edges = 0;
  obj->numbers_of_vertexes_in_facets = 0;
  if (!(file = fopen(file_name, "r"))) {
    printf("Ошибка: не удалось открыть файл\n");
    status = -1;
  } else {
    while (fgets(buffer, 1000000, file)) {
      if (strncmp(buffer, "v ", 2) == 0) {
        (obj->count_of_vertexes)++;
        status = 1;
      } else if (strncmp(buffer, "f ", 2) == 0) {
        (obj->count_of_edges)++;
        status = 1;
      } else if (obj->count_of_vertexes == 0) {
        status = -1;
      }
    }
    fclose(file);
  }
  return status;
}

int allocate_memory_for_array_vertexes_in_facets(char *file_name,
                                                 struct data *obj) {
  int status = 0;
  char buffer[1000000];
  char *istr = NULL;
  int i = 0;
  obj->vertexes = (int *)calloc(obj->count_of_edges, sizeof(int));
  if (obj->vertexes == NULL) {
    printf(
        "Ошибка: не удалось выделить память под массив вершин "
        "многоугольников\n");
    status = -1;
  }
  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("Ошибка: не удалось открыть файл\n");
    status = -1;
  } else {
    while (fgets(buffer, 1000000, file) != NULL) {
      int vertex_num;
      if (sscanf(buffer, "f %d", &vertex_num) == 1) {
        obj->vertexes[i] = 0;
        istr = strtok(buffer, "f ");
        while (istr != NULL) {
          int vertex_idx;
          if (sscanf(istr, "%d", &vertex_idx) == 1) {
            (obj->vertexes[i]) += 1;
          }
          istr = strtok(NULL, " ");
        }
        i++;
      }
    }
    status = 1;
    fclose(file);
  }
  return status;
}

int allocate_memory_for_array_of_vertexes(char *file_name, struct data *obj) {
  int status = 0;
  char buffer[1000000];
  char *istr = NULL;
  obj->array_of_vertexes =
      (double **)calloc(obj->count_of_vertexes, sizeof(double *));
  if (obj->array_of_vertexes == NULL) {
    status = -1;
  }
  for (unsigned int i = 0; i < obj->count_of_vertexes; i++) {
    obj->array_of_vertexes[i] = (double *)calloc(3, sizeof(double));
    if (obj->array_of_vertexes[i] == NULL) {
      for (unsigned int j = 0; j < i; j++) {
        free(obj->array_of_vertexes[j]);
      }
      free(obj->array_of_vertexes);
      status = -1;
    }
  }
  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("Ошибка: не удалось открыть файл\n");
    status = -1;
  } else {
    for (int i = 0; !feof(file);) {
      fgets(buffer, 1000000, file);
      if (!strncmp(buffer, "v ", 2)) {
        istr = strtok(buffer, "v ");
        obj->array_of_vertexes[i][0] = atof(istr);
        istr = strtok(NULL, " ");
        obj->array_of_vertexes[i][1] = atof(istr);
        istr = strtok(NULL, " ");
        obj->array_of_vertexes[i][2] = atof(istr);
        i++;
      }
    }
    obj->single_array_for_vertexes =
        (double *)calloc((obj->count_of_vertexes * 3), sizeof(double));
    if (obj->single_array_for_vertexes) {
      for (unsigned int i = 0, k = 0; i < obj->count_of_vertexes; i++) {
        obj->single_array_for_vertexes[k] = obj->array_of_vertexes[i][0];
        obj->single_array_for_vertexes[k + 1] = obj->array_of_vertexes[i][1];
        obj->single_array_for_vertexes[k + 2] = obj->array_of_vertexes[i][2];
        k += 3;
      }
      status = 1;
    } else {
      status = -1;
    }
    fclose(file);
  }
  return status;
}

int allocate_memory_for_array_of_facets(char *file_name, struct data *obj) {
  int status = 0;
  char buffer[1000000];
  obj->array_of_facets = (int **)calloc(obj->count_of_edges, sizeof(int *));
  if (obj->array_of_facets == NULL) {
    status = -1;
  }
  for (unsigned int i = 0; i < obj->count_of_edges; i++) {
    obj->array_of_facets[i] = (int *)calloc(obj->vertexes[i], sizeof(int));
    if (obj->array_of_facets[i] == NULL) {
      status = -1;
    }
  }
  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("Ошибка: не удалось открыть файл\n");
    status = -1;
  } else {
    int i = 0;
    while (fgets(buffer, 1000000, file)) {
      if (strncmp(buffer, "f ", 2) == 0) {
        char *istr = strtok(buffer, "f ");
        obj->array_of_facets[i][0] = atoi(istr);
        obj->numbers_of_vertexes_in_facets =
            obj->numbers_of_vertexes_in_facets + 1;
        for (int j = 1; j < obj->vertexes[i]; j++) {
          istr = strtok(NULL, " ");
          obj->array_of_facets[i][j] = atoi(istr);
          obj->numbers_of_vertexes_in_facets =
              obj->numbers_of_vertexes_in_facets + 1;
        }
        i++;
      }
      status = 1;
    }
    obj->numbers_of_vertexes_in_facets *= 2;
    obj->single_array_for_facets =
        (int *)calloc(obj->numbers_of_vertexes_in_facets, sizeof(int));
    if (obj->single_array_for_facets) {
      for (unsigned int i = 0, k = 0; i < obj->count_of_edges; i++) {
        for (int j = 0; j < (obj->vertexes[i]); j++) {
          if (j == 0) {
            obj->single_array_for_facets[k] = obj->array_of_facets[i][0];
            obj->single_array_for_facets[k + obj->vertexes[i] * 2 - 1] =
                obj->array_of_facets[i][j];
          } else {
            obj->single_array_for_facets[k - 1] = obj->array_of_facets[i][j];
            obj->single_array_for_facets[k] = obj->array_of_facets[i][j];
          }
          k += 2;
        }
      }
    } else {
      status = -1;
    }
    fclose(file);
  }
  return status;
}