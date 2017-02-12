/*Задание 1
Написать рекурсивную функцию нахождения наибольшего общего делителя двух целых чисел.
*/

#include <stdio.h>

int gcd(int firstNumber, int secondNumber, int divisor);
int getNumber(void);

int main()
{
	printf("Program find the greatest common divisor of two numbers\n\n");

	printf("First number =\t");
	int firstNumber = getNumber();				//первое число

	printf("Second number = ");
	int secondNumber = getNumber();				//второе число

	int minNumber = (firstNumber <= secondNumber) ? firstNumber : secondNumber; //меньшее число
	minNumber *= (minNumber < 0) ? -1 : 1;		//в случае если меньшее число отрицательное

	printf("%i\n", gcd(firstNumber, secondNumber, minNumber));
}

/*Наибольший общий делитель*/
int gcd(int firstNumber, int secondNumber, int divisor)
{
	return ((firstNumber % divisor == 0) && (secondNumber % divisor == 0)) ? divisor : gcd(firstNumber, secondNumber, divisor - 1);
}

/*Получает от пользователя одно целое число*/
int getNumber(void)								//проверка корректности ввода
{
	int userNumber;								//Введенное пользователем число
	while((scanf("%i", &userNumber) != 1) || (userNumber==0))
	{
		printf("Incorrect number. Pleasee try again.\n");
		while(getchar() != '\n') {}			    //очистка потока ввода
	}
	return userNumber;
}
