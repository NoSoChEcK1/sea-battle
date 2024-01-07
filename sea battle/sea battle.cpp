#include<iostream>
#include<utility>
#include<vector>
#include<string>
#include<map>
#include<Windows.h>
#include<random>
#include<set>
#include<thread>
using namespace std;
struct ships {
	const int size = 13;
	vector<vector<char>>& matrixFiel;
	ships(vector<vector<char>>& matrixFiel) :matrixFiel(matrixFiel) {}
	bool nerby(vector<pair<int, int>>ship, pair<int, int>coordinate) {
		for (int i = 0; i < ship.size(); ++i) {
			if (coordinate.first == ship[i].first && coordinate.second == ship[i].second) {
				return false;
			}
			if (coordinate.first - 1 == ship[i].first && coordinate.second == ship[i].second || coordinate.first + 1 == ship[i].first && coordinate.second == ship[i].second ||
				coordinate.first == ship[i].first && coordinate.second - 1 == ship[i].second || coordinate.first == ship[i].first && coordinate.second + 1 == ship[i].second ||
				coordinate.first - 1 == ship[i].first && coordinate.second + 1 == ship[i].second || coordinate.first - 1 == ship[i].first && coordinate.second - 1 == ship[i].second ||
				coordinate.first + 1 == ship[i].first && coordinate.second - 1 == ship[i].second || coordinate.first + 1 == ship[i].first && coordinate.second + 1 == ship[i].second) {
				return false;
			}
		}
		return true;
	}
	void show() {
		system("cls");
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cout << matrixFiel[i][j] << " ";
			}
			cout << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(800));
	}
};
struct Shoot {
	set<pair<int, int>>shoot;
	Shoot(set<pair<int, int>>& shoot) :shoot(shoot) {}
	void push(int y, int x) {
		shoot.insert(make_pair(y, x));
	}
	bool checkIn(int y, int x) {
		return shoot.find(make_pair(y, x)) != shoot.end();
	}
};
bool proverka(pair<int, int>coordinate, pair<int, int>coordinateTo, int lOng) {
	if (coordinate.first == coordinateTo.first && coordinate.second == coordinateTo.second) {
		return false;
	}
	if (abs(coordinateTo.first - coordinate.first) < lOng && abs(coordinateTo.second - coordinate.second) < lOng) {
		return false;
	}
	if (coordinate.first <= 0 || coordinate.first > 10 || coordinate.second <= 0 || coordinate.second > 10 || coordinateTo.first <= 0 || coordinateTo.first > 10 || coordinateTo.second <= 0 || coordinateTo.second > 10) {
		return false;
	}
	return true;
}
void arround(int& ship, int& coordinateTo) {
	(ship < coordinateTo) ? ++ship : (ship > coordinateTo) ? --ship : ship = ship;
}
pair<int, int> toFin(int side, int To, int y, int x) {
	if (side == 1) {
		y -= To;
	}
	else if (side == 2) {
		x -= To;
	}
	else if (side == 3) {
		x += To;
	}
	else if (side == 4) {
		y += To;
	}
	if (x < 0 || x > 10 || y > 10 || y < 0) {
		return make_pair(0, 0);
	}
	else
		return make_pair(y, x);
}
int main()
{
	setlocale(LC_ALL, "rus");
	uniform_int_distribution<int>randN(1, 10);
	uniform_int_distribution<int>randS(1, 4);
	mt19937 gen(random_device{}());
	bool check = true;
	int choose, size = 13, counterY = 0, counterX = 0;
	int shipy = 0, shipx = 0;
	map<int, int>count = { { 1,0 }, { 2,0 }, { 3,0 }, { 4,0 } };
	pair<int, int>coordinate, coordinateTo;
	vector<pair<int, int>>ship;
	cout << "Для выбора: катера нажмите 1, для эсминца нажмите 2, для крейсера нажмите 3, для линкора нажмите 4" << endl;
	cout << "всего 4 катера, 3 эсминца, 2 крейсера, 1 линкор" << endl;
	vector<vector<char>>matrixField(size, vector<char>(size, ' '));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (j == 0 || j == 11) {
				matrixField[i][j] = '|';
			}
			if (i == 0 || i == 11) {
				matrixField[i][j] = '-';
			}
			if (i == 12) {
				if (counterY == 11) {
					matrixField[i][j] = '0';
				}
				else {
					matrixField[i][j] = to_string(counterY)[0];
					++counterY;
				}
			}
			if (j == 12) {
				if (i == 12 && j == 12) {
					matrixField[i][j] = ' ';
				}
				else {
					if (counterX == 11) {
						matrixField[i][j] = '0';
					}
					else {
						matrixField[i][j] = to_string(counterX)[0];
						++counterX;
					}
				}
			}
		}
	}
	ships s(matrixField);
	for (int i = 0; i < 10; ++i) {
		check = true;
		cin >> choose;
		switch (choose)
		{
		case 1:
			if (count[choose] == 4) {
				--i;
				break;
			}
			else {
				cin >> coordinate.first >> coordinate.second;
				if (coordinate.first < 0 || coordinate.first>10 || coordinate.second < 0 || coordinate.second>10) {
					--i;
					break;
				}
				if (s.nerby(ship, coordinate)) {
					ship.push_back(make_pair(coordinate.first, coordinate.second));
					matrixField[coordinate.first][coordinate.second] = '^';
					++count[choose];
				}
				else {
					--i;
				}
			}
			break;
		case 2:
			if (count[choose] == 3) {
				--i;
				break;
			}
			else {
				cin >> coordinate.first >> coordinate.second >> coordinateTo.first >> coordinateTo.second;
				if (!proverka(coordinate, coordinateTo, 1)) {
					--i;
					break;
				}
				if (!s.nerby(ship, coordinate)) {
					--i;
					break;
				}
				shipy = coordinate.first, shipx = coordinate.second;
				for (int j = 0; j < 2; ++j) {
					arround(coordinate.first, coordinateTo.first);
					arround(coordinate.second, coordinateTo.second);
					if (!s.nerby(ship, coordinate)) {
						check = false;
					}
					else {
						if (check)
							check = true;
					}
				}
				if (check) {
					for (int j = 0; j < 2; ++j) {
						ship.push_back(make_pair(shipy, shipx));
						matrixField[shipy][shipx] = '^';
						arround(shipy, coordinateTo.first);
						arround(shipx, coordinateTo.second);
						++count[choose];
					}
				}
				else {
					--i;
				}
			}
			break;
		case 3:
			if (count[choose] == 2) {
				--i;
				break;
			}
			else {
				cin >> coordinate.first >> coordinate.second >> coordinateTo.first >> coordinateTo.second;
				if (!proverka(coordinate, coordinateTo, 2)) {
					--i;
					break;
				}
				if (!s.nerby(ship, coordinate)) {
					--i;
					break;
				}
				shipy = coordinate.first, shipx = coordinate.second;
				for (int j = 0; j < 3; ++j) {
					arround(coordinate.first, coordinateTo.first);
					arround(coordinate.second, coordinateTo.second);
					if (!s.nerby(ship, coordinate)) {
						check = false;
					}
					else {
						if (check)
							check = true;
					}
				}
				if (check) {
					for (int v = 0; v < 3; ++v) {
						ship.push_back(make_pair(shipy, shipx));
						matrixField[shipy][shipx] = '^';
						arround(shipy, coordinateTo.first);
						arround(shipx, coordinateTo.second);
						++count[choose];
					}
				}
				else {
					--i;
				}
			}
			break;
		case 4:
			if (count[choose] == 1) {
				--i;
				break;
			}
			else {
				cin >> coordinate.first >> coordinate.second >> coordinateTo.first >> coordinateTo.second;
				if (!proverka(coordinate, coordinateTo, 3)) {
					--i;
					break;
				}
				if (!s.nerby(ship, coordinate)) {
					--i;
					break;
				}
				shipy = coordinate.first, shipx = coordinate.second;
				for (int v = 0; v < 4; ++v) {
					arround(coordinate.first, coordinateTo.first);
					arround(coordinate.second, coordinateTo.second);
					if (!s.nerby(ship, coordinate)) {
						check = false;
					}
					else {
						if (check)
							check = true;
					}
				}
				if (check) {
					for (int k = 0; k < 4; ++k) {
						ship.push_back(make_pair(shipy, shipx));
						matrixField[shipy][shipx] = '^';
						arround(shipy, coordinateTo.first);
						arround(shipx, coordinateTo.second);
						++count[choose];
					}
				}
				else {
					--i;
				}
			}
			break;
		}
		s.show();
	}
	vector<vector<char>>botMap(size, vector<char>(size, ' '));
	int BotY = 0, BotX = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (j == 0 || j == 11) {
				botMap[i][j] = '|';
			}
			if (i == 0 || i == 11) {
				botMap[i][j] = '-';
			}
			if (i == 12) {
				if (BotY == 11) {
					botMap[i][j] = '0';
				}
				else {
					botMap[i][j] = to_string(BotY)[0];
					++BotY;
				}
			}
			if (j == 12) {
				if (i == 12 && j == 12) {
					botMap[i][j] = ' ';
				}
				else {
					if (BotX == 11) {
						botMap[i][j] = '0';
					}
					else {
						botMap[i][j] = to_string(BotX)[0];
						++BotX;
					}
				}
			}
		}
	}
	ships E(botMap);
	int botsx, botsy;
	vector<vector<char>>ForPlayerMap = botMap;
	ships FP(ForPlayerMap);
	vector<pair<int, int >> coordinateBot;
	pair<int, int > XY;
	int side = 0;
	pair<int, int>To;
	for (int i = 0; i < 10; ++i) {
		botsx = 0, botsy = 0;
		check = true;
		To = make_pair(0, 0);
		side = 0;
		if (i == 1 || i == 2 || i == 3 || i == 0) {
			XY.first = randN(gen);
			XY.second = randN(gen);
			if (E.nerby(coordinateBot, XY)) {
				coordinateBot.push_back(XY);
				botMap[XY.first][XY.second] = '^';
			}
			else {
				--i;
			}
		}


		else if (i == 4 || i == 5 || i == 6) {
			XY.first = randN(gen);
			XY.second = randN(gen);
			botsy = XY.first, botsx = XY.second;
			side = randS(gen);
			To = toFin(side, 1, XY.first, XY.second);
			if (!proverka(coordinate, To, 1)) {
				check = false;
			}
			for (int q = 0; q < 2; ++q) {
				if (!E.nerby(coordinateBot, XY)) {
					check = false;
					q = 2;
				}
				else {
					arround(XY.first, To.first);
					arround(XY.second, To.second);
				}
			}
			if (check == true) {
				for (int q = 0; q < 2; ++q) {
					coordinateBot.push_back(make_pair(botsy, botsx));
					botMap[botsy][botsx] = '^';
					arround(botsy, To.first);
					arround(botsx, To.second);

				}
			}
			else {
				--i;
			}
		}
		else if (i == 7 || i == 8) {
			XY.first = randN(gen);
			XY.second = randN(gen);
			botsy = XY.first, botsx = XY.second;
			side = randS(gen);
			To = toFin(side, 2, XY.first, XY.second);
			if (!proverka(coordinate, To, 2)) {
				check = false;
			}
			for (int q = 0; q < 3; ++q) {
				if (!E.nerby(coordinateBot, XY)) {
					check = false;
					q = 3;
				}
				else {
					arround(XY.first, To.first);
					arround(XY.second, To.second);
				}
			}
			if (check == true) {
				for (int q = 0; q < 3; ++q) {
					coordinateBot.push_back(make_pair(botsy, botsx));
					botMap[botsy][botsx] = '^';
					arround(botsy, To.first);
					arround(botsx, To.second);
				}
			}
			else {
				--i;
			}
		}
		else if (i == 9) {
			XY.first = randN(gen);
			XY.second = randN(gen);
			botsy = XY.first, botsx = XY.second;
			side = randS(gen);
			To = toFin(side, 3, XY.first, XY.second);
			if (!proverka(make_pair(botsy, botsx), To, 3)) {
				check = false;
			}
			for (int q = 0; q < 4; ++q) {
				if (!E.nerby(coordinateBot, XY)) {
					check = false;
					q = 4;
				}
				else {
					arround(XY.first, To.first);
					arround(XY.second, To.second);
				}
			}
			if (check == true) {
				for (int q = 0; q < 4; ++q) {
					coordinateBot.push_back(make_pair(botsy, botsx));
					botMap[botsy][botsx] = '^';
					arround(botsy, To.first);
					arround(botsx, To.second);
				}
			}
			else {
				--i;
			}
		}
	}
	set<pair<int, int>>shoot;
	set<pair<int, int>>botsot;
	Shoot Sme(shoot);
	Shoot Sbot(botsot);
	int counterkill = 0, botkils = 0;
	check = true;
	XY = make_pair(0, 0);
	while (check) {
		FP.show();
		cin >> coordinate.first >> coordinate.second;
		while (coordinate.first <= 0 || coordinate.first > 10 || coordinate.second <= 0 || coordinate.second > 10) {
			cin >> coordinate.first >> coordinate.second;
		}
		while (Sme.checkIn(coordinate.first, coordinate.second)) {
			cin >> coordinate.first >> coordinate.second;
		}
		Sme.push(coordinate.first, coordinate.second);
		while (botMap[coordinate.first][coordinate.second] == '^') {
			FP.matrixFiel[coordinate.first][coordinate.second] = 'X';
			++counterkill;
			FP.show();
			cin >> coordinate.first >> coordinate.second;
		}
		FP.matrixFiel[coordinate.first][coordinate.second] = '#';

		if (counterkill >= 20) {
			cout << "Ты выиграл!!!" << endl;
			check = false;
		}
		FP.show();
		XY.first = randN(gen);
		XY.second = randN(gen);

		while (Sbot.checkIn(XY.first, XY.second)) {
			XY.first = randN(gen);
			XY.second = randN(gen);
		}
		Sbot.push(XY.first, XY.second);
		while (s.matrixFiel[XY.first][XY.second] == '^') {
			s.matrixFiel[XY.first][XY.second] = 'X';
			s.show();
			++botkils;
			XY.first = randN(gen);
			XY.second = randN(gen);
		}
		s.matrixFiel[XY.first][XY.second] = '#';
		if (botkils >= 20) {
			cout << "Ты проиграл..." << endl;
			check = false;
		}
		s.show();
	}
}