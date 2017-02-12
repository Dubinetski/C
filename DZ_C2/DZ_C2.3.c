/*Задание 3
Зарплата менеджера составляет 200$ + процент от продаж , продажи до 500$ - 3 % , от 500
до 1000 – 5 % , свыше 1000 – 8 % .Пользователь вводит с клавиатуры уровень продаж для
трех менеджеров.Определить их зарплату , определить лучшего менеджера , начислить
ему премию 200$ , вывести итоги на экран.*/


#include <stdio.h>
#include <stdbool.h>

int main () {
	enum limitSail {
		limitSail1 = 500 ,									//Величина продаж для начисления повышенной премии
		limitSail2 = 1000									//Величина продаж для начисления максимальной премии
	};
	float const premiumInRateSale1 = 0.03;					//Базовый процент премии
	float const premiumInRateSale2 = 0.05;					//Процент повышенной премии
	float const premiumInRateSale3 = 0.08;					//Максимальный процент премии
	unsigned short const defaultPay = 200;					//Оклад
	unsigned short const premiumPay = 200;					//Бонусная премия за лучшие продажи

	float saleFirstManager;									//Продажи первого менеджера
	float saleSecondManager;								//Продажи второго менеджера
	float saleThirdManager;									//Продажи третьего менеджера

	char c;													//Временная переменная

	printf ("Program calculate pay of managers and define better of them.\n\n");

	/*Получение исходных данных с проверкой их корректности и очисткой потока ввода от "мусора"*/
	while (true) {
		printf ("Sale fitst manager ($):\t\t");
		c = scanf ("%f" , &saleFirstManager);
		if (c == 1 && saleFirstManager > 0) break;
		printf ("Incorrect number. Please try again\n\n");
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
	}
	while (true) {
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
		printf ("Sale second manager ($):\t");
		c = scanf ("%f" , &saleSecondManager);
		if (c == 1 && saleSecondManager > 0) break;
		printf ("Incorrect number. Please try again\n\n");
	}
	while (true) {
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
		printf ("Sale third manager ($):\t\t");
		c = scanf ("%f" , &saleThirdManager);
		if (c == 1 && saleThirdManager > 0) break;
		printf ("Incorrect number. Please try again\n\n");
	}
	float payFirstManager = defaultPay;						//Зарплата первого менеджера
	float paySecondtManager = defaultPay;					//Зарплата второго менеджера
	float payThirdManager = defaultPay;						//Зарплата третьего менеджера

	/*Определение процентов премии для каждого менеджера в зависимости от объема его продаж*/
	if (saleFirstManager > limitSail2) payFirstManager += saleFirstManager*premiumInRateSale3;
	else {
		if (saleFirstManager > limitSail1) payFirstManager += saleFirstManager*premiumInRateSale2;
		else {
			payFirstManager += saleFirstManager*premiumInRateSale1;
		}
	}
	if (saleSecondManager > limitSail2) paySecondtManager += saleSecondManager*premiumInRateSale3;
	else {
		if (saleSecondManager > limitSail1) paySecondtManager += saleSecondManager*premiumInRateSale2;
		else {
			paySecondtManager += saleSecondManager*premiumInRateSale1;
		}
	}
	if (saleThirdManager > limitSail2) payThirdManager += saleThirdManager*premiumInRateSale3;
	else {
		if (saleThirdManager > limitSail1) payThirdManager += saleThirdManager*premiumInRateSale2;
		else {
			payThirdManager += saleThirdManager*premiumInRateSale1;
		}
	}
	/*Определение менеджера продавшего больше остальных и начисление ему за это дополнительной премии*/
	if (saleFirstManager > saleSecondManager && saleFirstManager > saleThirdManager) {
		payFirstManager += premiumPay;
		printf ("\nThe First manager have a best sale.\n\n");
	}
	else {
		if (saleSecondManager > saleFirstManager && saleSecondManager > saleThirdManager) {
			paySecondtManager += premiumPay;
			printf ("\nThe Second manager have a best sale.\n\n");
		}
		else {
			payThirdManager += premiumPay;
			printf ("\nThe Third manager have a best sale.\n\n");
		}
	}
	/*Вывод результатов на экран*/
	printf ("Pay First manager:\t\t%0.1f\n" , payFirstManager);
	printf ("Pay Second manager:\t\t%0.1f\n" , paySecondtManager);
	printf ("Pay Third manager:\t\t%0.1f\n" , payThirdManager);
}