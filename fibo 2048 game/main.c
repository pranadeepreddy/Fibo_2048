// fib_2048_game.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define max 31

struct userdetails{
	char *name;
	int boardNumber;
	int moves;
	int status;
	char *date;
	int **board;
};


struct leaderboard{
	char *date;
	char *name;
	int board;
	int moves;
};


int fibanocii[max];

void title(){
	printf("\n\n\n\t\t*************FIBO 2048 GAME*************\n\n");
}




void clearScreen(){
	system("cls");
	title();
}

void gohome()
{
	printf("\n\n\n\n\n\n\t\tpress any key to go to home....");
    getch();
}

void printBoard(struct userdetails *user){
	clearScreen();
	printf("\n\tusername    :   %s\n", user->name);
	printf("\n\tmoves used  :  %d\n", user->moves);
	printf("\n\t\t ");
	int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = 0; j < user->boardNumber * 16 ; j++){
			printf("-");
		}
		printf("\n");
		for (j = 0; j < user->boardNumber; j++){
			printf("\t\t|");
			if (user->board[i][j] == fibanocii[2 * user->boardNumber*user->boardNumber - 2]){
				printf("  *%d", user->board[i][j]);
			}
			else if (user->board[i][j]!=0){
				printf("  %d", user->board[i][j]);
			}
			else{
				printf("   ");
			}
		}
		printf("\t\t |");
		printf("\n\t\t ");
	}
	for (i = 0; i < user->boardNumber * 16; i++){
		printf("-");
	}
	printf("\n\n\n");
	printf("\t\t   left -->a     right -->d     up -->w     down -->s\n\n");
	printf("\t\tpress x to exit......\n\n");
}

void deletestats(){
	FILE *fp=fopen("currentstate.txt", "w");
	if (fp!=NULL){
		fprintf(fp, "\n");
		fclose(fp);

	}
	else{
		printf("\nerror occured while storing the result.....");
	}
}

void displayStatus(struct userdetails *user){
	clearScreen();
	printBoard(user);
	if (user->status == 1){
		printf("\n\n\t\tHURRY!!!!  %s has won the game with %d moves\n", user->name, user->moves);
		struct leaderboard *lb = (struct leaderboard *)malloc(sizeof(struct leaderboard));
		lb->name = user->name;
		lb->date = user->date;
		lb->board = user->boardNumber;
		lb->moves = user->moves;
		FILE *fp=fopen("leaderboard.txt", "a");
		if (fp!=NULL){
			//fwrite(lb, sizeof(struct leaderboard), 1, fp);
			fprintf(fp, "%s,%s,%d,%d\n", user->date, user->name, user->boardNumber, user->moves);
			fclose(fp);

		}
		else{
			printf("\nerror occured while storing the result.....");
		}
	}
	else{
		printf("\n\n\t%s has lost the game spending %d moves\n", user->name, user->moves);
	}
	deletestats();
	gohome();
}








void welcomeNote(){
	clearScreen();
	gohome();
}

int firstMenu(){
	clearScreen();
	int choice=0;
	printf("\n\t1.play game\n");
	printf("\t2.leader board\n");
	printf("\t3.exit\n");
	printf("\n\tenter your choice  :  ");
	do{
		choice = getch() - 48;
	} while (choice != 1 && choice != 2 && choice!=3);
	clearScreen();
	return choice;
}


int compare(const void *s1, const void *s2)
{
	struct leaderboard *l1 = (struct leaderboard *)s1;
	struct leaderboard *l2 = (struct leaderboard *)s2;

	return l1->moves - l2->moves;
}


void sortLeaderBoard(struct leaderboard *l,int len){
	qsort(l, len, sizeof(struct leaderboard), compare);
}


void displayLeaderBoard(struct leaderboard *l, int len){
	printf("\n\t\t\t****leader board****\n\n");
	printf("----------------------------------------------------------------\n");
	printf("\tsno    date                name       board     moves\n");
	printf("----------------------------------------------------------------\n");
	int i;
	for (i = 0; i < 20 && i < len; i++){
		printf("\t%d    %10s   %15s      %d*%d      %d", i+1,l[i].date, l[i].name, l[i].board, l[i].board, l[i].moves);
		printf("\n");
	}
	printf("----------------------------------------------------------------\n");
}

void printLeaderBoard(){
	struct leaderboard lb[50];
	struct leaderboard l;
	FILE *fp;
	int len = 0;
	char s[50];
	fp = fopen("leaderboard.txt", "r");
	if (fp!=NULL){
		while (fgets(s,50,fp)){
			lb[len].name = (char *)calloc(30, sizeof(char));
			lb[len].date = (char *)calloc(30, sizeof(char));
			int j = 0;
			int i = 0;
			for (; s[i] != ','; i++,j++){
				lb[len].date[i] = s[i];
			}
			j = 0;
			for (i = i + 1; s[i] != ','; i++, j++){
				lb[len].name[j] = s[i];
			}
			for (i = i + 1; s[i] != ','; i++){
				lb[len].board = s[i] - 48;
			}
			lb[len].moves = 0;
			for (i = i + 1; s[i] != '\n'; i++){
				lb[len].moves = lb[len].moves*10 + s[i] - 48;
			}
			len++;
		}
		sortLeaderBoard(&lb, len);
		displayLeaderBoard(lb, len);
		fclose(fp);

	}
	else{
		printf("\nerror occured while loading the file.....");
	}
	gohome();
}




void findFibanocii(){
	fibanocii[0] = 1;
	fibanocii[1] = 1;
	int i;
	for (i = 2; i <= max; i++){
		fibanocii[i] = fibanocii[i - 1] + fibanocii[i - 2];
	}

}


int isValid(char move){
	if (move == 'a' || move == 'w' || move == 's' || move == 'd' || move=='x'){
		return 0;
	}
	else
		return 1;
}

int areAdjecent(int a, int b){
	if (a > b){
		int t = a;
		a = b;
		b = t;
	}
	int i;
	for (i = 0; i < max - 1; i++){
		if (fibanocii[i] == a && fibanocii[i + 1] == b)
			return 1;
	}
	return 0;
}




void adjustLeft(struct userdetails *user){
	int k;
	int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = 0; j < user->boardNumber - 1; j++){
			if (user->board[i][j] == 0){
				for (k = j + 1; k < user->boardNumber; k++){
					if (user->board[i][k] != 0){
						user->board[i][j] = user->board[i][k];
						user->board[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}

void moveLeft(struct userdetails *user){
	adjustLeft(user);
	int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = 0; j < user->boardNumber - 1; j++){
			if (user->board[i][j]!=0 && areAdjecent(user->board[i][j], user->board[i][j + 1])){
				user->board[i][j] += user->board[i][j + 1];
				user->board[i][j + 1] = 0;
			}
		}
	}
	adjustLeft(user);
}

void adjustRight(struct userdetails *user){
	int k,i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = user->boardNumber - 1; j >0; j--){
			if (user->board[i][j] == 0){
				for (k = j - 1; k >=0; k--){
					if (user->board[i][k] != 0){
						user->board[i][j] = user->board[i][k];
						user->board[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}

void moveRight(struct userdetails *user){
	adjustRight(user);
	int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = user->boardNumber-1; j >0; j--){
			if (user->board[i][j] != 0 && areAdjecent(user->board[i][j], user->board[i][j - 1])){
				user->board[i][j] += user->board[i][j - 1];
				user->board[i][j - 1] = 0;
			}
		}
	}
	adjustRight(user);
}

void adjustUp(struct userdetails *user){
	int k;
	int i,j;
	for (j = 0; j < user->boardNumber; j++){
		for (i = 0; i < user->boardNumber - 1; i++){
			if (user->board[i][j] == 0){
				for (k = i + 1; k < user->boardNumber; k++){
					if (user->board[k][j] != 0){
						user->board[i][j] = user->board[k][j];
						user->board[k][j] = 0;
						break;
					}
				}
			}
		}
	}
}

void moveUp(struct userdetails *user){
	adjustUp(user);
	int i,j;
	for (j = 0; j < user->boardNumber; j++){
		for (i = 0; i < user->boardNumber - 1; i++){
			if (user->board[i][j] != 0 && areAdjecent(user->board[i][j], user->board[i+1][j])){
				user->board[i][j] += user->board[i+1][j];
				user->board[i+1][j] = 0;
			}
		}
	}
	adjustUp(user);
}


void adjustDown(struct userdetails *user){
	int k;
	int i,j;
	for (j = 0; j < user->boardNumber; j++){
		for (i = user->boardNumber - 1; i >0; i--){
			if (user->board[i][j] == 0){
				for (k = i - 1; k >=0; k--){
					if (user->board[k][j] != 0){
						user->board[i][j] = user->board[k][j];
						user->board[k][j] = 0;
						break;
					}
				}
			}
		}
	}
}


void moveDown(struct userdetails *user){
	adjustDown(user);
	int i,j;
	for (j = 0; j < user->boardNumber; j++){
		for (i = user->boardNumber - 1; i >0; i--){
			if (user->board[i][j] != 0 && areAdjecent(user->board[i][j], user->board[i - 1][j])){
				user->board[i][j] += user->board[i - 1][j];
				user->board[i - 1][j] = 0;
			}
		}
	}
	adjustDown(user);
}


void addRandom(struct userdetails *user){
	int r;
	srand(time(NULL));
	do{
		r = rand() % (user->boardNumber*user->boardNumber);
	} while (!(user->board[r / user->boardNumber][r%user->boardNumber] == 0));
	user->board[r / user->boardNumber][r%user->boardNumber] = 1;
}

int isBlockCondition(struct userdetails *user){
    int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = 0; j < user->boardNumber; j++){
			if (user->board[i][j] == 0){
				return 0;
			}
		}
	}
	return 1;
}


int isWon(struct userdetails *user){
	int won = 2 * user->boardNumber*user->boardNumber;
	int i,j;
	for (i = 0; i < user->boardNumber; i++){
		for (j = 0; j < user->boardNumber; j++){
			if (user->board[i][j] == fibanocii[won-2]){
				return 1;
			}
		}
	}
	return 0;
}

void storecurrentstate(struct userdetails *user){
	FILE *fp = fopen("currentstate.txt", "w");
	int i,j;
	if (fp!=NULL){
		fprintf(fp, "%s,%s,%d,%d,%d",  user->date,user->name, user->boardNumber, user->moves,user->status);
		for (i = 0; i < user->boardNumber ; i++){
			for (j = 0; j < user->boardNumber ; j++){
				fprintf(fp, ",%d", user->board[i][j]);
			}
		}
		fprintf(fp,"\n");
		fclose(fp);

	}
	else{
		printf("\nerror occured while storing the result.....");
	}
}


void playGame(struct userdetails *user){
	char move;
	while (1){
		printBoard(user);
		printf("\n\tenter your move  :  ");
		do{
			move=tolower(_getch());
		} while (isValid(move));
		switch (move){
		case 'a':
			moveLeft(user);
			break;
		case 's':
			moveDown(user);
			break;
		case 'd':
			moveRight(user);
			break;
		case 'w':
			moveUp(user);
			break;
		case 'x':
			printf("\n\n\t\t  do you really want to quit (y/n)   :");
			char ch;
			do{
				ch = tolower(_getch());
			} while (ch != 'y' && ch != 'n');
			if (ch == 'y'){
				clearScreen();
				printf("\n\n\n\n\n\t\t******thank you*******\n\n\n\n\n\n\n");
				exit(1);
			}
		}

		if (move != 'x'){
			if (isBlockCondition(user)){
				user->status = 0;
				break;
			}
			user->moves++;
			if (isWon(user)){
				user->status = 1;
				break;
			}
			addRandom(user);
			storecurrentstate(user);
		}

	}
}










void initializeBoard(struct userdetails *user){
	user->board = (int **)malloc(sizeof(int)*(user->boardNumber));
	int i;
	for (i = 0; i < user->boardNumber; i++){
		user->board[i] = (int *)calloc(user->boardNumber, sizeof(int));
	}
	int r1, r2;
	srand(time(NULL));
	r1 = rand() % (user->boardNumber*user->boardNumber);
	r2 = rand() % (user->boardNumber*user->boardNumber);
	while (r1 == r2){
		r2 = rand() % (user->boardNumber*user->boardNumber);
	}
	user->board[r1 / user->boardNumber][r1 % user->boardNumber] = 1;
	user->board[r2 / user->boardNumber][r2 % user->boardNumber] = 1;
}


char *formDate(int d, int m, int y){
	char *date = (char *)malloc(sizeof(char) * 11);
	date[1] = (d % 10)+48;
	date[0] = (d / 10) + 48;
	date[2] = '-';
	date[4] = (m % 10) + 48;
	date[3] = (char)(m / 10) + 48;
	date[5] = '-';
	date[9] = (y % 10) + 48;
	date[8] = ((y / 10) % 10) + 48;
	date[7] = ((y / 100) % 10) + 48;
	date[6] = ((y / 1000) % 10) + 48;
	date[10] = '\0';
	return date;
}

struct userdetails *ispreviouspresent(struct userdetails *user){
	FILE *fp;
	char s[200];
	fp = fopen("currentstate.txt", "r");
	int i,j,k;
	if (fp!=NULL){
		fgets(s, 200, fp);
		if (s[0] != '\n'){
			user = (struct userdetails *)malloc(sizeof(struct userdetails));
			user->date = (char *)calloc(11, sizeof(char));
			user->name = (char *)calloc(30, sizeof(char));
			int i = 0;
			int j;
			for (i = 0,j=0; s[i] != ','; i++,j++){
				user->date[j] = s[i];
			}
			user->date[j] = '\0';
			for (i = i+1, j = 0; s[i] != ','; i++, j++){
				user->name[j] = s[i];
			}
			user->name[j] = '\0';
			user->boardNumber = s[++i]-48;
			user->moves = 0;
			for (i = i+2 ; s[i] != ','; i++){
				user->moves = user->moves*10+s[i]-48;
			}
			user->status = 0;
			for (i = i + 1; s[i] != ','; i++){
				user->status = user->status * 10 + s[i] - 48;
			}
			user->board = (int **)calloc(user->boardNumber,sizeof(int *));
			for (j=0; j < user->boardNumber; j++){
				user->board[j] = (int *)calloc(user->boardNumber, sizeof(int));
				for (k = 0; k < user->boardNumber; k++){
					for (i = i + 1; s[i] != ',' && s[i]!='\n'; i++){
						user->board[j][k] = user->board[j][k] * 10 + s[i] - 48;
					}
				}
			}
		}
		fclose(fp);

	}
	return user;
}

struct userdetails *takeUserDetails(struct userdetails *user){
	user=ispreviouspresent(user);
	if (user != NULL){
		printf("\n\n\t%s hadn't completed previous game...... ", user->name);
		printf("\n\n\twould you like to continue  (y/n)   :   ");
		char ch;
		do{
			ch = tolower(_getch());
		} while (ch != 'y' && ch != 'n');
		if (ch == 'y'){
			return user;
		}
	}
	user = (struct userdetails *)malloc(sizeof(struct userdetails));
	user->name = (char *)calloc(30,sizeof(char));
	printf("\n\n\n\tenter user name :   ");
	printf("%s",user->name);
	do{
		fflush(stdin);
		//user->name=gets(30);
		scanf("%s",user->name);
	} while (strlen(user->name)==0);
	printf("\n\n\n\ton which board you want to play  \n");
	printf("\n\n\t1.  2*2 board");
	printf("\n\t2.  4*4 board");
	printf("\n\n\tenter your choice  :  ");
	do{
		user->boardNumber = _getch()-48;
	} while (user->boardNumber != 1 && user->boardNumber != 2);
	user->boardNumber *= 2;
	user->moves = 0;
	user->status = 0;
	initializeBoard(user);
	time_t t = time(NULL);
	struct tm *tm = (struct tm *)malloc(sizeof(struct tm));
	tm=localtime(&t);
	user->date = formDate(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1990);
	return user;
}





int main()
{
	welcomeNote();
	findFibanocii();
	while (1){
		int choice = firstMenu();
		switch (choice){
		case 1:
			printf("\n");
			struct userdetails *user = NULL;
			user=takeUserDetails(user);
			playGame(user);
			displayStatus(user);
			break;
		case 2:
			printLeaderBoard();
			break;
		case 3:
			printf("\n\n\n\n\n\t\t******thank you*******\n\n\n\n\n\n\n");
			return 0;
		}
	}

}

