#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
enum blocks {
    energy = 1,
    mitosis,
    forbidden,
    normal
    };

typedef struct cell{
    char name[10];
    int cell_energy;
    struct cell*next;
}cell;

typedef struct block{
    int x,y;
    int type;
    int block_energy;
    cell* mycell;
}block;
typedef struct game_data{
    bool single_player;
    bool load;
}game_data;

char *rand_string(size_t size) {
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1); str[i] = charset[key];
    }
    str[size] = '\0';
    return str; }
int show_menu(void){
    int q;
    printf("[1]Load\n[2]New single player game\n[3]New Multiplayer game\n[4]Exit\n");
    scanf("%d",&q);
    return q;
}
void print_map(int n,block map[n][n]){
   for(int i = 0;i < n;i++)
    {
      for(int j = 0;j < n;j+=2)
      {
        printf("__________          ");
      }
      printf("\n");
      for(int j = 0;j < n;j+=2)
      {
        printf(" %s          " , map[i][j].type==Energy?" Energy  ":map[i][j].type==Mitosis?" Mitosis ": map[i][j].type==Forbidden?"Forbidden":" Normal  ");
      }
      printf("\n");
      for(int j = 0;j < n;j+=2)
      {
        printf("     %c              " ,map[i][j]!=NULL?'x':' ');
      }
      printf("\n");
      for(int j = 1;j < n;j+=2)
      {
        printf("          __________" );
      }
      printf("\n");
      for(int j = 1;j < n;j+=2)
      {
        printf("          %s " , map[i][j].type==Energy?" Energy  ":map[i][j].type==Mitosis?" Mitosis ": map[i][j].type==Forbidden?"Forbidden":" Normal  ");
      }
      printf("\n");
      for(int j = 1;j < n;j+=2)
      {
        printf("     %c               " ,map[i][j]!=NULL?'x':' ');
      }
      printf("\n");
    }
    for(int j = 0;j < n;j+=2)
    {
      printf("__________          ");
    }
    printf("\n");
    for(int j = 0;j < n;j+=2)
    {
      printf("                    ");
    }
    printf("\n");
    for(int j = 0;j < n;j+=2)
    {
      printf("                    ");
    }
    printf("\n");
    for(int j = 1;j < n;j+=2)
    {
      printf("          __________" );
    }


}
cell *add(int energy,cell*head,int x,int y){
    cell* new_cell = (struct cell*) malloc(sizeof(cell));
    new_cell->cell_energy=energy;
    new_cell->next=NULL;
    strcpy(new_cell->name,rand_string(10));
    if(head==NULL){
        head=new_cell;
        return new_cell;
    }
    cell*current;
    for(current=head;current->next!=NULL;current=current->next);
    current->next=new_cell;
    return new_cell;
}
void remove_cell(cell*head,cell*c){
    cell*current=head;
    for(current=head;current->next!=c;current=current->next);
    current->next=current->next->next;
    free(c);

}



#endif