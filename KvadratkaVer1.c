#include <TXLib.h>
#include <stdio.h>
#include <math.h>

const int ALLNUMBERS = -1;                                                                  /*���������� ����������*/
const double EPS = 1e-8;                                                                    /*������� �����������*/

int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2 );            /*���������� �������, �������� ���������� ���������*/
int QuadraticInput ( double* a, double* b, double* c );                                     /*���������� ������� �����*/
int AnswerOutput ( int SwitchReturn, double x1, double x2 );                                      /*���������� ������� ������*/

int main()
    {
    /*-----------------------������ ����� ������------------------------------------------*/
    double a = 0, b = 0, c = 0;
    QuadraticInput ( &a, &b, &c);
    double x1=0, x2=0;
    /*------------------------------------------------------------------------------------*/

    /*-----------------------������ ������� �� ����� ����������---------------------------*/
    int SwitchReturn = SolutionOfQuadratic( a, b, c, &x1, &x2);
    AnswerOutput ( SwitchReturn, x1, x2 );
    /*------------------------------------------------------------------------------------*/
    return 0;
    }


    /*-----------------------������ ����������(�������, ������� ����� �������� �����)---- */
int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2 )
    {
    assert ( isfinite (a) );
    assert ( isfinite (b) );
    assert ( isfinite (c) );
    assert ( x1 != NULL );
    assert ( x2 != NULL );
    assert ( x1 != x2 );

    if ( fabs(a) < EPS )
        {
        if ( fabs(b) < EPS )
            {
            return ( fabs(c) < EPS )? ALLNUMBERS : 0;
            }
        else
            {
            *x1 = -c / b;
            return 1;
            }
    }
    else
        {
        if ( fabs(b) < EPS )
            {
            *x1 =   sqrt(c/a);
            *x2 = - sqrt(c/a);
            return 2;
            }
        else
            {
            double discriminant = b*b - 4*a*c;

            if ( fabs(discriminant) < EPS )
                {
                *x1 = (- b + sqrt(discriminant))/(2*a);
                return 1;
                }

            if (discriminant < 0)
                {
                return 0;
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


    /*-------------------------������ ����� �������������---------------------------------*/
int QuadraticInput ( double* a, double* b, double* c )
    {
    int SuccessfulInput = 0;
    while (SuccessfulInput != 3)
            {
            printf  ("#���� ���������� ���������.\n");
            printf  ("#������� ����������� ����� ������� � ������� ������ a,b,c:");
            SuccessfulInput = scanf ("%lg,%lg,%lg", a, b, c);
            if (SuccessfulInput != 3)
                {
                int DelBuffer = getchar();
                while (DelBuffer != EOF and DelBuffer != '\n')
                    {
                    DelBuffer = getchar();
                    }

                printf ("\n#�� ����� �������� ��������, ���������� ��� ���.\n\n");
                }
            }
    printf  ("�� �����: %lg, %lg, %lg\n", *a, *b, *c);
    return 0;
    }
    /*------------------------------------------------------------------------------------*/

     /*-----------------------������ ������ ����������-------------------------------------*/
int AnswerOutput ( int SwitchReturn, double x1, double x2 )
    {
    switch (SwitchReturn)
        {
        case 0: printf("��� �������\n");
                break;

        case 1: printf("x = %lg\n", x1);
                break;

        case 2: printf("x1 = %lg, x2 = %lg\n", x1, x2);
                break;

        case ALLNUMBERS: printf("�������� �������� ����� �����");
                break;

        default: printf ("main(): ERROR: SwitchReturn = %d\n", SwitchReturn);
                return 1;
        }
    return 0;
    }
    /*------------------------------------------------------------------------------------*/
