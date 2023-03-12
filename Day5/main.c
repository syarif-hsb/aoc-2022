#include <stdio.h>
#include <stdlib.h>

#define STACK_WIDTH 10
#define STACK_DEPTH 64
#define STACK_TEMP  10

const int stack_width = STACK_WIDTH;
const int stack_depth = STACK_DEPTH;
char stacks[STACK_WIDTH][STACK_DEPTH] = {
  {'D', 'L', 'J', 'R', 'V', 'G', 'F'},
  {'T', 'P', 'M', 'B', 'V', 'H', 'J', 'S'},
  {'V', 'H', 'M', 'F', 'D', 'G', 'P', 'C'},
  {'M', 'D', 'P', 'N', 'G', 'Q'},
  {'J', 'L', 'H', 'N', 'F'},
  {'N', 'F', 'V', 'Q', 'D', 'G', 'T', 'Z'},
  {'F', 'D', 'B', 'L'},
  {'M', 'J', 'B', 'S', 'V', 'D', 'N'},
  {'G', 'L', 'D'},
};

char stack_pop(int stack_num)
{
  char temp;
  for (int i=stack_depth-1; i>=0; i--){
    if (stacks[stack_num][i]){
      temp = stacks[stack_num][i];
      stacks[stack_num][i] = '\0';
      return temp;
    }
  }

  return '\0';
}

void stack_push(int stack_num, char c)
{
  for (int i=stack_depth-1; i>=0; i--){
    if (stacks[stack_num][i]){
      stacks[stack_num][i+1] = c;
      return;
    }
  }
  stacks[stack_num][0] = c;
}

int do_stack_procedure(int iter_num, int stack_ini, int stack_dst)
{
  /* for (int i=0; i<iter_num; i++){ */
  /*   stack_push(stack_dst, stack_pop(stack_ini)); */
  /* } */

  for (int i=0; i<iter_num; i++){
    stack_push(STACK_TEMP - 1, stack_pop(stack_ini));
  }
  for (int i=0; i<iter_num; i++){
    stack_push(stack_dst, stack_pop(STACK_TEMP - 1));
  }
}

void print_stacks()
{
  for (int i=0; i<stack_width; i++){
    for (int j=0; j<stack_depth; j++) {
      printf("[%c] ", stacks[i][j]);
    }
    printf("\n\n");
  }
}

int read_line(FILE *fstream)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;


  while ((nread = getline(&line, &len, fstream)) != -1) {
    /* printf("Retrieved line of length %zd:\n", nread); */
    int double_digit_iter = 0;
    char iter[3] = { '\0', '\0', '\0' };
    char stack_dst[3] = { '\0', '\0', '\0' };
    char stack_ini[3] = { '\0', '\0', '\0' };
    if (line[0] != 'm')
      continue;
    fwrite(line, nread, 1, stdout);
    iter[0] = line[5];
    if (line[6] != ' ') {
      iter[1] = line[6];
      double_digit_iter = 1;
    }
    stack_ini[0] = line[12 + double_digit_iter];
    stack_dst[0] = line[17 + double_digit_iter];
    /* print_stacks(); */
    /* printf("%d\n", atoi(stack_ini)); */
    /* printf("%d\n", atoi(stack_dst)); */
    do_stack_procedure(atoi(iter), atoi(stack_ini) - 1, atoi(stack_dst) - 1);
  }
    print_stacks();

  free(line);
}

int main(int argc, char *argv[])
{
  FILE *fstream;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fstream = fopen(argv[1], "r");
  if (fstream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  /* printf("%c\n", stack_pop(1)); */
  print_stacks();

  read_line(fstream);

  /* print_stacks(); */
  /* stack_push(2, stack_pop(1)); */

  fclose(fstream);
  exit(EXIT_SUCCESS);
  return 0;
}
