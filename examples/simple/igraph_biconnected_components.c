/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>
#include <stdlib.h>

int sort_and_print_vector(igraph_vector_t *v) {
  long int i, n=igraph_vector_size(v);
  igraph_vector_sort(v);
  for (i=0; i<n; i++) {
    printf(" %li", (long int) VECTOR(*v)[i]);
  }
  printf("\n");
}

void warning_handler_ignore(const char* reason,const char* file,int line,int e) {
}

int main() {
  
  igraph_t g;
  igraph_vector_ptr_t result;
  igraph_es_t es;
  igraph_integer_t no;
  long int i, j, n;
  const int params[] = {4, -1, 2, 2, 0, 0, -1, -1};
 
  igraph_set_warning_handler(warning_handler_ignore);

  igraph_vector_ptr_init(&result, 0);
  igraph_small(&g, 7, 0, 0, 1, 1, 2, 2, 3, 3, 0, 2, 4, 4, 5, 2, 5, -1);
  
  igraph_biconnected_components(&g, &no, 0, 0, &result, 0);
  if (no != 2 || no != igraph_vector_ptr_size(&result)) return 1;
  for (i = 0; i < no; i++) {
    sort_and_print_vector((igraph_vector_t*)VECTOR(result)[i]);
    igraph_vector_destroy((igraph_vector_t*)VECTOR(result)[i]);
  }

  igraph_biconnected_components(&g, &no, 0, &result, 0, 0);
  if (no != 2 || no != igraph_vector_ptr_size(&result)) return 2;
  for (i = 0; i < no; i++) {
    sort_and_print_vector((igraph_vector_t*)VECTOR(result)[i]);
    igraph_vector_destroy((igraph_vector_t*)VECTOR(result)[i]);
  }

  igraph_biconnected_components(&g, &no, &result, 0, 0, 0);
  if (no != 2 || no != igraph_vector_ptr_size(&result)) return 3;
  for (i = 0; i < no; i++) {
    sort_and_print_vector((igraph_vector_t*)VECTOR(result)[i]);
    igraph_vector_destroy((igraph_vector_t*)VECTOR(result)[i]);
  }

  igraph_vector_ptr_destroy(&result);
  igraph_destroy(&g);

  return 0;
}