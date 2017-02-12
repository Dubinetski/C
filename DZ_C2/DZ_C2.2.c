/*Грузовой самолет должен пролететь с грузом из пункта А в пункт С через пункт В.
Емкость бака для топлива у самолета – 300литров. Потребление топлива на 1 км в
зависимости от веса груза у самолета следующее:
- до 500 кг: 1 литров / км
- до 1000 кг: 4 литров / км
- до 1500 кг: 7 литров / км
- до 2000 кг: 9 литров / км.
- более 2000 кг – самолет не поднимает.
Пользователь вводит расстояние между пунктами А и В, и расстояние между пунктами В
и С, а также вес груза. Программа должна рассчитать какое минимальное количество
топлива необходимо для дозаправки самолету в пункте В, чтобы долететь из пункта А в
пункт С. В случае невозможности преодолеть любое из расстояний – программа должна
вывести сообщение о невозможности полета по введенному маршруту. */

#include <stdio.h>
#include <stdbool.h>

int main () {

	enum WeightLimits {										//Лимиты перевозимого груза (л/км)
		WeightLimits1 = 500 ,
		WeightLimits2 = 1000 ,
		WeightLimits3 = 1500 ,
		WeightLimits4 = 2000
	};
	enum Consumption {										//Расход топлива в зависимости от веса груза (л/км)
		fuelConsumptionInLimit1 = 1 ,
		fuelConsumptionInLimit2 = 4 ,
		fuelConsumptionInLimit3 = 7 ,
		fuelConsumptionInLimit4 = 9
	};
	unsigned short const tankVolume = 300;					//Объем топливного бака

	float distanceFromAtoB;									//Расстояние между пунктами А и В
	float distanceFromBtoC;									//Расстояние между пунктами В и С
	float weight;											//Вес груза
	float fuelConsumption;									//Расход топлива

	char c;													//Временная переменная

	printf ("Program calculate the value of refueling in point B\nfor the successful flying from point A to point C.\n\n");

	/*Получение исходных данных с проверкой их корректности и очисткой потока ввода от "мусора"*/
	while (true) {
		printf ("Distance from points A to B (km):\t");
		c = scanf ("%f" , &distanceFromAtoB);
		if (c == 1 && distanceFromAtoB > 0) break;
		printf ("Incorrect number. Please try again\n\n");
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
	}
	while (true) {
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
		printf ("Distance from points B to C (km):\t");
		c = scanf ("%f" , &distanceFromBtoC);
		if (c == 1 && distanceFromBtoC > 0) break;
		printf ("Incorrect number. Please try again\n\n");
	}
	while (true) {
		do {
			c = getchar ();
		} while (c != '\n' && c != EOF);
		printf ("Weight (kg):\t\t\t\t");
		c = scanf ("%f" , &weight);
		if (c == 1 && weight >= 0) break;
		printf ("Incorrect number. Please try again\n\n");
	}
	/*Нахождение расхода топлива в зависимости от веса груза*/
	if (weight < WeightLimits1) fuelConsumption = fuelConsumptionInLimit1;
	else {
		if (weight < WeightLimits2) fuelConsumption = fuelConsumptionInLimit2;
		else {
			if (weight < WeightLimits3) fuelConsumption = fuelConsumptionInLimit3;
			else {
				if (weight < WeightLimits4) fuelConsumption = fuelConsumptionInLimit4;
				else {
					printf ("Airplane don't pick up more then 2000 kg weight.\n\n");
					return 1;
				}
			}
		}
	}
	float fuelNeedToFlyFromAtoB = distanceFromAtoB * fuelConsumption;		//Требуется толива для полета из пункта А в пункт В
	float fuelNeedToFlyFromBtoC = distanceFromBtoC * fuelConsumption;		//Требуется толива для полета из пункта В в пункт С

	float maxFuelConsumption;												//Максимально возможный расход топлива
	unsigned short maxWeight = 0;											//Максимальный вес груза

	/*Проверка достаточности топлива для полета с заданным грузом.
	При невозможности полета сообщается сколько нужно долить бензина в пункте В
	либо, если нужно топлива больше чем вместимость топливного бака,
	на сколько кг уменьшить перевозимый груз.*/
	if (fuelNeedToFlyFromAtoB > tankVolume) {
		maxFuelConsumption = tankVolume / distanceFromAtoB;
		if (maxFuelConsumption > fuelConsumptionInLimit3) maxWeight = WeightLimits3;
		else {
			if (maxFuelConsumption > fuelConsumptionInLimit2) maxWeight = WeightLimits2;
			else {
				if (maxFuelConsumption > fuelConsumptionInLimit1) maxWeight = WeightLimits1;
			}
		}
		maxWeight ?
			printf ("\nFlying is not possible.\nWeight mast be less then %hu kg.\n\n" , maxWeight) :
			printf ("\nEven empty airplane can't fly from point A to point B.\n\n");
	}
	else {
		if (fuelNeedToFlyFromBtoC > tankVolume) {
			maxFuelConsumption = tankVolume / distanceFromBtoC;
			if (maxFuelConsumption > fuelConsumptionInLimit3) maxWeight = WeightLimits3;
			else {
				if (maxFuelConsumption > fuelConsumptionInLimit2) maxWeight = WeightLimits2;
				else {
					if (maxFuelConsumption > fuelConsumptionInLimit1) maxWeight = WeightLimits1;
				}
			}
			maxWeight ?
				printf ("\nFlying is not possible.\nWeight mast be less then %hu kg.\nYou may unship %0.1f kg weight in point B.\n\n" , maxWeight , weight - maxWeight + 1) :
				printf ("\nFlying is possible only to point B.\nEven empty airplane can't fly from point B to point C.\n\n");
		}
		else {
			float fuelNeedAdd = fuelNeedToFlyFromBtoC + fuelNeedToFlyFromAtoB - tankVolume;
			fuelNeedAdd > 0 ?
				printf ("\nNeed add %0.1f l fuel in point B for flying to point C.\n\n" , fuelNeedAdd) :
				printf ("\nFuel is enough. Add not need.\n");
		}
	}
}



