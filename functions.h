#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
enum blocks {
    Energy = 1,
    Mitosis,
    Forbidden,
    Normal
    };

typedef struct cell{
    char name[10];
    char owner;
    int x;
    int y;
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
    char *str = (char*)malloc((size + 1) * sizeof(char));
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


void remove_cell(cell*head,cell*c){
    cell*current=head;
    for(current=head;current->next!=c;current=current->next);
    current->next=current->next->next;
    free(c);

}
void print_cell(cell*head){
	cell* current=head;
	while(current!=NULL){
		printf("(%d,%d) ",current->y, current->x);
		printf("%s\n",current->name);
		current=current->next;
	}
}



#endif
