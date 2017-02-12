/*Задание 3 
Пользователь вводит с клавиатуры расстояние, расход бензина на 100 км и стоимость трех 
видов  бензина.  Вывести  на  экран  сравнительную  таблицу  (используя  спецсимволы  из 
таблицы ASCII для рисования таблиц) со стоимостью поездки на разных видах бензина.*/

#include <stdio.h>													
#include <stdlib.h>
int main()
{
	float distance;													//Расстояние
	float consumption;												//Расход топлива на 100 км
	float fuel_ron80_cost, fuel_ron92_cost, fuel_ron95_cost;		

	printf("Please enter the initial data for the calculation of the trip cost.\n\n");
	printf("Distanse (km):\t\t\t");
	scanf("%f", &distance);
	printf("Fuel consumption (l/100 km):\t");
	scanf("%f", &consumption);
	printf("\nCost 80 RON fuel (BYN):\t\t");
	scanf("%f", &fuel_ron80_cost);
	printf("Cost 92 RON fuel (BYN):\t\t");
	scanf("%f", &fuel_ron92_cost);
	printf("Cost 95 RON fuel (BYN):\t\t");
	scanf("%f", &fuel_ron95_cost);

	/*Для отладки*/
	//distance = 1520.5;
	//consumption = 5.2;
	//fuel_ron80_cost = 1.2;
	//fuel_ron92_cost = 2.3;
	//fuel_ron95_cost = 3.5;
	
	float trip_cost_ron80 = distance*consumption*fuel_ron80_cost/100;				//стоимость бензина Аи-80
	float trip_cost_ron92 = distance*consumption*fuel_ron92_cost/100;				//стоимость бензина Аи-92
	float trip_cost_ron95 = distance*consumption*fuel_ron95_cost/100;				//стоимость бензина Аи-95

	/*
	╔══════════════════════════╗
	║     Trip is cost, BYN	   ║
	╠════════╦════════╦════════╣
	║ RON 80 ║ RON 92 ║ RON 95 ║
	╠════════╬════════╬════════╣
	║ xx.xx  ║ xx.xx  ║ xx.xx  ║
	╚════════╩════════╩════════╝

	╔ - 201		╦ - 203		╗ - 187		║ - 186		
	╠ - 204		╬ - 206		╣ - 185		═ - 205		
	╚ - 200		╩ - 202		╝ - 188			

	*/
	
	printf("\n\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("\t%c%7s%-23s%c\n", 186, " ","Trip is cost, BYN", 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205,205,205, 205, 205, 205, 205, 205,205, 203, 205,205, 205, 205, 205, 205,205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205,205,205,205, 185);
	printf("\t%c  %s%c  %s%c  %s%c\n", 186, "80 RON ", 186, "92 RON ",186, "95 RON  ",186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 185);
	printf("\t%c%-9s%c%-9s%c%-10s%c\n", 186, " ", 186, " ", 186, " ", 186);
	printf("\t%c  %-6.2f %c  %-7.2f%c  %-8.2f%c\n", 186, trip_cost_ron80, 186, trip_cost_ron92, 186, trip_cost_ron95, 186);
	printf("\t%c%-9s%c%-9s%c%-10s%c\n", 186, " ", 186, " ", 186, " ", 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
	
	system("pause");												
}