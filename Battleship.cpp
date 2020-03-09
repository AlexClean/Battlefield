// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;

void ship_rand(int pole[10][10], const int size, int p, int h, int v, int ship, int number) {
	if (ship == 0)
		return;

	for (int n = 0; n < number; n++) {
		if (h > size - ship) {
			v = v + 2;
			h = 0;
		}
		if (p) {
			for (int i = v; i < v + 1; i++) {
				for (int j = h; j < h + ship; j++) {

					pole[i][j] = 1;
				}
			}
		}
		else {
			for (int i = v; i < v + 1; i++) {
				for (int j = h; j < h + ship; j++) {

					pole[j][i] = 1;
				}
			}
		}
		h = h + ship + 1;

	}

	ship_rand(pole, size, p, h, v, ship - 1, number + 1);

}

void battlefield(int pole_me[10][10], int pole_comp[10][10], char mass[11][11], const int size) {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pole_me[i][j] == 2) {
				mass[i + 1][j + 1] = 88;
			}
			else if (pole_me[i][j] == 3) {
				mass[i + 1][j + 1] = 2;
			}
			else {
				mass[i + 1][j + 1] = 94;
			}
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << mass[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pole_comp[i][j] == 2) {
				mass[i + 1][j + 1] = 88;
			}
			else if (pole_comp[i][j] == 3) {
				mass[i + 1][j + 1] = 2;
			}
			else {
				mass[i + 1][j + 1] = 94;
			}
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << mass[i][j] << " ";
		}
		cout << endl;
	}
}

int strike(int pole_comp[10][10], int &count, int &check) {
	if (count == 0) {
		cout << "\n You win!" << endl;
		return count;
	}
	int X;
	cout << "\n Enter your coordinate X: ";
	cin >> X;
	int Y;
	cout << " Enter your coordinate Y: ";
	cin >> Y;
	X = X - 1;
	Y = Y - 1;
	if (pole_comp[X][Y] == 1) {
		cout << " Strike!" << endl;
		count--;
		cout << "count is " << count << endl;
		pole_comp[X][Y] = 2;//если попадание, мен€ем на уже отстрел€нное значение
		check = 1;
		strike(pole_comp, count, check);
	}
	else {
		pole_comp[X][Y] = 3; //ставим промах
		cout << " You miss";
		check = 0;
		return count;
	}
}

int strike_comp(int pole_me[10][10], int &count, int &check_comp, int mode, int x, int y) {
	if (count == 0) {
		cout << "\n Computer is win!" << endl;
		return count;
	}
	if (mode == 0) {
		x = rand() % 10;
		y = rand() % 10;
	}
	int dir = rand() % 3;
	if (dir == 0) {
		if (x > 0)
			x++;
		else
			x--;
	}

	else if (dir == 1) {
		if (x < 10)
			x--;
		else
			x++;
	}
		
	else if (dir == 2) {
		if (y < 10)
			y++;
		else
			y--;
	}
		
	else if (dir == 3) {
		if (y > 0)
			y--;
		else
			y++;
	}
	if (pole_me[x][y] == 0) {
		cout << "Computer miss!\n";
		pole_me[x][y] = 3; //помен€ли на мимо дл€ показа
		check_comp = 0;    //переход хода
		return count;
	}
	else if (pole_me[x][y] == 1) {
		cout << "Computer is got your ship!\n";
		count--;
		cout << "count comp is " << count << endl;
		pole_me[x][y] = 2; // отстрел€ное поле
		mode = 1;
		strike_comp(pole_me, count, check_comp, mode, x, y);
	}
	else {
		strike_comp(pole_me, count, check_comp, mode, x, y);//нужно сделать рекурсию выстрела
	}
}



int main()
{
	srand(time(0));
	int ship = 4;
	int number = 1;
	int p = rand() % 2; //переменна€ дл€ рандома расстановки: по вертикали или горизонтали
	int h = rand() % 5; //переменна€ дл€ начала расстановки горизонталей
	int v = rand() % 4;  //тоже дл€ начала, чтобы не всегда с одного и того же места начиналась по вертикали
	const int size = 10;
	int k = 1;
	int pole_for_comp[size][size] = { 0 };
	int pole_for_me[size][size] = { 0 };

	char mass[11][11]; //массив дл€ отображени€ на экране
	mass[0][0] = 0;
	mass[0][10] = 48;
	mass[10][0] = 48;

	for (int j = 1; j < 10; j++) {
		mass[0][j] = 48 + j;
		mass[j][0] = 48 + j;
	}

	ship_rand(pole_for_comp, size, p, h, v, ship, number);//расстановка кораблей компа

	p = rand() % 2; // ещЄ раз рандом, чтобы были разные пол€ у игрока и у компьютера
	h = rand() % 5; //и разное положение
	v = rand() % 2;

	ship_rand(pole_for_me, size, p, h, v, ship, number); //расстановка кораблей игрока

	cout << "This is Battlefield!" << endl;
	cout << "Use numbers from 1 to 10 to enter coordinate" << endl;
	cout << "X is horizontal coordinate Y is vertical coordinate" << endl;
	cout << "Press Enter to start the game!" << endl;
	cin.get();

	battlefield(pole_for_me, pole_for_comp, mass, size);//функци€ выводит заполненное поле на экран

	int count_me = 5;    //дл€ теста, в полной версии игры она равна 20
	int count_comp = 5;  //тоесть общему количеству палуб
	int check_comp = 1;
	int check_me = 1;// переменна€ дл€ включени€ режима добивани€
	int x = 0;
	int y = 0;
	//сама игра. ќсуществление ходов происходит, пока остаютс€ свободные корабли. 
	// ак только все корабли одного из игроков потоплены, цикл заканчиваетс€.

	int mode = 0;// дл€ хранени€ попаданий компьютера
	int dir = 0;
	while ((count_me || count_comp) != 0) {
		check_me = 1;
		while (check_me) {
			count_comp = strike(pole_for_comp, count_comp, check_me);	//ходы игрока
			battlefield(pole_for_me, pole_for_comp, mass, size); // обновление пол€
		}
		if (count_comp == 0) {
			cout << "You win!";
			break;
		}
		check_comp = 1;
		while (check_comp) {
			count_me = strike_comp(pole_for_me, count_me, check_comp, mode, x, y);//ходы компьютера
			battlefield(pole_for_me, pole_for_comp, mass, size); // обновление пол€
		}
		if (count_me == 0) {
			cout << "You loose!" << endl;
			break;
		}
	}



	//старый цикл игры
	/*
	count_comp = strike(pole_for_comp, count_comp);	//ходы игрока
	if (count_comp == 0)
		break;
	else
		count_me = strike_comp(pole_for_me, count_me, hits, check, x, y);//ходы компьютера
	cout << endl;
	if (count_me == false)//чтобы не рисовал ещЄ раз поле после своего выиграша
		break;
	else
		battlefield(pole_for_me, pole_for_comp, mass, size); // обновление пол€

		*/
	// выстрелы компа стара€ функци€
	/*if (pole_me[x][y] == 2)
		strike_comp(pole_me, count, hits, check, x, y);
	if (pole_me[x][y] == 3)
		strike_comp(pole_me, count, hits, check, x, y);
	if (pole_me[x][y] == 1) { //если корабль, корабль это 1
		cout << " Comp got your ship!";
		count = count - 1;
		pole_me[x][y] = 2;//попадани€ отмечает
		
		check = 1;
		strike_comp(pole_me, count, hits, check, x, y);
	}
	else {  //все оcтальные случаи это 0, 0 это изначальное пустое поле
		pole_me[x][y] = 3;//промах отмечает
		cout << " He miss! LOL";
		
		return count;
	}*/



}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
