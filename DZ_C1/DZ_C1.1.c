/*
Задание 1:
Написать программу, вычисляющую, с какой скоростью бегун пробежал дистанцию.
Рекомендуемый вид экрана во время выполнения программы приведен ниже:
Вычисление скорости бега
Длина дистанции = 1000 м
Время (мин.сек) = 3.25
Время: 3 мин 25 сек = 205 сек
Вы бежали со скоростью 17.56 км/ч
Длина дистанции и время задается в коде программы в переменных.

Для примера взята длина марафона и время мужского мирового рекорда на этой дистанции
*/

#include <stdio.h>			
#include <math.h>
#include <stdlib.h>													//подключение библиотеки для использования функции system()
int main()
{
	unsigned short distance = 42195;								//Длина дистанции
	float time = 122.57;											//Время бега (минуты.секунды)

	printf("Calculating the running speed\n\n");
	printf("Distance \t= %hu m\n", distance);						//hu - unsigned short
	printf("Time (min.sec) \t= %4.2f\n\n", time);

	unsigned short minutes = (unsigned short)time;					//Полных минут бега
	
	char seconds = (char)roundf((time - minutes)*100);				//Число секунд бега сверх полных минут 
																	/*roundf() применено для исключения случаев когда числанаподобие 56.9999999999 при приведении к целому не становились 56*/	
	unsigned short time_in_seconds = minutes * 60 + seconds;		//Все время бега в секундах
	float speed = (float)distance / time_in_seconds;				//Скорость бега 
	speed *= 3.6;													//Перевод из м/с в км/ч

	printf("Time: %hu minutes %hu seconds = %hu seconds\n\n",
				  minutes,	  seconds,		time_in_seconds);
	printf("You ran with the speed %.2f km/h\n\n\n", speed);
	system("pause");												//чтобы консоль не закрывалась сразу после выполнения программы
}