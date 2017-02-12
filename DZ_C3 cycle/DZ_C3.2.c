/*
Задание 2
Напишите программу , которая вычисляет сумму целых чисел от а до 500(значение a вводится с клавиатуры).*/

#include <stdio.h>
#include <stdbool.h>

int main (void) {
	float endRange = 500;								//Конец диапазона
	float startRange;									//Начало диапазона

	printf ("Program is calculate a summ of the integer numbers between A and %.0f.\n\n" , endRange);
	/*Пользовательский ввод с проверкой корректности*/
	while (true) {
		printf ("Enter a beginning of range: ");
		if (scanf ("%f" , &startRange) == 1) {
			break;
		}
		printf ("Incorrect value of beginning of range. Pleasee enter number.\n\n");
		while (getchar () != '\n') {
		}
	}
	/*Расстановка границ диапазона в порядке возрастания*/
	if (startRange > endRange) {
		float k = endRange;
		endRange = startRange;
		startRange = k;
	}

	int summIntegerNumbers = 0;											//Сумма целых чисел из диапазона
	int i = startRange;
	if (startRange != (int) startRange && startRange > 0) {				//Определение первого целого числа, в случае ввода пользователем вещественного числа
		i += 1;
	}
	/*Вычисление произведения целых чисел диапазона.*/
	for (; i <= endRange; i++) {
		summIntegerNumbers += i;
	}

	printf ("\nSumm of integer numbers of range from %0.1f to %0.1f:\t%i\n\n" , startRange , endRange , summIntegerNumbers);
}

