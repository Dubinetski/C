/*Задание 2 
Вывести на экран фигуры, заполненные звездочками.
Диалог с пользователем реализовать при помощи меню.*/

#include <stdio.h>
#include <stdbool.h>

#define ESC '\x1b'
#define ENTER '\r'

enum triangle {None=0, Up, Right, Down, Left};

int main()
{
    char firthtFullTriangle;                                       //номер первого закрашенного треугольника фигуры
    char secondFullTriangle;                                       //номер второго закрашенного треугольника фигуры
    char size = 20;                                                //ширина квадрата

    while (true)
    {
        printf("Choise the figure:\n");
        printf("0\tUpper right corner of square\n");               //верхний правый угол
        printf("1\tBottom left corner of square\n");               //нижний левый угол
        printf("2\tUpper triangle of square\n");                   //верхний
        printf("3\tBottom triangle of square\n");                  //нижний
        printf("4\tUpper and bottom triangle of square\n");        //верхний и нижний
        printf("5\tLeft and right triangle of square\n");          //левый и правый
        printf("6\tLeft triangle of square\n");                    //левый
        printf("7\tRight triangle of square\n");                   //правый
        printf("8\tUpper left coner of square\n");                 //верхний левый угол
        printf("9\tBottom right coner of square\n\n");             //нижний правый угол
        printf("Enter\tChenge size of sqare.(%hu)\n", size);       //задать размер фигуры
        printf("Esc\tExit\n\n");

        switch (getch())
        {
            case '0': firthtFullTriangle = Up;
                secondFullTriangle = Right;
                break;
            case '1': firthtFullTriangle = Down;
                secondFullTriangle = Left;
                break;
            case '2': firthtFullTriangle = Up;
                secondFullTriangle = None;
                break;
            case '3': firthtFullTriangle = Down;
                secondFullTriangle = None;
                break;
            case '4': firthtFullTriangle = Up;
                secondFullTriangle = Down;
                break;
            case '5': firthtFullTriangle = Right;
                secondFullTriangle = Left;
                break;
            case '6': firthtFullTriangle = Left;
                secondFullTriangle = None;
                break;
            case '7': firthtFullTriangle = Right;
                secondFullTriangle = None;
                break;
            case '8': firthtFullTriangle = Up;
                secondFullTriangle = Left;
                break;
            case '9': firthtFullTriangle = Right;
                secondFullTriangle = Down;
                break;
            case ENTER: printf("sise: ");
                scanf("%hu", &size);
                system("cls");
                continue;
            case ESC: return 0;
            default: system("cls");
                continue;
        }
        system("cls");                                              //очистка экрана

        /*"Отрисовка" закрашенных областей фигур*/
        for (char i = 0; i <= size; i++)
        {
            for (char j = 0; j <= size; j++)
            {
                if (((firthtFullTriangle == Up || secondFullTriangle == Up) && (j >= i) && (j <= size - i)) ||
                    ((firthtFullTriangle == Right || secondFullTriangle == Right) && (j >= i) && (j >= size - i)) ||
                    ((firthtFullTriangle == Down || secondFullTriangle == Down) && (j <= i) && (j >= size - i)) ||
                    ((firthtFullTriangle == Left || secondFullTriangle == Left) && (j <= i) && (j <= size - i)))
                {
                    printf("*");
                }
                else 
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\nAny key\t\tBack\n");
        printf("Esc\t\tExit\n");

        switch (getch())
        {
            case ESC: return 0;
            default:system("cls");
                break;
        }
    }
}