#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include<string.h>

char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
void menu();
int game();
void scoremenu();
int checkWin();
void drawBoard();

void addrecord(int pl);
void displayrecord();
void deletefile();
void search();

COORD coord= {0,0}; 

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//colors

void red () {
  printf("\033[1;31m");
}

void cyan () {
  printf("\033[1;36m");
}

void green() {
	printf("\033[1;32m");	
}

void reset () {
  printf("\033[0m");
}

//menu
void menu()
{
    int choice;
    system("cls");
    gotoxy(47,2);
	green();
	printf("TIC TAC TOE");
	reset();
	gotoxy(42,3);
    printf("--------MENU--------");
    gotoxy(42,4);
	printf("1 : Play ");
    gotoxy(42,5);
	printf("2 : Scorecard");
    gotoxy(42,6);
	printf("3 : Exit");
	gotoxy(42,8);
    printf("Enter your choice:>");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        system("cls");
        game();
        break;
    case 2:
        system("cls");
        scoremenu();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

void scoremenu()
{
    int choice2;
    system("cls");
    gotoxy(52,2);
	green();
	printf("TIC TAC TOE");
	reset();
	gotoxy(42,3);
    printf("--------SCORECARD MENU--------");
    gotoxy(42,4);
	printf("1 : View Scorecard");
    gotoxy(42,5);
	printf("2 : Search player");
	gotoxy(42,6);
	printf("3 : Reset scorecard");
    gotoxy(42,7);
	printf("4 : Back");
	gotoxy(42,9);
    printf("Enter your choice:>");
    scanf("%d",&choice2);
    switch (choice2)
    {
    case 1:
        system("cls");
        displayrecord();
        break;
    case 2:
        system("cls");
        search();
        break;
    case 3:
        system("cls");
        deletefile();
        break;
	case 4:
        menu();
        break;
    default:
        scoremenu();
    }
}
//game

int game(){
	int player = 1, i ,choice;
	char mark; // X,O
	do {
		drawBoard();
		player = (player % 2) ? 1 : 2;
		(player==1) ? red():cyan();
		mark = (player == 1) ? 'X' : 'O';
		printf("\n\nenter the choice :Player %d(%c)  ::",player,mark);
		scanf("%d",&choice);
		reset();
		
		if(choice == 1 && square[1] == '1')
			square[1] = mark;
		else if(choice == 2 && square[2] == '2')
			square[2] = mark;
		else if(choice == 3 && square[3] == '3')
			square[3] = mark;
		else if(choice == 4 && square[4] == '4')
			square[4] = mark;
		else if(choice == 5 && square[5] == '5')
			square[5] = mark;
		else if(choice == 6 && square[6] == '6')
			square[6] = mark;
		else if(choice == 7 && square[7] == '7')
			square[7] = mark;
		else if(choice == 8 && square[8] == '8')
			square[8] = mark;
		else if(choice == 9 && square[9] == '9')
			square[9] = mark;
			
		else {
			printf("Invalid option !");
			player--;
			getch();
			}
	
		i = checkWin();
			player++;	
		
	}while(i == -1);
	
	drawBoard();
	if(i==1){
		printf("==>Player %d won",--player);
		addrecord(player);
	}
	else {
		printf("==>Game draw");
	}
		getch();
		return 0;
}
int checkWin(){
	if(square[1] == square[2] && square[2] == square[3])
		return 1;
	else if (square[4] == square[5] && square[5] == square[6])
		return 1;
	else if(square[7] == square[8] && square[8] == square[9])
		return 1;
	else if(square[1] == square[4] && square[4] == square[7])
		return 1;
	else if(square[2] == square[5] && square[5] == square[8])
		return 1;
	else if(square[3] == square[6] && square[6] == square[9])
		return 1;
	else if(square[1] == square[5] && square[5] == square[9])
		return 1;
	else if(square[3] == square[5] && square[5] == square[7])
		return 1;
	else if(square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] !='4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else 
		return -1;	
}

void drawBoard(){
	system("cls");
	gotoxy(42,2);
	green();
	printf("Tic Tac Toe");
	gotoxy(35,5);
	red();
	printf("Player1 (X) - ");
	cyan();
	printf("Player2 (O) \n\n\n");
	reset();
	gotoxy(35,9);
	printf("        |        |        \n");
	gotoxy(35,10);
	printf("   %c    |    %c   |    %c   \n",square[1],square[2],square[3]);
	gotoxy(35,11);
	printf("________|________|________\n");
	gotoxy(35,12);
	printf("        |        |        \n");
	gotoxy(35,13);
	printf("   %c    |    %c   |    %c   \n",square[4],square[5],square[6]);
	gotoxy(35,14);
	printf("________|________|________\n");
	gotoxy(35,15);
	printf("        |        |        \n");
	gotoxy(35,16);
	printf("   %c    |    %c   |    %c   \n",square[7],square[8],square[9]);
	gotoxy(35,17);
	printf("        |        |        \n");	
}

//file handling
struct score
{
	char p1[80];
	char p2[80];
	char w[80];
};

void addrecord(int pl)
{	
	(pl==1)?red():cyan();
	FILE *fp;
	fp=fopen("scorecard.bin","ab");
	struct score s;
	printf("\n\nEnter names\n");
	printf("Player 1:\t");
	scanf("%s",s.p1);
	printf("Player 2:\t");
	scanf("%s",s.p2);
	(pl==1)?strcpy(s.w,s.p1):strcpy(s.w,s.p2);
	fwrite(&s,sizeof(s),1,fp);
	fclose(fp);
	reset();
	displayrecord();
}

void displayrecord()
{	
	system("cls");
	FILE *fp;
	fp=fopen("scorecard.bin","rb");
		if(fp==NULL)
{
	printf("scorecard not available");
}
else{

	struct score s[100];
	int i=0;
	gotoxy(0,0);
	red();
	printf("    Player 1");
	gotoxy(35,0);
	cyan();
	printf("Player 2");
	gotoxy(70,0);
	green();
	printf("Winner");
	reset();
	fseek(fp, 0, SEEK_SET);
	while(fread(&s[i],sizeof(s[i]),1,fp)==1){	
		gotoxy(0,i+1);
		printf("%d.  %s",i+1,s[i].p1);
		gotoxy(35,i+1);
		printf("%s",s[i].p2);
		gotoxy(70,i+1);
		green();
		printf("%s",s[i].w);
		i++;
		reset();
	}
}
	fclose(fp);		
}

void search()
{	
	system("cls");
	char search[80];
	FILE *fp;
	fp=fopen("scorecard.bin","rb");
	if(fp==NULL)
{
	printf("scorecard not available");
}
else{
	printf("Enter name to search\t");
	scanf("%s",search);
	int i=0;
	system("cls");
	gotoxy(0,0);
	red();
	printf("    Player 1");
	gotoxy(35,0);
	cyan();
	printf("Player 2");
	gotoxy(70,0);
	green();
	printf("Winner");
	reset();
	fseek(fp, 0, SEEK_SET);
	struct score s[100];
	int no_name=0;
	int w=0,l=0;
	int line=1;
	while(fread(&s[i],sizeof(s[i]),1,fp)==1) {
		if(strcmpi(s[i].p1,search)==0 || strcmpi(s[i].p2,search)==0) {
			gotoxy(0,line);
			printf("%d.  %s",line,s[i].p1);
			gotoxy(35,line);
			printf("%s",s[i].p2);
			gotoxy(70,line);
			printf("%s",s[i].w);
			line++;
			if(strcmpi(s[i].w,search)==0) {
				w++;
			}
			else {
				l++;
			}
		}
		else {
			no_name++;
		}
		i++;
	}
	if(no_name++==i) {
		system("cls");
		printf("No player found");
	}
	else {
		printf("\n\n\n Games won:::::%d",w);
		printf("\n Games lost::::%d",l);
	}
}
	fclose(fp);
}

void deletefile()
{
	if (remove("scorecard.bin") == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("File not deleted");
    }  
}

int main()
{
    system("cls");
    menu();
    getch();

}
