// Cardgame.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <cstdio>
#include <locale>
#include <string.h>

#define COL_CARDS 52
#define COL_USERS 1
#define COL_GET_CARDS 5
#define CNAME 13
#define CTYPE 4
#define COL_CARD_INFO 4
#define COL_CARD_ARM 5


void shufleCard(int [][13], int);
bool getCardsToUser(int [][COL_CARDS][COL_CARD_INFO], int, int, int* , int, int[][13]);
void printUsersCard(int [][COL_CARDS][COL_CARD_INFO], int, const int [][13], const char* [], const char* []);
void printUserCard(int [][COL_CARDS][COL_CARD_INFO], int, const int[][13], const char* [], const char* []);
void userArm_analiz(int[][COL_CARD_INFO], int[2]);

bool getResult_Double(int tempArr[COL_CARDS][COL_CARD_INFO], int resultArr[]);

void findCardName(int, const char* [], const int [][13], const char* [], const char* []);
void findCardCoor(int, int*, const int [][13]);
int  findCardID(const int [][13], int, int);

int main()
{
	setlocale(LC_ALL, "russian");
		
	//int cardMap[4][13] =	{0};
	/*int cardMap[4][13] =	{{1,13,26,25,38,39,6,7,8,9,10,11,12},
							{2,14,15,16,17,18,19,20,21,22,23,24,5},
							{27,3,28,29,30,31,32,33,34,35,36,37,4},
							{52,40,41,42,43,44,45,46,47,48,49,50,51}};*/
	int cardMap[4][13]	=	{{1,2,3,4,5,39,6,7,8,9,10,11,12},
							{13,14,15,16,17,18,19,20,21,22,23,24,38},
							{27,26,28,29,30,31,32,33,34,35,36,37,25},
							{52,40,41,42,43,44,45,46,47,48,49,50,51}};
	int cardsUser[COL_USERS][COL_CARDS][COL_CARD_INFO] = { 0 };
	int cardsUserArm[COL_USERS][2] = {0};
	char* cardName[13] = {"Двойка","Тройка","Четверка","Пятерка","Шестерка","Семерка","Восьмерка","Девятка","Десятка","Валет","Дама","Король","Туз"};
	char* cardType[4] =  {"Черви","Буби","Крести","Пики"};
	int currentCard = 1;

	/*Перетасовка карт*/
	//shufleCard(cardMap, COL_CARDS);
	
	/*Раздача карт*/
	if (!getCardsToUser(cardsUser, COL_USERS, COL_GET_CARDS, &currentCard, COL_CARDS, cardMap)) 
		return 0;
	
	/*Вывод карт игроков*/
	printUsersCard(cardsUser, COL_USERS, cardMap, (const char**)cardName, (const char**)cardType);

	/*Проверка на пары*/
	for (int i = 0; i <= COL_USERS - 1; i++)
	{
		printf("Анализ карт игрока %d\n", i);
		userArm_analiz(cardsUser[i], cardsUserArm[i]);
	}
	
	system("PAUSE");
	return 0;
}

/*Перетасовка карт*/
void shufleCard(int cards[][13],int count)
{
	int step, row, col;
	srand((unsigned int)time(NULL));

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
bool getCardsToUser(int cardsUser[][COL_CARDS][COL_CARD_INFO], int countUser, int countCards, int* currentCard, int maxCards, int map[][13])
{
	int cntUser, cntCards;
	int arrCoord[2] = {0};
	/*Проверка на раздачу карт больше количества карт в колоде*/
	if ((countUser * countCards + (*currentCard-1)) > maxCards) return false;
	
	for (cntCards = 0; cntCards < countCards; cntCards++)
		for (cntUser = 0; cntUser < countUser; cntUser++)
		{
			findCardCoor(*currentCard, arrCoord, map);
			cardsUser[cntUser][cntCards][0] = *currentCard;
			cardsUser[cntUser][cntCards][1] = arrCoord[0];
			cardsUser[cntUser][cntCards][2] = arrCoord[1];
			*currentCard += 1;
		}
	return true;
}

/*Печать карт игроков*/
void printUsersCard(int cardsUser[][COL_CARDS][COL_CARD_INFO], int countUser, const int cardMap[][13], const char* cardName[], const char* cardType[])
{
	int cnt;
	
	for (cnt = 0; cnt < countUser; cnt++)
	{
		printUserCard(cardsUser, cnt, cardMap, cardName, cardType);
	}
	
}

/*Печать карт игрока*/
void printUserCard(int cardsUser[][COL_CARDS][COL_CARD_INFO], int cntUser, const int cardMap[][13], const char* cardName[], const char* cardType[])
{
	int cnt = 0; 
	//char* arrCard[2];
	
	printf("****** Карты %d игрока ******\n",cntUser+1);
	while (cardsUser[cntUser][cnt][0] != 0) 
	{
		//findCardName(cardsUser[cntUser][cnt], (const char**)arrCard,  cardMap, cardName, cardType);
		printf("[%d]\t", cardsUser[cntUser][cnt][0]);
		printf("%s - %s\n", cardType[(cardsUser[cntUser][cnt][1])], cardName[(cardsUser[cntUser][cnt][2])]);
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


bool getResult_Double(int tempArr[COL_CARDS][COL_CARD_INFO], int resultArr[])
{
	int currentCard = 0, counter = 0;
	int analizArray[COL_CARD_ARM][2] = { 0 };
	int point = 0, level = 0;

	/*Подготовка массива для анализа результата руки*/
	while (tempArr[currentCard][0] != 0)
	{
		counter = 0;
		while (tempArr[counter][0] != 0)
		{
			if (counter == currentCard)
			{
				counter++;
				continue;
			}
			if (tempArr[currentCard][2] == tempArr[counter][2])
			{
				if (tempArr[currentCard][3] == 0) tempArr[currentCard][3] = currentCard + 1;
				if (tempArr[counter][3] == 0) tempArr[counter][3] = currentCard + 1;
			}
			counter++;
		}
		currentCard++;
	}

	/*Определение результата руки*/
	
	currentCard = 0;
	while (tempArr[currentCard][0] != 0)
	{
		if (tempArr[currentCard][3] == 0)
		{
			currentCard++;
			continue;
		}
		analizArray[(tempArr[currentCard][3])][0] += 1;
		analizArray[(tempArr[currentCard][3])][1] += tempArr[currentCard][2];
		currentCard++;
	}
	for (int i = 0; i < COL_CARD_ARM; i++)
	{
		if (level == 0)
		{
			switch (analizArray[i][0])
			{
				case 2 :	level = 1;
							point = analizArray[i][1];
							break;
				case 3:		level = 3;
							point = analizArray[i][1];
							break;
				case 4:		level = 7;
							point = analizArray[i][1];
							break;
			}
		}
		else
		{
			switch (analizArray[i][0])
			{
				case 2:		
					switch (level)
					{
						case 1: level = 2;
								point += analizArray[i][1];
								break;
						case 3: level = 6;
								point += analizArray[i][1];
								break;
					}
					break;
				case 3:		
					if (level = 1)
					{
						level = 6;
						point += analizArray[i][1];
					}
					break;
			}
		}
	}
	resultArr[0] = level;
	resultArr[1] = point;
	return (level)?true:false;
}

bool getResult_CardIncrease(int tempArr[COL_CARDS][COL_CARD_INFO], int resultArr[])
{
	/*Сортировка массива по возрастанию*/
	int currentCard = 0, cnt = 0;
	int tmp[COL_CARD_INFO];
	
	while (tempArr[currentCard][0] != 0)
	{
		cnt = currentCard + 1;
		while (tempArr[cnt][0] != 0)
		{
			if (tempArr[currentCard][2] > tempArr[cnt][2])
			{
				tmp[0] = tempArr[currentCard][0];
				tmp[1] = tempArr[currentCard][1];
				tmp[2] = tempArr[currentCard][2];
				tmp[3] = tempArr[currentCard][3];

				tempArr[currentCard][0] = tempArr[cnt][0];
				tempArr[currentCard][1] = tempArr[cnt][1];
				tempArr[currentCard][2] = tempArr[cnt][2];
				tempArr[currentCard][3] = tempArr[cnt][3];

				tempArr[cnt][0] = tmp[0];
				tempArr[cnt][1] = tmp[1];
				tempArr[cnt][2] = tmp[2];
				tempArr[cnt][3] = tmp[3];
			}
			cnt++;
		}
		currentCard++;
	}
	/*Проверка руки на стрит*/
	bool flag = true;
	int point = tempArr[0][2];
	
	for (int i = 1; tempArr[i][0] != 0; i++)
	{
		point += tempArr[i][2];
		if (tempArr[i][2] -1 != tempArr[i - 1][2])
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		resultArr[0] = 4;
		resultArr[1] = point;
	}
	else
	{
		resultArr[0] = 0;
		resultArr[1] = 0;
	}

	return flag;
}

void userArm_analiz(int arr[COL_CARDS][COL_CARD_INFO], int arm[2])
{
	bool result = false, variant1, variant2, variant3, variant4;
	int tempArr[COL_CARDS][COL_CARD_INFO];
	int resultVariant[4][2];
	
	memcpy(tempArr, arr, sizeof(tempArr));
	
	variant1 = getResult_Double(tempArr, resultVariant[0]);
	printf("Тип руки:%d\tКол-во очков:%d\n", resultVariant[0][0], resultVariant[0][1]);

	variant2 = getResult_CardIncrease(tempArr, resultVariant[1]);
	printf("Тип руки:%d\tКол-во очков:%d\n", resultVariant[1][0], resultVariant[1][1]);
	

	/*int currentCard = 0;
	int arrCoord[2] = {0};*/
			
	//int result[COL_CARDS][2] = { 0 };
		
	/*Формирование матрицы повторений*/


	/*while (arr[currentCard][0] != 0)
	{
		findCardCoor(arr[currentCard][0], arrCoord, map);
		for (int row = 0; row <= CTYPE-1 ; row++)
		{
			int item, i;
			if (row == arrCoord[0])	{continue;}
			item = findCardID(map, row, arrCoord[1]);
			i = 0;
			while (arr[i] != 0)
			{
				if (i == currentCard){i++;	continue;}
				if (item == arr[i][0])
				{
					if (result[currentCard][1] == 0) result[currentCard][1]++;
					result[currentCard][0] = arrCoord[1];
					result[currentCard][1]++;
				}
					
				i++;
			}
		}
		currentCard++;
	}*/
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