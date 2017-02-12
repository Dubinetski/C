/*Задание 1
Нарисовать елку звездочками на экране :
*						  +1	  1
***						  +2	  3
******					  +3	  6
**********				  +4	  10 <--высота елки
******					  +3	  6
***						  +2	  3
*						  +1	  1
Высота елки задается с клавиатуры пользователем.*/

#include <stdio.h>
#include <stdbool.h>

int main (void) {
	short heightTree;								//Высота ели

	/*Пользовательский ввод с проверкой корректности*/
	while (true) {
		printf ("Enter hight tree:\t");
		if (scanf ("%hi" , &heightTree) == 1 && heightTree >= 1) {
			break;
		}
		printf ("Incorrect number. Pleasee enter the positive integer number\n\n");
		while (getchar () != '\n') {
		}
	}

	short wedth = 0;								//Половина ширины ели
	char step = 0;									//Шаг приращения высоты
													/*Нахождение "радиуса" елки*/
	for (char i = 1; i <= heightTree; i += step) {
		wedth++;
		step++;
	}

	short height = 1;
	step = 1;

	for (int i = 1; i <= wedth * 2 - 1; i++) {	   //смещение по вертикали
		for (int j = 1; j <= height; j++) {		   //смещение по горизонтали
			printf ("*");
		}
		printf ("\n");
		if (i<wedth) {
			step++;
			height += step;
		}
		else {
			height -= step;
			step--;
		}
	}
}
