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
    char name[11];
    char owner;
    int x;
    int y;
    int cell_energy;
    bool cell_moved;
    int num;
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
    char last_team;
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
int show_menu2(void){
    printf("[1] Move\n[2] Split cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
    int q;
    scanf("%d",&q);
    return q;
}
int show_menu_moves(void){
    printf("[1]North\n[2]South\n[3]NorthEast\n[4]NorthWest\n[5]SouthEast\n[6]SouthWest\n");
    int q;
    scanf("%d" , &q);
    return q;

}



void print_cell(cell*head , int n,bool mp){
    cell* current=head;
    int i = 1;
    while(current!=NULL){
        if(mp && current->cell_moved == true) {
            current->num = 0;
            current=current->next;
            continue;
        }
        printf("%d: %s (%d,%d) with %d energy. \n",i,current->name,current->y, n-1-current->x,current->cell_energy);
        current->num = i;
        current=current->next;
        i++;
    }

}

char check_turn(char team,cell*head){
    cell*current=head;

    for(current;current!=NULL;current=current->next)
        if(current->cell_moved==false)return team;

    current=head;
    for(current;current!=NULL;current=current->next){
        current->cell_moved = current->owner == team?true:false;
    }
    if(team == 'X')return 'Y';
    else return 'X';
}

#endif