/*
Задание 3
Найти произведение всех целых чисел от a до 20 (значение a вводится с клавиатуры: 1 <= a <= 20).*/

#include <stdio.h>
#include <stdbool.h>

int main (void) {
	char const endRange = 20;								//Конец диапазона
	float startRange;										//Начало диапазона

	printf ("Program is calculate a multiplication of the integer numbers from A to 20.\nWere A is a number between 1 and 20.\n\n");
	/*Пользовательский ввод с проверкой корректности*/
	while (true) {
		printf ("A = ");
		if (scanf ("%f" , &startRange) == 1 && startRange >= 1 && startRange <= endRange) {
			break;
		}
		printf ("Incorrect value of beginning of range. Pleasee enter number from 1 to %hu.\n\n",endRange);
		while (getchar () != '\n') {
		}
	}

	unsigned long long multiplicationIntegerNumbers = 1;						   //Произведение целых чисел из диапазона
	
	int i = startRange;
	if (startRange != (int) startRange) {
		i += 1;
	}
	for (; i <= endRange; i++) {
		multiplicationIntegerNumbers *= i;
	}

	printf ("\nMultiplication of integer numbers of range from %0.1f to %hu:\n\n%llu\n\n" , startRange , endRange , multiplicationIntegerNumbers);
}

