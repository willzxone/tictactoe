#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
char newplace;
char matrix [3][3] = {  {'1','2','3'} ,
						{'4','5','6'}, 
						{'7','8','9'} };
int flag = 0;

///////////////////////////////////////////FOR GETTING POSITION OF INPUT//////////////////////////////////////////////////////

void gettingPos(int input) {
	int rows = 0, cols = 0;

	if( input % 3 == 0) {

		rows = (input / 3) - 1;
		cols = 2;
	}
	else {
		rows = input / 3;
		cols = (input % 3) - 1;

	}

	matrix[rows][cols] = newplace;
}

///////////////////////////////////////////FOR DISPLAY BOARD//////////////////////////////////////////////////////


void display() {
	
	cout << "     |     |     " << endl;
	cout << "  " << matrix[0][0] << "  |  " << matrix[0][1] << "  |  " << matrix[0][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << matrix[1][0] << "  |  " << matrix[1][1] << "  |  " << matrix[1][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << matrix[2][0] << "  |  " << matrix[2][1] << "  |  " << matrix[2][2] << endl;

	cout << "     |     |     " << endl << endl;

}


///////////////////////////////////////////FOR CHECKING INPUTS//////////////////////////////////////////////////////

bool check(int input, char arr[],int count) {

	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j <= count; j++) {
			if (arr[i] == arr[j]) {
				cout << "\nThis place is already taken by another player." << endl;
				return true;
			}
		}
	}
	return false;
}


///////////////////////////////////////////WINNING CONDITION//////////////////////////////////////////////////////



bool winningCondition(char matrix[][3]) {
	
	for (int i = 0; i < 3; i++) {
		if (matrix[i][0] == matrix[i][1]&& matrix[i][1] == matrix[i][2]) {
			return true;
		}
		if (matrix[0][i] == matrix[1][i]&& matrix[1][i] == matrix[2][i]) {
			return true;
		}
	}

	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) {
		return true;
	}
	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) {
		return true;
	}
	
}


///////////////////////////////////////////FOR GENERATING RANDOM NUMBERS//////////////////////////////////////////////////////



int randomNumber() {
	srand((unsigned)time(0));
	int randomNumber = (rand() % 9) + 1;
	return randomNumber;
}

///////////////////////////////////////////TOSS//////////////////////////////////////////////////////


bool boolToss(bool &player1,bool &player2) {
	
	int rand;
	rand = randomNumber();
	if (rand < 5) {
		player1 = true;
		return player1;
	}
	else {
		player2 = true;
		return player2;
	}
}

///////////////////////////////////////////FOR PLAYER TURN//////////////////////////////////////////////////////


bool playerTurn(bool &player1, bool &player2) {

	if (player1 == true) {
		player2 = false;
		return player2;
	}
	if (player2 == true) {
		player1 = false;
		return player1;
	}
}


///////////////////////////////////////////STORING SCORES//////////////////////////////////////////////////////


void scoreStore(string str) {
	fstream score;
	score.open("score.txt", ios::app);
	score << str << endl;
	score.close();
}

///////////////////////////////////////////FOR DISPLAY OF SCORES//////////////////////////////////////////////////////


void scoreFunc() {
	int p1Score=0,p2Score=0;
	fstream score;
	score.open("score.txt", ios::in);

	string playerScore,str;
	while (!score.eof()) {
		getline(score, playerScore);
		if (playerScore == "") {
			score.get();
			break;
		}
			if (playerScore[6] == '1') {
				p1Score++;
			}
			else if(playerScore[6] == '2') {
				p2Score++;
			}
	}
	score.close();
	system("cls");
	cout << "Player 1 total winning score: " << p1Score;
	cout << "\nPlayer 2 total winning score: " << p2Score;

}


///////////////////////////////////////////BIG OUTPUTS//////////////////////////////////////////////////////


void output(string outputFile) {
	fstream file;
	file.open(outputFile + ".txt", ios::in);
	string output;
	while (!file.eof()) {
		getline(file, output);
		for (int i = 0; i < 1; i++) {
			Sleep(150);
			cout << output << endl;
		}
	}
}


///////////////////////////////////////////SLEEPING//////////////////////////////////////////////////////


void sleep(float seconds) {
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	while (clock() < startClock + secondsAhead);
	return;
}




///////////////////////////////////////////MODE 1//////////////////////////////////////////////////////


int playerToPlayer() {
	system("cls");

	int input1 = 0, input2 = 0, size = 0,count=-1;
	char arr[9] = {0};
	bool vali = false, player1 = false, player2 = false,draw=false;
	fstream score;
	string str,outputFile="toss";

	output(outputFile);
	system("pause");
	boolToss(player1,player2);
	if (player1 == true) {
		cout << "\nPLAYER 1 WINS\n";
		system("pause>8");

	}
	else {
		cout << "\nPLAYER 2 WINS\n";
		system("pause>8");
	}
	system("cls");
	display();
	for (int i = 0; i < 5; i++) {
		playerTurn(player1,player2);
		size++;
		////////////////////////////////////////////PLAYER 1/////////////////////////////////////
		if (player1 == true) {

			do {
				count++;
				cout << "\nPlayer 1: ";
				newplace = 'X';
				cin >> input1;
				arr[count] = input1;
				flag=check(input1, arr, count);
				if (flag == true) {
					count--;
				}
			} while ((flag == true));

			gettingPos(input1);
			vali = winningCondition(matrix);
		////////////////////////////////////WINNING/////////////////////////////////////////////
			if (vali == true) {
				str = "Player1Wins";
				scoreStore(str);
				system("cls");
				display();
				cout << "\nPlayer 1 has won the game.";
				cout << endl;
				system("pause");
				return 0;
			}
			system("cls");
			display();
		}

		////////////////////////////////////PLAYER 2///////////////////////////////////////
		player1 = true;
		do {
			count++;
			cout << "\nPlayer 2: ";
			newplace = 'O';
			cin >> input2;
			arr[count] = input2;
			flag=check(input2, arr, count);
			if (flag == true) {
				count--;
			}
		} while ((flag == true));
		gettingPos(input2);
		winningCondition(matrix);
		vali = winningCondition(matrix);
		////////////////////////////////////WINNING/////////////////////////////////////////////
		if (vali == true) {
			system("cls");
			display();
			str = "Player2Wins";
			scoreStore(str);
			cout << "\nPlayer 2 has won the game.";
			cout << endl;
			system("pause");
			return 0;
		}
		system("cls");
		display();
		////////////////////////////////////DRAW//////////////////////////////////////////////
		if (i == 4) {
			cout << "\nNICE TRY, GAME TIED!";
			cout << endl;
			system("pause");
			return 0;
		}
	}
}


///////////////////////////////////////////MODE 2//////////////////////////////////////////////////////

int playerToMachine() {
	system("cls");

	int input1 = 0, input2 = 0, size = 0,count=-1,rand=0;
	char arr[9];
	bool vali = false, player1 = false, player2 = false, draw = false;
	fstream score;
	string str, outputFile = "toss";
	output(outputFile);
	system("pause");
	boolToss(player1, player2);
	if (player1 == true) {
		cout << "\nPLAYER 1 WINS\n";
		system("pause>8");
	}else if(player2== true) {
		cout << "\nCOMPUTER WINS\n";
		system("pause>8");
	}
	system("cls");
	display();
	for (int i = 0; i < 5; i++) {
		playerTurn(player1, player2);
		size++;
	
		////////////////////////////////////////////PLAYER 1/////////////////////////////////////
		if (player1 == true) {

			do {
				count++;
				cout << "\nPlayer 1: ";
				newplace = 'X';
				cin >> input1;
				arr[count] = input1;
				flag = check(input1, arr, count);
				if (flag == true) {
					count--;
				}
			} while ((flag == true));

			gettingPos(input1);
			vali = winningCondition(matrix);
		//////////////////////////////////////WINNING/////////////////////////////////////////////
			if (vali == true) {
				str = "Player1Wins";
				scoreStore(str);
				system("cls");
				display();
				cout << "\nPlayer 1 has won the game.";
				cout << endl;
				system("pause");
				return 0;
			}
			system("cls");
			display();
		}

		////////////////////////////////////PLAYER 2///////////////////////////////////////
		player1 = true;
		do {
			count++;
			cout << "\nComputer: ";
			newplace = 'O';
			Sleep(500);
			rand = randomNumber();
			input2 = rand;
			arr[count] = input2;
			flag = check(input2, arr, count);
			if (flag == true) {
				count--;
			}
		} while ((flag == true));
		gettingPos(input2);
		winningCondition(matrix);
		vali = winningCondition(matrix);
		//////////////////////////////////////WINNING/////////////////////////////////////////////
		if (vali == true) {
			system("cls");
			display();
			str = "Player2Wins";
			scoreStore(str);
			cout << "\nComputer has won the game.";
			cout << endl;
			system("pause");
			return 0;

		}
		system("cls");
		display();

		////////////////////////////////////DRAW//////////////////////////////////////////////
		if (i == 4) {
			cout << "\nNICE TRY, GAME TIED!";
			cout << endl;
			system("pause");
			return 0;
		}
	}
}

void credits();
void rules();

///////////////////////////////////////////MAIN MENU//////////////////////////////////////////////////////


void mainMenu() {
	string mainOut = "main";
	int mainMenu=0,playMode=0;
	bool back,loop=true;

	while(loop){
		system("cls");
		output(mainOut);
		cout << endl;
		cout << "\nMAIN MENU\n\n";

		cout << "\n1.Play Game";
		cout << "\n2.Credits";
		cout << "\n3.Instructions";
		cout << "\n4.Scores\n";
		cout << "\nCHOOSE FROM ABOVE MENU: ";

		do {
			cin >> mainMenu;
		} while (!(mainMenu > 0 && mainMenu < 5));
	
		switch (mainMenu) {
			case 1: {
				system("cls");
				cout << "1.Player vs Player";
				cout << "\n2.Player vs Computer\n";

				cout << "\nChoose a mode to play: ";
				do {
					cin >> playMode;
				} while (!(mainMenu > 0 && mainMenu < 3));
				if (playMode == 1) {
					playerToPlayer();
					continue;
				}
				else {
					playerToMachine();
					continue;
				}
				break;
			}
			case 2: {
				credits();
				cout << "Press 1 to go back: ";
				cout << "\nPress 0 to exit: ";
				cin >> back;
				if (back == 1) {
					continue;
				}
				else {
					loop = false;
					continue;
				}
				break;
			}
			case 3: {
				rules();
				cout << "\nPress 1 to go back: ";
				cout << "\nPress 0 to exit: ";
				cin >> back;
				if (back == 1) {
					continue;
				}
				else {
					loop = false;
					continue;
				}
				break;
			}
			case 4: {
				scoreFunc();
				cout << "\n\nPress 1 to go back: ";
				cout << "\nPress 0 to exit: ";
				cin >> back;
				if (back == 1) {
					continue;
				}
				else {
					loop = false;
					continue;
				}
				break;
			}
		}
	}
}


int main() {	
	mainMenu();
}

///////////////////////////////////////////CREDITS//////////////////////////////////////////////////////



void credits() {
	fstream credit;
	credit.open("credit.txt", ios::in);
	string output;
	system("cls");
	cout << endl;
	
	while (!credit.eof()) {
		getline(credit, output);
		for (int i = 0; i<1; i++) {
			Sleep(200);
			cout << output<<endl;
		}
	}
}


///////////////////////////////////////////RULES//////////////////////////////////////////////////////


void rules() {
	fstream rules;
	rules.open("rules.txt", ios::in);
	string output;
	system("cls");
	cout << endl;

	while (!rules.eof()) {
		getline(rules, output);
		for (int i = 0; i < 1; i++) {
			Sleep(200);
			cout << output << endl;
		}
	}
}