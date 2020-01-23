#include "functions.h"
#define forfor(X) for(int i=0;i<X;i++)for(int j=0;j<X;j++)
game_data game;
int n,s;
bool isEmpty(int x,int y,block map[n][n]);
int main() {
    srand(time(NULL));
    while(1){
        game.load=false;
        cell * head = NULL;
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
                        arr_block[i][j].x = n-1-i;
                        arr_block[i][j].y = j;
                        arr_block[i][j].e = 100;
                        arr_block[i][j].cell=NULL;
                    }
                    fclose(ptf);
                    scanf("%d",&s);
                    while(s--)
                    {
                        int i=rand()%n;
                        int j=rand()%n;
                        while(!isEmpty(i,j,arr_block)){
                            i=rand()%n;
                            j=rand()%n;
                        }
                        add(40,head,i,j);
                    }
                }
                break;

        }
    }
    return 0;
}
bool isEmpty(int x,int y,block map[n][n]){
    if(map[x][y].cell!=NULL || map[x][y].type==3 ){

        return false;
    }
    else return true;



}