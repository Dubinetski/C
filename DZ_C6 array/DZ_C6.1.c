/*
Задание 1
Написать программу, которая вводит с клавиатуры массив из 10 целых чисел,
после чего выводит количество ненулевых элементов.
Перед вводом каждого элемента должна выводится подсказка с номером элемента.
*/

#include <stdio.h>

#define ARRAY_SIZE 10                       //Колличество элементов в массиве

void getArray(int array[], char arrayLength);
char countNonZeroElenentsInArray(int array[], char arrayLength);
int getIntNumber();

int main()
{
    printf("Please enter %i integer numbers.\n\n", ARRAY_SIZE);

    int intNumbers[ARRAY_SIZE];        //Целочисленный массив
    getArray(intNumbers, ARRAY_SIZE);  //получить массив

    printf("\nYou entering the %i non-zero numbers.\n", countNonZeroElenentsInArray(intNumbers, ARRAY_SIZE));
}

/*Получение массива чисел от пользователя*/
void getArray(int array[], char arrayLength)
{
    for(char i = 0; i < arrayLength; i++)
    {
        printf("%2i : ", i + 1);
        array[i] = getIntNumber();
    }
}

/*Подсчет колличества ненулевых элементов массива*/
char countNonZeroElenentsInArray(int array[], char arrayLength)
{
    char nonZeroCount = 0;                  //Счетчик ненулевых элементов
    for(char i = 0; i < arrayLength; i++)
    {
        if(array[i] != 0)
        {
            nonZeroCount++;
        }
    }
    return nonZeroCount;
}

/*Получение от пользователя одного целого числа*/
int getIntNumber()
{
    float enteringNumber;                   //Введенное пользователем число
    while((scanf("%f", &enteringNumber) != 1) || (enteringNumber != (int)enteringNumber))
    {
        printf("Incorrect number. Pleasee try again.\n");
        while(getchar() != '\n') {}         //очистка потока ввода
    }
    return (int)enteringNumber;
}
