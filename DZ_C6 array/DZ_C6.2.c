/*
Задание 2
Найти сумму положительных элементов двумерного массива.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_ROW_COUNT 5                                 //Колличество строк массиве
#define ARRAY_COLUMN_COUNT 10                            //Длина строк массива
#define MAX_NUMBER 100                              //Максимально возможный элемент массива

void fillRandomArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char columnCount);
void printArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char columnCount);
int summPositiveElenentsOfArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char columnCount);
int getSignedRandNumber();

int main()
{
    int arrayIntNumbers[ARRAY_ROW][ARRAY_COLLUMN];  //целочисленный массив
    srand(time(0) * 1000);                          //х1000 для более быстрого обновления стартового значения
    
    fillRandomArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN);

    printf("Random array %ix%i:\n", ARRAY_ROW, ARRAY_COLLUMN);
    printArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN);

    printf("\nSumm posiive elements of array: %i.\n\n", summPositiveElenentsOfArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN));
}

/*Заполнение массива случайными числами*/
void fillRandomArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount)
{
    for(char row = 0; row < rowCount; row++)
    {
        for(char collumn = 0; collumn < collumnCount; collumn++)
        {
            array[row][collumn] = randSigned();
        }
    }
}

/*Подсчет колличества ненулевых элементов массива*/
int summPositiveElenentsOfArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount)
{
    int summPositiveElenents = 0;                   //Сумма положительных элементов массива
    for(char row = 0; row < rowCount; row++)
    {
        for(char collumn = 0; collumn < collumnCount; collumn++)
        {
            if(array[row][collumn] > 0)
            {
                summPositiveElenents += array[row][collumn];
            }
        }
    }
    return summPositiveElenents;
}

/*Вывод массива на консоль*/
void printArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount)
{
    for(char row = 0; row < rowCount; row++)
    {
        for(char collumn = 0; collumn < collumnCount; collumn++)
        {
            printf("%5i ", array[row][collumn]);
        }
        printf("\n");
    }
}

/*Генерирует случайное число (со знаком)*/
int randSigned()
{
    return  rand() % (2 * MAX_NUMBER) - MAX_NUMBER;
}
