#include "functions.h"
#include <curses.h>

#define forfor(X) for(int i=0;i<X;i++)for(int j=0;j<X;j++)
game_data game;
int n,s;
bool isEmpty(int x,int y,block map[n][n]);
cell *add(int energy,int x,int y);
void remove_cell(cell*c);
void print_map(int n,block map[n][n]){
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j+=2)
        {
            printf("\x1b[41m          \x1b[0m          ");
        }
        printf("\n");
        for(int j = 0;j < n;j+=2)
        {
            printf(" \x1b[33m%s\x1b[0m          " , map[i][j].type==Energy?" ENERGY  ":map[i][j].type==Mitosis?" MITOSIS ": map[i][j].type==Forbidden?"FORBIDDEN":" NORMAL  ");
        }
        printf("\n");
        for(int j = 0;j < n;j+=2)
        {
            printf("     \x1b[32m%c              " ,map[i][j].mycell!=NULL?map[i][j].mycell->owner:' ');
        }
        printf("\n");
        for(int j = 1;j < n;j+=2)
        {
            printf("          \x1b[44m          \x1b[0m" );
        }
        printf("\n");
        for(int j = 1;j < n;j+=2)
        {
            printf("          \x1b[33m%s\x1b[0m " , map[i][j].type==Energy?" ENERGY  ":map[i][j].type==Mitosis?" MITOSIS ": map[i][j].type==Forbidden?"FORBIDDEN":" NORMAL  ");
        }
        printf("\n");
        for(int j = 1;j < n;j+=2)
        {
            printf("             \x1b[32m%c       " ,map[i][j].mycell!=NULL?map[i][j].mycell->owner:' ');
        }
        printf("\n");
    }
    for(int j = 0;j < n;j+=2)
    {
        printf("\x1b[41m          \x1b[0m          ");
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
        printf("          \x1b[44m          \x1b[0m" );
    }
    printf("\n");
}
cell * head = NULL;
int main() {
    srand(time(NULL));
    while(1){
        game.load=false;
        game.single_player=true;
        head=NULL;
      start_point:;
        int menu_input = show_menu();
          if(menu_input>=5){
              printf("+++++++++++++++\n");
              printf("!!Wrong input!!\n");
              printf("+++++++++++++++\n");
              goto start_point;}

        switch(menu_input){
            case 4:
                exit(0);
            case 1:
                game.load=true;
            case 3:
                if(game.load==false)
                    game.single_player=false;
            case 2:;
                FILE* ptf;
                head=NULL;
                if(!game.load){
                    openfile:
                    printf("Please enter map file name: ");
                    char str[100];
                    scanf("%s",str);
                    ptf =fopen(str,"rb");
                    if(ptf==NULL){
                        printf("Cannot open the file %s.\n",str);
                        goto openfile;
                    }
                }
                else
                {
                    ptf=fopen("save_map.bin","rb");
                }
                fread(&n,sizeof(n),1,ptf);
                block arr_block[n][n];
                if(!game.load){
                    forfor(n){

                            unsigned char temp;
                            fread(&temp,sizeof(unsigned char),1,ptf);
                            int tmp = temp - '0';
                            arr_block[i][j].type = tmp;
                            arr_block[i][j].x = i;
                            arr_block[i][j].y = j;
                            arr_block[i][j].block_energy = 100;
                            arr_block[i][j].mycell=NULL;
                        }
                }
                else
                {
                    forfor(n)
                            fread(&arr_block[i][j],sizeof(block),1,ptf);
                }
                fclose(ptf);

                if(game.load)
                {
                    ptf = fopen("save_cell.bin","rb");
                    cell temp;
                    cell * lastCell = NULL;
                    while(!feof(ptf))
                    {
                        fread(&temp,sizeof(cell),1,ptf);
                        if(lastCell != NULL)
                            if(lastCell->x == temp.x && lastCell->y == temp.y)
                            break;
                        cell * new_cell = add(temp.cell_energy,temp.x,temp.y);
                        strcpy(new_cell->name,temp.name);
                        new_cell->owner = temp.owner;
                        new_cell->cell_moved = temp.cell_moved;
                        arr_block[new_cell->x][new_cell->y].mycell = new_cell;
                        lastCell =  new_cell;
                        if(!new_cell->cell_moved)game.last_team = temp.owner;
                        if(temp.owner == 'Y')
                            game.single_player=false;
                    }
                }
                else
                {
                    printf("Please enter number of cells team 1: ");
                    scanf("%d",&s);
                    for(int k = 0;k<s;k++)
                    {
                        int i=rand()%n;
                        int j=rand()%n;
                        while(!isEmpty(i,j,arr_block)){
                            i=rand()%n;
                            j=rand()%n;
                        }
                        cell* new_cell = add(40,i,j);
                        new_cell->owner = 'X';
                        new_cell->cell_moved = false;
                        arr_block[i][j].mycell = new_cell;
                        game.last_team='X';
                    }
                    if(!game.single_player)
                    {
                        printf("Please enter number of cells team 2: ");
                        scanf("%d",&s);
                        for(int k = 0;k<s;k++)
                        {
                            int i=rand()%n;
                            int j=rand()%n;
                            while(!isEmpty(i,j,arr_block)){
                                i=rand()%n;
                                j=rand()%n;
                            }
                            cell* new_cell = add(40,i,j);
                            new_cell->owner = 'Y';
                            new_cell->cell_moved = true;
                            arr_block[i][j].mycell = new_cell;
                        }
                    }
                }

                while(1)
                {
                    game.last_team = check_turn(game.last_team,head);
                    print_map(n,arr_block);
                    print_cell(head , n,!game.single_player);
                    fflush(stdin);
                    printf("Player %c Choose your cell: ",game.last_team);
                    int a;
                    scanf("%d",&a);
                    cell* choosed_cell= NULL;
                    cell* current=head;
                    while(current != NULL)
                    {
                        if(current->num == a)break;
                        current = current->next;
                    }
                    choosed_cell=current;
                    if(current==NULL)
                    {
                        printf("Wrong input!\n");
                        continue;
                    }
                    if(choosed_cell!=NULL){
                        printf("------------------------\n");
                        printf("You choosed [%s]\n" , choosed_cell->name);
                        printf("------------------------\n");
                        game.last_team=choosed_cell->owner;
                    }
                    int q=show_menu2();
                    if(q==1){
                        int plus_x = 0,plus_y = 0;
                        switch(show_menu_moves())
                        {
                            case 1:
                                if(isEmpty(choosed_cell->x-1,choosed_cell->y,arr_block)){
                                    plus_x=-1;
                                }
                                break;
                            case 2:
                                if(isEmpty(choosed_cell->x+1,choosed_cell->y,arr_block)){
                                    plus_x=1;
                                }
                                break;
                            case 3:
                                if(isEmpty(choosed_cell->x-1,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 0){
                                    plus_x=-1;
                                    plus_y = 1;
                                }
                                else if(isEmpty(choosed_cell->x,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 1 )
                                {
                                    plus_y=1;
                                }
                                break;
                            case 4:
                                if(isEmpty(choosed_cell->x-1,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 0){
                                    plus_x=-1;
                                    plus_y = -1;
                                }
                                else if(isEmpty(choosed_cell->x,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 1 )
                                {
                                    plus_y=-1;
                                }
                                break;
                            case 5:
                                if(isEmpty(choosed_cell->x+1,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 1){
                                    plus_x=1;
                                    plus_y = 1;
                                }
                                else if(isEmpty(choosed_cell->x,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 0 )
                                {
                                    plus_y=1;
                                }
                                break;
                            case 6:
                                if(isEmpty(choosed_cell->x+1,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 1){
                                    plus_x=1;
                                    plus_y=-1;
                                }
                                else if(isEmpty(choosed_cell->x,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 0 )
                                {
                                    plus_y=-1;
                                }
                        }
                        if(plus_x != 0 || plus_y != 0)
                        {
                            choosed_cell->cell_moved=true;
                            int per_x = choosed_cell->x;
                            int per_y = choosed_cell->y;
                            choosed_cell->x=plus_x+per_x;
                            choosed_cell->y=plus_y+per_y;
                            arr_block[choosed_cell->x][choosed_cell->y].mycell = arr_block[per_x][per_y].mycell;
                            arr_block[per_x][per_y].mycell = NULL;

                        }
                    }
                    if(q==2){
                        int num = 0;
                        if(isEmpty(choosed_cell->x+1,choosed_cell->y,arr_block))num++;
                        if(isEmpty(choosed_cell->x-1,choosed_cell->y,arr_block))num++;
                        if(choosed_cell->y%2==0){
                            if(isEmpty(choosed_cell->x+1  ,choosed_cell->y+1,arr_block))num++;
                            if(isEmpty(choosed_cell->x+1  ,choosed_cell->y-1,arr_block))num++;

                            if(isEmpty(choosed_cell->x  ,choosed_cell->y+1,arr_block))num++;
                            if(isEmpty(choosed_cell->x  ,choosed_cell->y-1,arr_block))num++;
                        }
                        else {
                            if(isEmpty(choosed_cell->x  ,choosed_cell->y+1,arr_block))num++;
                            if(isEmpty(choosed_cell->x  ,choosed_cell->y-1,arr_block))num++;

                            if(isEmpty(choosed_cell->x-1  ,choosed_cell->y+1,arr_block))num++;
                            if(isEmpty(choosed_cell->x-1  ,choosed_cell->y-1,arr_block))num++;
                        }
                        if(num >= 1 && arr_block[choosed_cell->x][choosed_cell->y].type==2 && choosed_cell->cell_energy>=80 ){
                                int plus_x=0,plus_y=0;
                                for(int random_num = rand()%6+1;plus_x == 0 && plus_y == 0;random_num= rand()%6+1)
                                {
                                    if(random_num == 1)
                                    {
                                        if(isEmpty(choosed_cell->x-1,choosed_cell->y,arr_block)){
                                            plus_x=-1;
                                        }
                                    }
                                    else if(random_num == 2)
                                    {
                                        if(isEmpty(choosed_cell->x+1,choosed_cell->y,arr_block)){
                                            plus_x=1;
                                        }
                                    }
                                    else if(random_num == 3)
                                    {
                                        if(isEmpty(choosed_cell->x-1,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 0){
                                            plus_x=-1;
                                            plus_y = 1;
                                        }
                                        else if(isEmpty(choosed_cell->x,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 1 )
                                        {
                                            plus_y=1;
                                        }
                                    }
                                    else if(random_num == 4)
                                    {
                                        if(isEmpty(choosed_cell->x-1,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 0){
                                            plus_x=-1;
                                            plus_y = -1;
                                        }
                                        else if(isEmpty(choosed_cell->x,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 1 )
                                        {
                                            plus_y=-1;
                                        }
                                    }
                                    else if (random_num == 5)
                                    {
                                        if(isEmpty(choosed_cell->x+1,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 1){
                                            plus_x=1;
                                            plus_y = 1;
                                        }
                                        else if(isEmpty(choosed_cell->x,choosed_cell->y+1,arr_block) && choosed_cell->y%2 == 0 )
                                        {
                                            plus_y=1;
                                        }
                                    }
                                    else if (random_num == 6)
                                    {
                                        if(isEmpty(choosed_cell->x+1,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 1){
                                            plus_x=1;
                                            plus_y=-1;
                                        }
                                        else if(isEmpty(choosed_cell->x,choosed_cell->y-1,arr_block) && choosed_cell->y%2 == 0 )
                                        {
                                            plus_y=-1;
                                        }
                                    }
                                }
                                choosed_cell->cell_moved=true;
                                cell* new_cell = add(40,choosed_cell->x+plus_x,choosed_cell->y+plus_y);
                                new_cell->owner = choosed_cell->owner;
                                arr_block[choosed_cell->x+plus_x][choosed_cell->y+plus_y].mycell = new_cell;
                            new_cell = add(40,choosed_cell->x,choosed_cell->y);
                            new_cell->owner = choosed_cell->owner;
                            arr_block[choosed_cell->x][choosed_cell->y].mycell = new_cell;
                            remove_cell(choosed_cell);
                        }
                    }
                    if(q == 3)
                    {
                        if(arr_block[choosed_cell->x][choosed_cell->y].type==Energy && arr_block[choosed_cell->x][choosed_cell->y].block_energy>0 ){
                            choosed_cell->cell_moved=true;
                            if(arr_block[choosed_cell->x][choosed_cell->y].block_energy>=15){
                                choosed_cell->cell_energy+=15;
                                arr_block[choosed_cell->x][choosed_cell->y].block_energy-=15;
                                if (choosed_cell->cell_energy > 100)
                                    choosed_cell->cell_energy = 100;
                            }

                            else
                            {
                                choosed_cell->cell_energy+=arr_block[choosed_cell->x][choosed_cell->y].block_energy;
                                arr_block[choosed_cell->x][choosed_cell->y].block_energy=0;
                                if (choosed_cell->cell_energy > 100)
                                    choosed_cell->cell_energy = 100;
                            }

                        } else printf("Wrong input!\n");
                    }
                    if(q == 4)
                    {
                        FILE* f = fopen("save_map.bin" , "wb");
                        if(f==NULL){
                            printf("cannot create the file\n");
                            continue;
                        }
                        fwrite(&n,sizeof(int),1,f);
                        forfor(n){
                                fwrite(&arr_block[i][j],sizeof(block),1,f);
                            }
                        fclose(f);
                        f = fopen("save_cell.bin" , "wb");
                        if(f==NULL){
                            printf("cannot create the file\n");
                            continue;
                        }
                        for(cell*current=head;current!=NULL;current=current->next){
                            fwrite(current,sizeof(cell),1,f);
                        }
                        fclose(f);
                    }
                    if(q==5){
                        int sum1=0,sum2=0;
                        for(current=head;current!=NULL;current=current->next){
                            if(current->owner=='X')sum1+=current->cell_energy;
                            else sum2+=current->cell_energy;
                        }
                        printf("\x1b[34m____________________________\n");
                        if(menu_input==2)printf("Player %c your score is : %d\n",head->owner,sum1);
                        if(menu_input==3){
                            printf("Player %c your score is : %d\n",head->owner,sum1);
                            printf("Player Y your score is : %d\n",sum2);}
                        printf("____________________________\x1b[0m\n");
                        if(menu_input==3 && sum2>sum1)printf("!PLAYER (Y) HAS WON THE GAME!");
                        if(menu_input==3 && sum1>sum2)printf("!PLAYER (X) HAS WON THE GAME!");
                        if(menu_input==3 && sum1==sum2)printf("!NO WINNER!");
                        exit(0);
                    }


                }
        }
        break;

    }
}
bool isEmpty(int x,int y,block map[n][n]){
    if( x >= n || y >= n || x <0 || y < 0)return false;
    if(map[x][y].mycell!=NULL || map[x][y].type==3){
        return false;
    }
    else return true;



}
cell *add(int energy,int x,int y){
    cell* new_cell = (struct cell*) malloc(sizeof(cell));
    new_cell->cell_energy=energy;
    new_cell->next=NULL;
    new_cell->x=x;
    new_cell->y=y;
    strcpy(new_cell->name,rand_string(10));
    cell*current = head;
    if(current==NULL){
        head=new_cell;
        return new_cell;
    }
    for(current=head;current->next!=NULL;current=current->next);
    current->next=new_cell;
    return new_cell;
}

void remove_cell(cell*c){
    cell * current = head;
    if(head == c)
    {
        if(c->next != NULL)
            head = c->next;
        else
            head = NULL;
        free(c);
        return;
    }
    while(current->next != c)
        current = current->next;
    if(current->next->next != NULL)
        current->next = current->next->next;
    else
        current->next = NULL;
    free(c);
}