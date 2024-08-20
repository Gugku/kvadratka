#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int ALLNUMBERS = -1;                                                                  /*Глобальная переменная*/

int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2);             /*Обьявление функции, решающей квадратное уравнение*/

int main(void)
    {
    /*-----------------------Модуль ввода данных------------------------------------------*/
        double a = 0, b=0, c=0;                                                             /*Вводим три переменных, которые являются коэффицентами квадратного уравнения*/
        int SuccessfulInput = 0;
        while (SuccessfulInput == 0)                                                        /*Считываем, что вводит пользователь*/
            {
            printf  ("#Реши квадратное уравнение.\n");                                      /*Описание нашей программы*/
            printf  ("#Введите коэффиценты через запятую с дробной частью a,b,c:");         /*Обращение к пользователю*/
            SuccessfulInput = scanf   ("%lg,%lg,%lg", &a, &b, &c);
            }
        printf  ("Вы ввели: %f, %f, %f\n", a, b, c);                                        /*Выводим числа введеные пользователем*/
        double x1=0, x2=0;                                                                  /*Вводим переменные, в которые будут записываться корни*/
    /*------------------------------------------------------------------------------------*/


    /*-----------------------Модуль запроса на вывод результата---------------------------*/
        int SwitchReturn = SolutionOfQuadratic( a, b, c, &x1, &x2);
    /*------------------------------------------------------------------------------------*/



    /*-----------------------Модуль вывода результата-------------------------------------*/
        switch (SwitchReturn)
        {
            case 0: printf("Нет решений\n");
                    break;

            case 1: printf("x = %lg\n", x1);
                    break;

            case 2: printf("x1 = %lg, x2 = %lg\n", x1, x2);
                    break;

            case ALLNUMBERS: printf("Решением является любое число");
                        break;

            default: printf ("main(): ERROR: SwitchReturn = %d\n", SwitchReturn);
                     return 1;
        }
    /*------------------------------------------------------------------------------------*/

    }

    /*-----------------------Модуль вычисления(функция, которая будет находить корни)---- */
int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2)
    {

    if (a == 0)
        {
        if (b == 0)
            {
            return (c == 0)? ALLNUMBERS : 0;
            }
        else
            {
            *x1 = -c / b;
            return 1;
            }
    }
    else
        {
        if (b == 0)
            {
            *x1 =   sqrt(c/a);
            *x2 = - sqrt(c/a);
            return 2;
            }
        else
            {
            double discriminant = b*b - 4*a*c;

            if (discriminant < 0)
                {
                return 0;
                            }
            if (discriminant == 0)
                {
                *x1 = (- b + sqrt(discriminant))/(2*a);
                return 1;
                }
            if (discriminant > 0)
                {
                *x1 = (- b + sqrt(discriminant))/(2*a);
                *x2 = (- b - sqrt(discriminant))/(2*a);
                return 2;
                }
            }
        }
    }
    /*------------------------------------------------------------------------------------*/
