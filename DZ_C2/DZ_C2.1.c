/*Задание 1 
Пользователь вводит четырехзначное число. Необходимо поменять в этом числе 1 и 2 
цифры, а также 3 и 4 цифры. Если пользователь вводит не четырехзначное число – 
вывести сообщение об ошибке.*/

#include <stdio.h>
#include <stdbool.h>

int main (){
	short number;														//Введенное число
	short newNumber;													//Преобразованное число
	short const minNumber = 1000;										//Минимально возможное число
	short const maxNumber = 9999;										//Максимально возможное число
	char c;																//временная переменная

	printf ("Programm change 1 with 2 and 3 with 4 digits in nomber.\n\n");

	/*Получение числа с проверкой корректности ввода*/
	while (true){
		printf ("Please enter a four-digit number:\t");

		c = scanf ("%hi" , &number);										//Функция scanf() возвращает число успешно считанных и преобразованых в требуемый тип значений
		if (c == 1 && number >= minNumber && number <= maxNumber) break;	//Если введено число и оно находится в диапазоне 1000-9999, то ввод корректен - выходим из цикла		   

		printf ("Incorrect number. Please try again\n\n");

		/*Для очистки потока ввода считываем все, что в нем хранится*/
		do{
			c = getchar ();
		} while (c != '\n' && c != EOF);
	}

	char firstDigit = number / 1000;									//Первая цифра исходного числа
	char secondDigit = number % 1000 / 100;								//Вторая цифра исходного числа
	char fourthDigit = number % 10;										//Четвертая цифра исходного числа
	char thirdDigit = number % 100 / 10;								//Третья цифра исходного числа

	newNumber = secondDigit * 1000 + firstDigit * 100 + fourthDigit * 10 + thirdDigit;

	printf ("Number after transformation:\t\t%4hi\n\n" , newNumber);
}