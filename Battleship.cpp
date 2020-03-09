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
		pole_comp[X][Y] = 2;//���� ���������, ������ �� ��� ������������ ��������
		check = 1;
		strike(pole_comp, count, check);
	}
	else {
		pole_comp[X][Y] = 3; //������ ������
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
		pole_me[x][y] = 3; //�������� �� ���� ��� ������
		check_comp = 0;    //������� ����
		return count;
	}
	else if (pole_me[x][y] == 1) {
		cout << "Computer is got your ship!\n";
		count--;
		cout << "count comp is " << count << endl;
		pole_me[x][y] = 2; // ����������� ����
		mode = 1;
		strike_comp(pole_me, count, check_comp, mode, x, y);
	}
	else {
		strike_comp(pole_me, count, check_comp, mode, x, y);//����� ������� �������� ��������
	}
}



int main()
{
	srand(time(0));
	int ship = 4;
	int number = 1;
	int p = rand() % 2; //���������� ��� ������� �����������: �� ��������� ��� �����������
	int h = rand() % 5; //���������� ��� ������ ����������� ������������
	int v = rand() % 4;  //���� ��� ������, ����� �� ������ � ������ � ���� �� ����� ���������� �� ���������
	const int size = 10;
	int k = 1;
	int pole_for_comp[size][size] = { 0 };
	int pole_for_me[size][size] = { 0 };

	char mass[11][11]; //������ ��� ����������� �� ������
	mass[0][0] = 0;
	mass[0][10] = 48;
	mass[10][0] = 48;

	for (int j = 1; j < 10; j++) {
		mass[0][j] = 48 + j;
		mass[j][0] = 48 + j;
	}

	ship_rand(pole_for_comp, size, p, h, v, ship, number);//����������� �������� �����

	p = rand() % 2; // ��� ��� ������, ����� ���� ������ ���� � ������ � � ����������
	h = rand() % 5; //� ������ ���������
	v = rand() % 2;

	ship_rand(pole_for_me, size, p, h, v, ship, number); //����������� �������� ������

	cout << "This is Battlefield!" << endl;
	cout << "Use numbers from 1 to 10 to enter coordinate" << endl;
	cout << "X is horizontal coordinate Y is vertical coordinate" << endl;
	cout << "Press Enter to start the game!" << endl;
	cin.get();

	battlefield(pole_for_me, pole_for_comp, mass, size);//������� ������� ����������� ���� �� �����

	int count_me = 5;    //��� �����, � ������ ������ ���� ��� ����� 20
	int count_comp = 5;  //������ ������ ���������� �����
	int check_comp = 1;
	int check_me = 1;// ���������� ��� ��������� ������ ���������
	int x = 0;
	int y = 0;
	//���� ����. ������������� ����� ����������, ���� �������� ��������� �������. 
	//��� ������ ��� ������� ������ �� ������� ���������, ���� �������������.

	int mode = 0;// ��� �������� ��������� ����������
	int dir = 0;
	while ((count_me || count_comp) != 0) {
		check_me = 1;
		while (check_me) {
			count_comp = strike(pole_for_comp, count_comp, check_me);	//���� ������
			battlefield(pole_for_me, pole_for_comp, mass, size); // ���������� ����
		}
		if (count_comp == 0) {
			cout << "You win!";
			break;
		}
		check_comp = 1;
		while (check_comp) {
			count_me = strike_comp(pole_for_me, count_me, check_comp, mode, x, y);//���� ����������
			battlefield(pole_for_me, pole_for_comp, mass, size); // ���������� ����
		}
		if (count_me == 0) {
			cout << "You loose!" << endl;
			break;
		}
	}



	//������ ���� ����
	/*
	count_comp = strike(pole_for_comp, count_comp);	//���� ������
	if (count_comp == 0)
		break;
	else
		count_me = strike_comp(pole_for_me, count_me, hits, check, x, y);//���� ����������
	cout << endl;
	if (count_me == false)//����� �� ������� ��� ��� ���� ����� ������ ��������
		break;
	else
		battlefield(pole_for_me, pole_for_comp, mass, size); // ���������� ����

		*/
	// �������� ����� ������ �������
	/*if (pole_me[x][y] == 2)
		strike_comp(pole_me, count, hits, check, x, y);
	if (pole_me[x][y] == 3)
		strike_comp(pole_me, count, hits, check, x, y);
	if (pole_me[x][y] == 1) { //���� �������, ������� ��� 1
		cout << " Comp got your ship!";
		count = count - 1;
		pole_me[x][y] = 2;//��������� ��������
		
		check = 1;
		strike_comp(pole_me, count, hits, check, x, y);
	}
	else {  //��� �c������� ������ ��� 0, 0 ��� ����������� ������ ����
		pole_me[x][y] = 3;//������ ��������
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
