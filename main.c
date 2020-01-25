#include "functions.h"
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
        printf("             %c       " ,map[i][j].mycell!=NULL?map[i][j].mycell->owner:' ');
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
                        cell* new_cell = add(80,i,j);
                        new_cell->owner = 'X';
                        arr_block[i][j].mycell = new_cell;
                    }
					
					while(1)
					{
						print_map(n,arr_block);
						print_cell(head , n);
						fflush(stdin);
						printf("Choose your cell: ( , )\b\b\b\b");
						int a,b;
						char input;
						first:
						input = getch();
						a = input-'0';
						printf("%d," , a);
						input = getch();
						b = input-'0';
						printf("%d)\n" , b);
						b = n-1-b;
						cell*choosed_cell = arr_block[b][a].mycell;
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
								int per_x = choosed_cell->x;
								int per_y = choosed_cell->y;
								choosed_cell->x=plus_x+per_x;
								choosed_cell->y=plus_y+per_y;
								arr_block[choosed_cell->x][choosed_cell->y].mycell = arr_block[b][a].mycell;
								arr_block[b][a].mycell = NULL;
								
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
							if(num >= 2 && arr_block[choosed_cell->x][choosed_cell->y].type==2 && choosed_cell->cell_energy>=80 ){
								int randome_num;
								for(int i = 0;i < 2;i++)
								{
									int plus_x=0,plus_y=0;
									for(int random_num = rand()%6+1;plus_x == 0 && plus_y == 0;random_num= rand()%6+1)
									{
//										printf("%d\n" , random_num);getchar();
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
									cell* new_cell = add(40,choosed_cell->x+plus_x,choosed_cell->y+plus_y);
									new_cell->owner = choosed_cell->owner;
									arr_block[choosed_cell->x+plus_x][choosed_cell->y+plus_y].mycell = new_cell;
									
								}
								arr_block[choosed_cell->x][choosed_cell->y].mycell = NULL;
								remove_cell(choosed_cell);
							}
						}
						if(q == 3)
						{
						  if(arr_block[choosed_cell->x][choosed_cell->y].type==Energy && arr_block[choosed_cell->x][choosed_cell->y].block_energy>0 ){
								if(arr_block[choosed_cell->x][choosed_cell->y].block_energy>=15){
									choosed_cell->cell_energy+=15;
									arr_block[choosed_cell->x][choosed_cell->y].block_energy-=15;
								}
								else 
								{
									choosed_cell->cell_energy+=arr_block[choosed_cell->x][choosed_cell->y].block_energy;
									arr_block[choosed_cell->x][choosed_cell->y].block_energy=0;
								}
						  }	
						}
					}
                }
                break;

        }
    }
    return 0;
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
