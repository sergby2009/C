// Cardgame.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <cstdio>
#include <locale>

#define COL_CARDS 52
#define COL_USERS 1
#define COL_GET_CARDS 5
#define CNAME 13
#define CTYPE 4


void shufleCard(int [][13], int);
bool getCardsToUser(int [][COL_CARDS][3], int, int, int* , int);
void printUsersCard(int [][COL_CARDS][3], int, const int [][13], const char* [], const char* []);
void printUserCard(const int [][COL_CARDS][3], int, const int[][13], const char* [], const char* []);
void findCardName(int, const char* [], const int [][13], const char* [], const char* []);

bool is_coupe(int [][3], int [][CNAME]);
void findCardCoor(int, int*, const int [][13]);
int findCardID(const int [][13], int, int);

int main()
{
	setlocale(LC_ALL, "russian");
	
	//int cardMap[4][13] = {0};
	int cardMap[4][13] = {	{1,13,26,25,38,39,6,7,8,9,10,11,12},
							{2,14,15,16,17,18,19,20,21,22,23,24,5},
							{3,27,28,29,30,31,32,33,34,35,36,37,4},
							{52,40,41,42,43,44,45,46,47,48,49,50,51}};
	int cardsUser[COL_USERS][COL_CARDS][3] = { 0 };
	char* cardName[13] = {"Туз","Двойка","Тройка","Четверка","Пятерка","Шестерка","Семерка","Восьмерка","Девятка","Десятка","Валет","Дама","Король"};
	char* cardType[4] =  {"Черви","Буби","Крести","Пики"};
	int currentCard = 1;

		
	/*Перетасовка карт*/
	//shufleCard(cardMap, COL_CARDS);
	
	/*Раздача карт*/
	if (!getCardsToUser(cardsUser, COL_USERS, COL_GET_CARDS, &currentCard, COL_CARDS)) 
		return 0;
	
	/*Вывод карт игроков*/
	printUsersCard(cardsUser, COL_USERS, cardMap, (const char**)cardName, (const char**)cardType);

	/*Проверка на пары*/
	for (int i = 0; i <= COL_USERS - 1; i++)
	{
		is_coupe(cardsUser[i], cardMap);
	}
	
	system("PAUSE");
	return 0;
}

/*Перетасовка карт*/
void shufleCard(int cards[][13],int count)
{
	int step, row, col;
	srand(time(NULL));

	for (step = 1; step <= count; step++) 
	{
		row = rand() % 4;
		col = rand() % 13;

		while (cards[row][col] != 0) 
		{
			row = rand() % 4;
			col = rand() % 13;
		}

		cards[row][col] = step;
	}
}

/*Раздача карт*/
bool getCardsToUser(int cardsUser[][COL_CARDS], int countUser, int countCards, int* currentCard, int maxCards)
{
	int cntUser, cntCards;
	/*Проверка на раздачу карт больше количества карт в колоде*/
	if ((countUser * countCards + (*currentCard-1)) > maxCards) return false;
	
	for (cntCards = 0; cntCards < countCards; cntCards++)
		for (cntUser = 0; cntUser < countUser; cntUser++)
		{
			cardsUser[cntUser][cntCards] = *currentCard;
			*currentCard += 1;
		}
	return true;
}

/*Печать карт игроков*/
void printUsersCard(int cardsUser[][COL_CARDS], int countUser, const int cardMap[][13], const char* cardName[], const char* cardType[])
{
	int cnt;
	
	for (cnt = 0; cnt < countUser; cnt++)
	{
		printUserCard(cardsUser, cnt, cardMap, cardName, cardType);
	}
	
}

/*Печать карт игрока*/
void printUserCard(const int cardsUser[][COL_CARDS], int cntUser, const int cardMap[][13], const char* cardName[], const char* cardType[])
{
	int cnt = 0; 
	char* arrCard[2] = {"",""};
	
	
	printf("****** Карты %d игрока ******\n",cntUser+1);
	while (cardsUser[cntUser][cnt] != 0) 
	{
		findCardName(cardsUser[cntUser][cnt], (const char**)arrCard,  cardMap, cardName, cardType);
		printf("[%d]\t", cardsUser[cntUser][cnt]);
		printf("%s - %s\n",arrCard[0], arrCard[1]);
		cnt++;
	}
	printf("******************************\n");
}

/*Поиск карты по id*/
void findCardName(int cardID, const char* arrCard[], const int cardMap [][13], const char* cardName[], const char* cardType[])
{
	int row, col;

	for (row = 0; row <= CTYPE - 1; row++)
		for (col = 0; col <= CNAME - 1; col++)
		{
			if (cardMap[row][col] == cardID)
			{
				 arrCard[0] = cardType[row];
				 arrCard[1] = cardName[col];
			}
		}
}

bool is_coupe(int arr[][3], int map[][CNAME])
{
	int cnt = 0;
	int arrCoord[2] = {0};
	int result[COL_CARDS][2] = { 0 };
	
	/*Формирование матрицы повторений*/
	while (arr[cnt] != 0)
	{
		findCardCoor(arr[cnt][0], arrCoord, map);
		for (int row = 0; row <= CTYPE-1 ; row++)
		{
			int item, i;
			if (row == arrCoord[0])	{continue;}
			item = findCardID(map, row, arrCoord[1]);
			i = 0;
			while (arr[i] != 0)
			{
				if (i == cnt){i++;	continue;}
				if (item == arr[i][0])
				{
					if (result[cnt][1] == 0) result[cnt][1]++;
					result[cnt][0] = arrCoord[1];
					result[cnt][1]++;
				}
					
				i++;
			}
		}
		cnt++;
	}
	printf("stop\n");
	return true;
}

int findCardID(const int map[][13], int row, int col)
{
	return map[row][col];
}


void findCardCoor(int cardID, int *arrCard, const int map[][13])
{
	int row, col;

	for (row = 0; row <= CTYPE - 1; row++)
		for (col = 0; col <= CNAME - 1; col++)
		{
			if (map[row][col] == cardID)
			{
				arrCard[0] = row;
				arrCard[1] = col;
			}
		}
}