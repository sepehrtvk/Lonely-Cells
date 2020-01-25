#include "functions.h"
#define forfor(X) for(int i=0;i<X;i++)for(int j=0;j<X;j++)
game_data game;
int n,s;
bool isEmpty(int x,int y,block map[n][n]);
cell *add(int energy,int x,int y);
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
        printf("     %c              " ,map[i][j].mycell!=NULL?map[i][j].mycell->owner:' ');
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
        printf("               %c     " ,map[i][j].mycell!=NULL?map[i][j].mycell->owner:' ');
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
	printf("\n");

}

cell * head = NULL;
int main() {
    srand(time(NULL));
    while(1){
        game.load=false;
        
        game.single_player=true;
        int menu_input = show_menu();
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
                if(!game.load){
                	head = NULL;
                    char str[100];
                    scanf("%s",str);
                    ptf =fopen(str,"rb");
                    fread(&n, sizeof(n),1,ptf);
                }
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
                    fclose(ptf);
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
                        arr_block[i][j].mycell = new_cell;
                    }
					
					while(1)
					{
						print_map(n,arr_block);
						print_cell(head);
						fflush(stdin);
						getchar();
						printf("Choose your cell: ( , )\b\b\b\b");
						int a,b;
						char n;
						n = getch();
						a = n-'0';
						printf("%d," , a);
						n = getch();
						b = n-'0';
						printf("%d)\n" , b);
						
					}
                }
                break;

        }
    }
    return 0;
}
bool isEmpty(int x,int y,block map[n][n]){
    if(map[x][y].mycell!=NULL || map[x][y].type==3 ){
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
