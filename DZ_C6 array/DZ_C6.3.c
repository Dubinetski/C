/*
Задание 3
Даны два одномерных массива А и В одинаковой размерности. Получить третий массив Р
такой же размерности, каждый элемент которого равен сумме соответствующих
элементов данных массивов. Значения элементов массивов А и В задать датчиком
случайных чисел.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10                       //Колличество строк массиве
#define MAX_NUMBER 100                      //Максимально возможный элемент массива

void fillRandomArray(int array[], char lengthArray);
void summArrays(int firstArray[], int secondArray[], int summArray[], char lengthArray);
void printArray(int array[], char lengthArray);

int main()
{
    srand(time(0) * 1000);

    int firstArray[ARRAY_SIZE];             //первый массив
    fillRandomArray(firstArray, ARRAY_SIZE);
    printf("First array: \n");
    printArray(firstArray, ARRAY_SIZE);

    int secondArray[ARRAY_SIZE];            //второй массив
    getRandomArray(secondArray, ARRAY_SIZE);
    printf("\nSecond array: \n");
    printArray(secondArray, ARRAY_SIZE);

    int summArray[ARRAY_SIZE];              //массив из суммы соответствующих элементов первого и второго массива
    summArrays(firstArray, secondArray, summArray, ARRAY_SIZE);
    printf("\nSumm array:.\n");
    printArray(summArray, ARRAY_SIZE);
}

/*Заполнение массива случайными числами*/
void fillRandomArray(int array[], char lengthArray)
{
    for(char i = 0; i < lengthArray; i++)
    {
        array[i] = rand() % MAX_NUMBER;
    }
}

/*Получение массива из суммы соответствующих элементов первого и второго массивов*/
void summArrays(int firstArray[], int secondArray[], int summArray[], char arrayLength)
{
    for(char i = 0; i < arrayLength; i++)
    {
        summArray[i] = firstArray[i] + secondArray[i];
    }
}

/*Вывод массива на консоль*/
void printArray(int array[], char arrayLength)
{
    for(char i = 0; i < arrayLength; i++)
    {
        printf("%-5i ", array[i]);
    }
    printf("\n");
}
