/*«адание 2: 
ѕользователь  вводит  с  клавиатуры  врем¤  начала  и  врем¤  завершени¤  телефонного 
разговора  (часы,  минуты  и  секунды).  ѕосчитать  стоимость  разговора,  если  стоимость 
минуты Ц 30 копеек. */

#include <stdio.h>																			//библиотеки ввода/вывода
#include <stdlib.h>																			//дл¤ использовани¤ функции system()
#include <stdbool.h>																		//библиотека логического типа
int main()
{
	unsigned short talk_start_hour, talk_start_minutes, talk_start_seconds;		
	unsigned short talk_finish_hour, talk_finish_minutes, talk_finish_seconds;
	char talk_minutes_cost = 30;															//стоимость минуты разговора
	
	printf("Input time beginning and ending your talk\n\n");
	//unsigned short rez;

	while (true) {																			//выход из цикла осуществл¤етс¤ в блоке if внутри цикла
		printf("Beginning talk (hh.mm.ss):\t");
		scanf("%hu.%hu.%hu", &talk_start_hour, &talk_start_minutes, &talk_start_seconds);	//ввод времени начала разговора с разделением часов, минут и секунд точками
		if (talk_start_hour <= 24 && talk_start_minutes <= 59 && talk_start_seconds <= 59)	//проверка корректности ввода времени
			break;																			//выход из цикла в случае корректно введенного времени
		printf("Incorrect time format. Please try again.\n\n");
	}
	
	while (true) {																			//выход из цикла осуществл¤етс¤ в блоке if внутри цикла
		printf("Ending talk (hh.mm.ss):\t\t");
		scanf("%hu.%hu.%hu", &talk_finish_hour, &talk_finish_minutes, &talk_finish_seconds);
		if (talk_finish_hour <= 24 && talk_finish_minutes <= 59 && talk_finish_seconds <= 59)
			break;
		printf("Incorrect time format. Please try again.\n\n");
	}

	unsigned int talk_start = talk_start_hour * 3600 + talk_start_minutes * 60 + talk_start_seconds;	//число секунд с начала суток до начала разговора
	unsigned int talk_finish = talk_finish_hour * 3600 + talk_finish_minutes * 60 + talk_finish_seconds;//число секунд с начала суток до окончани¤ разговора
	
	/*¬ычисл¤ем длительность разговора с проверкой "конца суток". »спользован тернарный оператор.*/
	unsigned int talk_duration = talk_finish > talk_start ? talk_finish - talk_start: 24*3600+talk_finish - talk_start; //ƒлительность разговора в секундах
	
	/*¬ывод на экран длительности разговора с разбивкой на часы, минуты, секунды*/
	printf("\nDuration of talk: %hi hour %hi minutes %hi seconds.\n\n", talk_duration/3600,talk_duration%3600/60,talk_duration%60);
	
	/*≈сли число секунд не равно нулю выражение (talk_duration%60!=0) будет истинно, а значит равно 1*/
	unsigned short talk_cost = (talk_duration/60+(talk_duration%60!=0))*talk_minutes_cost;	//стоимость разговора
		
	printf("Cost of talk: %hu r %hu k\n\n", talk_cost/100,talk_cost%100);					//вывод стоимости разговора с разбивкой на рубли и копейки
	
	system("pause");																		//чтобы консоль не закрывалась сразу при запуске
}