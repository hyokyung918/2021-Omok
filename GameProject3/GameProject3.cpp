#include <iostream>
#include <iomanip>
using namespace std;

const int unitSide = 19;
void printHead();
void printBox(int[][unitSide]);
void startGame(int[][unitSide], int*, int*, int);
int ifWin(int[][unitSide]);
bool wantContinue(int);

int main() {
	bool ifContinue = 1;
	do {
		int stonePlace[unitSide][unitSide] = { {0, }, };
		int stoneX, stoneY, count = 0;
		do {
			system("cls");
			printHead();
			printBox(stonePlace);
			int win = ifWin(stonePlace);
			if (win != 0) {
				ifContinue = wantContinue(win);
				break;
			}
			startGame(stonePlace, &stoneX, &stoneY, count);
			count++;
		} while (stoneX != 99 && stoneY != 99);
	} while (ifContinue == 1);
	return 0;
}

void printHead() {
	cout << "\t====== Let's Play Omok ======" << "\n\n";
}

void printBox(int stonePlace[][unitSide]) {
	string boxArr[3][3] = { {"┌-", "┬-", "┐"}, {"├-", "┼-", "┤"}, {"└-", "┴-", "┘"} };
	cout << "  ";
	for (int i = 1; i <= unitSide; i++)
		cout << setw(2) << i;
	cout << endl;
	for (int i = 1; i <= unitSide; i++) {
		cout << setw(2) << i;
		int boxArrayNum = 0;
		if (i > 1 && i < unitSide)
			boxArrayNum = 1;
		else if (i == unitSide)
			boxArrayNum = 2;
		for (int j = 1; j <= unitSide; j++) {
			if (stonePlace[j - 1][i - 1] == 0) {
				if (j == 1)
					cout << boxArr[boxArrayNum][0];
				else if (j == unitSide)
					cout << boxArr[boxArrayNum][2];
				else
					cout << boxArr[boxArrayNum][1];
			}
			else if (stonePlace[j - 1][i - 1] == 1)
				cout << "●";
			else
				cout << "○";
		}
		cout << endl;
	}
}

void startGame(int stonePlace[][unitSide], int* stoneX, int* stoneY, int count) {
	while (1) {
		int ifBlack = count % 2 == 0 ? 1 : 2;
		string stone = ifBlack == 1 ? "●" : "○";
		cout << endl << stone << "'s X,Y: ";
		cin >> *stoneX >> *stoneY;
		if (stonePlace[*stoneX-1][*stoneY-1] != 0 || *stoneX > unitSide || *stoneY > unitSide) {
			if (*stoneX == 99 && *stoneY == 99) break;
			else
				cout << "Can not put there. Try again.";
		}
		else {
			stonePlace[*stoneX-1][*stoneY-1] = ifBlack;
			break;
		}
	}
}

int ifWin(int stonePlace[][unitSide]) {
	for (int hor = 0; hor < unitSide; hor++) {
		for (int ver = 0; ver < unitSide; ver++) {
			for (int k = 1; k <= 2; k++) {
				if (stonePlace[hor][ver] == k) {
					int count1, count2, count3, count4;
					count1 = count2 = count3 = count4 = 1;
					for (int i = 1; i <= 5; i++) {
						if (stonePlace[hor + i][ver] == k) count1++; // 오른쪽으로
						if (stonePlace[hor + i][ver + i] == k) count2++; // 오른쪽 아래로
						if (stonePlace[hor][ver + i] == k) count3++; // 아래로
						if (stonePlace[hor - i][ver + i] == k) count4++; // 왼쪽 아래로
					}
					if (count1 == 5 || count2 == 5 || count3 == 5 || count4 == 5) return k;
				}
			}
		}
	}
	return 0;
}

bool wantContinue(int win) {
	char cont;
	string winner = win == 1 ? "●" : "○";
	cout << endl << winner << " win." << endl;
	cout << "Play again? (y/n): ";
	cin >> cont;
	if (cont == 'y' || cont == 'Y') return 1;
	return 0;
}