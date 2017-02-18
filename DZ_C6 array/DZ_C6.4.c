/*
Задание 4
Даны целые массивы А[10], B[10], C[10]. Каждый массив преобразовать по правилу: если
компоненты массива образуют убывающую последовательность, то все отрицательные
компоненты следует заменить на значении 0. В противном случае массив оставить без
изменений.
*/

#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 10                       //Колличество строк массиве

void getArray(int array[], char lengthArray);
int getIntNumber();
bool isDecreasingArray(int array[], char lengthArray);
void changeNegativeElementsToZero(int array[], char lengthArray);
void printArray(int array[], char lengthArray);

int main()
{
    /*Заполнение массивов*/
    int firstArray[ARRAY_SIZE];             //первый массив
    printf("Enter elements first array.\n");
    getArray(firstArray, ARRAY_SIZE);

    int secondArray[ARRAY_SIZE];            //второй массив
    printf("Enter elements second array.\n");
    getArray(secondArray, ARRAY_SIZE);

    int therdArray[ARRAY_SIZE];             //третий массив
    printf("Enter elements therd array.\n");
    getArray(therdArray, ARRAY_SIZE);

    /*Замена отрицательных элементов убывающих массивов нулями*/
    if (isDecreasingArray(firstArray, ARRAY_SIZE))
    {
        changeNegativeElementsToZero(firstArray, ARRAY_SIZE);
    }
    if (isDecreasingArray(secondArray, ARRAY_SIZE))
    {
        changeNegativeElementsToZero(secondArray, ARRAY_SIZE);
    }
    if (isDecreasingArray(therdArray, ARRAY_SIZE))
    {
        changeNegativeElementsToZero(therdArray, ARRAY_SIZE);
    }

    /*Вывод результатов на консоль*/
    printf("First array:\t");
    printArray(firstArray, ARRAY_SIZE);
    printf("Second array:\t");
    printArray(secondArray, ARRAY_SIZE);
    printf("Therd array:\t");
    printArray(therdArray, ARRAY_SIZE);
}

/*Получение массива целых чисел от пользователя*/
void getArray(int array[], char lengthArray)
{
    for (int i = 0; i < lengthArray; i++)
    {
        printf("%2i : ", i + 1);
        array[i] = getIntNumber();
    }
    printf("\n");
}

/*Получение от пользователя одного целого числа*/
int getIntNumber(void)
{
    float enteringNumber;                   //Введенное пользователем число
    while ((scanf("%f", &enteringNumber) != 1) || (enteringNumber != (int)enteringNumber))
    {
        printf("Incorrect number. Pleasee try again.\n");
        while(getchar() != '\n') {}         //очистка потока ввода
    }
    return (int)enteringNumber;
}

/*Убывающий ли массив?*/
bool isDecreasingArray(int array[], char lengthArray)
{
    for (char i = 1; i < lengthArray; i++)
    {
        if (array[i] > array[i - 1])
        {
            return false;
        }
    }
    return true;
}

/*Замена отрицательных элементов массива нулями*/
void changeNegativeElementsToZero(int array[], char lengthArray)
{
    for (char i = 0; i < lengthArray; i++)
    {
        if (array[i] < 0)
        {
            array[i] = 0;
        }
    }
}

/*Вывод массива на консоль*/
void printArray(int array[], char lengthArray)
{
    for (char i = 0; i < lengthArray; i++)
    {
        printf("%-5i ", array[i]);
    }
    printf("\n");
}
