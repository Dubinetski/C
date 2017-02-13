/*
Задание 2
Найти сумму положительных элементов двумерного массива.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_ROW 5                                 //Колличество строк массиве
#define ARRAY_COLLUMN 10                            //Длина строк массива
#define MAX_NUMBER 100                              //Максимально возможный элемент массива

void getRandomArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount);
void printArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount);
int summPositiveElenentsOfArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount);
int randSigned();

int main()
{
    int arrayIntNumbers[ARRAY_ROW][ARRAY_COLLUMN];  //целочисленный массив
    getRandomArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN);

    printf("Random array %ix%i:\n", ARRAY_ROW, ARRAY_COLLUMN);
    printArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN);

    printf("\nSumm posiive elements of array: %i.\n\n", summPositiveElenentsOfArray(arrayIntNumbers, ARRAY_ROW, ARRAY_COLLUMN));
}

/*Заполнение массива случайными числами*/
void getRandomArray(int array[ARRAY_ROW][ARRAY_COLLUMN], char rowCount, char collumnCount)
{
    srand(time(0) * 1000);                          //х1000 для более быстрого обновления стартового значения
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
