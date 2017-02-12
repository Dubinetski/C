/*Задание 1
Написать программу - калькулятор.
Реализовать 4 основные арифметические действия над 2 - мя целочисленными значениями, получаемыми от пользователя.
Арифметическое действие задается путем введения с клавиатуры символов ‘+’, ‘-’, '/', '*'.
*/

/*
Пояснения по работе программы:
Производится перехват нажатия клавиш БЕЗ вывода ее на экран.
Перехваченный символ обрабатывается. Действие зависит от того что за клавиша была нажата.
Калькулятор позволяет производить как последовательные расчеты (н-р: 3+4=7*5=35), 
так и независимые (н-р: 1+2=3   6/3=2)
Так же производится вычисление всей строки (н-р: 10-5*6/2+7=22)
Вычисления производятся в той последовательности как записаны (без учета приоритера операторов).
Поддерживаются как целые так и вещественные числа.
*/

#include <stdio.h>
#include <stdbool.h>

#define ESC '\x1b'
#define ENTER '\r'
#define BACKSPACE '\b'
#define NYL '0'
#define NINE '9'

int main()
{
    double firstOperand = 0;                                            //Первый операнд
    double secondOperand = 0;                                           //Второй операнд
    double rezult = 0;                                                  //Результат
    char pressKey;                                                      //Временная переменная для хранения char
    double number = 0;                                                  //Число из последовательно введенных цифр
    char lastAction = ENTER;                                            //Последний использовавшийся оператор (+,-,*,/,enter)
    char lastChar = NYL;                                                //Последний значимый символ (+,-,*,/,enter, . или цифра)
    bool fractionalPart = false;                                        //Признак дробной части числа
    double razrad = 0.1;                                                //Разряд, "вес" вводимой цифры в дробной части числа

    printf("Calculator\t(Press Esc to exit)\n");


    while (true)
    {
        pressKey = getch();                                             //Перехват вводимого символа БЕЗ его отображения на экране

        if ((pressKey >= NYL) && (pressKey <= NINE))                    //Если введенный символ - цифра
        {
            if ((lastChar == ENTER) || (lastChar == '='))               //Если перед вводом данного символа было произведено вычисление выражения
            {
                putchar('\n');
                firstOperand = 0;
            }
            if (!fractionalPart)                                        //Если признак дробной части числа не активен
            {
                number = number * 10 + (pressKey - NYL);                //целая часть числа
            }
            else
            {
                number += (pressKey - NYL)*razrad;                      //дробная часть числа
                razrad /= 10;
            }
        }
        else if ((pressKey == '+') || (pressKey == '-') || (pressKey == '*') || (pressKey == '/'))  //если нужный оператор
        {
            if ((lastChar >= NYL) && (lastChar <= NINE))                //и предыдущий символ - цифра
            {
                if (lastAction == ENTER)
                {
                    firstOperand = number;                              //накопленное число помечаем в качестве первого операнда
                }
                else if (lastAction != ENTER)                           //если предыдущий оператор не производил расчет
                {
                    secondOperand = number;

                    switch (lastAction)                                 //вычисляем выражение до введенного оператора
                    {
                        case '+': rezult = firstOperand + secondOperand;
                            break;
                        case '-': rezult = firstOperand - secondOperand;
                            break;
                        case '*': rezult = firstOperand * secondOperand;
                            break;
                        case '/':
                        {
                            if (secondOperand != 0)
                            {
                                rezult = firstOperand / secondOperand;
                            }
                            else
                            {
                                printf("\nDivision by zero");
                            }
                            break;
                        }
                        default: break;
                    }
                    secondOperand = 0;
                    firstOperand = rezult;
                }
                else
                {
                    secondOperand = number;
                }
                number = 0;
            }
            else if ((lastChar == '+') || (lastChar == '-') || (lastChar == '*') || (lastChar == '/')) //если пользователь решил изменить только что введенный оператор
            {
                putchar(BACKSPACE);                                     //удалить предыдущий символ на экране
            }
            else if ((lastChar == '=') || (lastChar == ENTER))          //если предыдущий символ произвел вычисление
            {
                firstOperand = rezult;
            }
            lastAction = pressKey;
            razrad = 0.1;                                               //"обнулить" позичию в дробной части для следущей вводимой цифры
            fractionalPart = false;
        }
        else if ((pressKey == ENTER) || (pressKey == '='))              //нажата Enter или =
        {
            if ((firstOperand == 0) && (lastAction == ENTER) ||         //еще не введено первое число
                (lastChar == ENTER) ||                                  //только что уже производился расчет
                ((lastAction != ENTER) && (number == 0) && (lastChar != 0)))    //после ввода +-*/ еще не введено ни одной цифры
            {
                continue;                                               //игнорируем нажатие Enter
            }
            if ((number != 0) || (lastChar == 0))                       //если на момент нажатия Enter (или =) накопленное число не нулевое или действительно был введен 0
            {
                secondOperand = number;
                number = 0;
            }
            switch (lastAction)
            {
                case '+': rezult = firstOperand + secondOperand;
                    break;
                case '-': rezult = firstOperand - secondOperand;
                    break;
                case '*': rezult = firstOperand * secondOperand;
                    break;
                case '/':
                {
                    if (secondOperand != 0)
                    {
                        rezult = firstOperand / secondOperand;
                    }
                    else
                    {
                        printf("\nDivision by zero\n");
                        rezult = 0;
                    }
                    break;
                }
                default: break;
            }
            if (!((lastAction == '/') && (rezult == 0)))
            {
                if (rezult == (int)rezult)
                {
                    printf("=\n%.f", rezult);
                }
                else
                {
                    printf("=\n%0.2f", rezult);
                }
            }
            secondOperand = 0;
            lastChar = lastAction = ENTER;
            razrad = 0.1;
            fractionalPart = false;
            continue;
        }
        else if (pressKey == '.')                                        //нажата точка - признак начала дробной части числа
        {
            fractionalPart = true;
        }
        else if (pressKey == ESC)                                        //нажата клавиша Esc - завершаем программу
        {
            return 0;
        }
        else
        {
            continue;                                                    //игнорируем все остальные символы
        }

        lastChar = pressKey;                                             //запоминаем последний значимый символ
        putchar(pressKey);                                               //выводим символ на экран
    }
}