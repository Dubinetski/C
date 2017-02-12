/*
Задание 3
Пользователь вводит число.
Определить количество цифр в этом числе, посчитать их сумму и среднее арифметическое.
Определить количество нулей в этом числе. Общение с пользователем организовать через меню.
*/


#include <stdio.h>
#include <stdbool.h>

#define ESC '\x1b'
#define ENTER '\r'

int main()
{
    long long int number;                                       //число
    unsigned short countCipherOfNumber;                         //число цифр в числе
    unsigned int summOfCipherOfNumber;                          //сумма цифр числа
    unsigned int arithmeticMiddlingCiphersOfNumber;             //среднее арифметическое цифр числа
    unsigned short countOfZeroInNumber;                         //число нулей в числе
    char cipher;                                                //цифра
    char positionMenu;                                          //выбранная позиция меню
    bool menuVisible;                                           //признак отображения меню

    while (true)
    {
        countCipherOfNumber = 0;
        summOfCipherOfNumber = 0;
        arithmeticMiddlingCiphersOfNumber = 0;
        countOfZeroInNumber = 0;

        /*Ввод числа*/
        printf("Please enter the number: ");
        while (scanf("%lli", &number) != 1)
        {
            printf("Incorrect number. Pleasee enter the positive integer number.\n\n");
            while (getchar() != '\n') {}
        }
        printf("\n");

        /*Проведение вычислений*/
        long long int tempNumber = number;                      //временная переменная для работы с введенным числом
        while (tempNumber != 0)                                 
        {
            cipher = tempNumber % 10;                           //выделяем последнюю цифру числа
            countCipherOfNumber++;                              //увеличиваем счетчик цифр в числе на 1
            summOfCipherOfNumber += cipher;                     //увеличиваем сумму цифр числа на только что выделенную последнюю цифру
            if (cipher == 0)
            {
                countOfZeroInNumber++;                          
            }
            tempNumber /= 10;                                   //отбрасываем последнюю цифру от числа
        }
        arithmeticMiddlingCiphersOfNumber = summOfCipherOfNumber / countCipherOfNumber;

        menuVisible = true;

        /*Организация меню*/
        while (menuVisible)
        {
            printf("\n1\tCount cipher in number\n");
            printf("2\tCount zero in number\n");
            printf("3\tSumm ciphers of number\n");
            printf("4\tArithmetic middling of cipher of number\n\n");
            printf("Enter\tEnother number\n");
            printf("Esc\tExit\n");

            positionMenu = getch();

            system("cls");                                      //Очистка экрана
            printf("Number:\t%lli\n", number);                  //Обновление отображения числа на экране

            switch (positionMenu)
            {
                case '1': printf("Count cipher in number: %hu\n", countCipherOfNumber);
                    break;
                case '2':printf("Count zero in number: %hu\n", countOfZeroInNumber);
                    break;
                case '3':printf("Summ ciphers of number: %hu\n", summOfCipherOfNumber);
                    break;
                case '4':printf("Arithmetic middling of cipher of number: %hu\n", arithmeticMiddlingCiphersOfNumber);
                    break;
                case ENTER: menuVisible = false;                    //используется для выхода из цикла т.к. break выходит из swich, а не из цикла 
                    system("cls");
                    break;
                case ESC :return 0;                              //завершение программы если нажата Esc
                    break;
                default:
                    break;
            }
        }
    }
}