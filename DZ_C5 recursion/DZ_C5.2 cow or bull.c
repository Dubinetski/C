/*Задание 2
Написать игру «Быки и коровы».
Программа "загадывает" четырёхзначное число и играющий должен угадать его.
После ввода пользователем числа программа сообщает, сколько цифр числа угадано (быки)
и сколько цифр угадано и стоит на нужном месте (коровы).
После отгадывания числа на экран необходимо вывести количество сделанных пользователем попыток.
В программе необходимо использовать рекурсию.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int getNumber(int);
int randAtoB(int, int);
int bullOrCow(int);

int main()
{
	short const minNumber = 1000;                               //Минимально возможное число
	short const maxNumber = 9999;                               //Максимально возможное число

	srand(time(0));

	int number = randAtoB(minNumber, maxNumber);				//Загаданное компьютером число

	printf("Program set the four-digit number. You mast be guess its.\n");
	printf("After the every trying program will be say you\nhow much digits divine (bull),\
and how much of them\nhave a right positions (cow).\n");
	printf("(Exit: Ctrl+C)\n\n");

	//printf("%i\n", number); //для отладки
	printf("The number is %i. You use a %i trying.\n", number, bullOrCow(number));
}

/*Угадывание пользователем задуманного числа*/
int bullOrCow(int rightNumber)
{
	enum MyEnum
	{
		digitsOfNumber = 4                                       //константная величина цифр в числе (Си не поддерживает задание размера массива через int const)
	};
	static int countOfTruing = 0;                                //Номер попытки
	countOfTruing++;

	printf("Try %u. Number is:\t", countOfTruing);
	int enteringNumber = getNumber(digitsOfNumber);              //Полученное от пользователя число

	int rightNumberDigits[digitsOfNumber];
	int enteringNumberDigits[digitsOfNumber];

	int tmpNumber = rightNumber;
	for(int i = digitsOfNumber - 1; i >= 0; i--)
	{
		rightNumberDigits[i] = tmpNumber % 10;
		tmpNumber /= 10;

		enteringNumberDigits[i] = enteringNumber % 10;
		enteringNumber /= 10;
	}

	int cow = 0;                                                 //Колличество "коров" - цифра правильная и стоит на своем месте
	for(int i = 0; i < digitsOfNumber; i++)					     //Подсчет "коров" - выделен в отдельный цикл для исключения засчитывания "коров" в "быки"
	{
		if(enteringNumberDigits[i] == rightNumberDigits[i])
		{
			cow++;
			enteringNumberDigits[i] = rightNumberDigits[i] = -1; //для исключения последующего засчитывания данной цифры в "быки"
		}
	}

	int bull = 0;                                                //Колличество "быков" - цифра правильная но не на своем месте
	for(int i = 0; i < digitsOfNumber; i++)
	{
		for(int j = 0; (j < digitsOfNumber) && (enteringNumberDigits[i] != -1); j++)
		{
			if(enteringNumberDigits[i] == rightNumberDigits[j])
			{
				bull++;
				rightNumberDigits[j] = -1;                       //для исключения повторного засчитывания данной цифры
				break;                                           //выходим во внешний цикл для исключения засчитывания одного "быка" несколько раз в случае повторения цифры в исходном числе
			}
		}
	}
	printf("bull = %i, cow = %i\n", bull, cow);

	if(cow == digitsOfNumber)
	{
		return countOfTruing;
	}
	bullOrCow(rightNumber);										//Рекурсивный вызов функции для следующей попытки угадывания числа
	return countOfTruing;
}

/*Получает от пользователя одно целое число*/
int getNumber(int digitsInNumber)                               //проверка корректности ввода
{
	int userNumber;                                             //Введенное пользователем число
	while((scanf("%i", &userNumber) != 1) || (userNumber % (int) pow(10, digitsInNumber) != userNumber))
	{
		printf("Incorrect number. Pleasee try again.\n");
		while(getchar() != '\n') {}								//очистка потока ввода
	}
	return userNumber;
}

/*Генерирует случайное число в заданном диапазоне*/
int randAtoB(int min, int max)
{
	return rand() % (max - min) + min;
}
