/*Задание 1
Нарисовать елку звездочками на экране :
           *
          ***
         *****
        *******
       *********
Высота елки задается с клавиатуры пользователем.*/

#include <stdio.h>
#include <stdbool.h>

int main (void) {
	short heightTree;								//Высота ели

	/*Пользовательский ввод с проверкой корректности*/
	while (true) {
		printf ("Enter hight tree:\t");
		if (scanf ("%hi" , &heightTree) == 1 && heightTree > 0) {
			break;
		}
		printf ("Incorrect number. Pleasee enter the positive integer number\n\n");
		while (getchar () != '\n') {
		}
	}

	/*Отрисовка ели*/
	for (int i = 1; i <= heightTree; i++) {
		for (int j = 1; j <= heightTree + i - 1; j++) {
			if (j <= heightTree - i) {
				printf (" ");
			}
			else {
				printf ("*");
			}
		}
		printf ("\n");
	}
}
