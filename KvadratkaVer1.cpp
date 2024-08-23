#include <TXLib.h>
#include <stdio.h>
#include <math.h>

const int ALLNUMBERS = -1;                                                                  /*���������� ����������*/
const double EPS = 1e-8;                                                                    /*������� �����������*/
struct TestQuadraticSrtruct
    {
    int    NumberTest;
    double a, b, c;
    double x1Supposed, x2Supposed;
    int    NumRootsSup;
    };

int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2 );            /*���������� �������, �������� ���������� ���������*/
int QuadraticInput ( double* a, double* b, double* c );                                     /*���������� ������� �����*/
int AnswerOutput ( int SwitchReturn, double x1, double x2 );                                /*���������� ������� ������*/
int TestQuadratic();
int AppealToQuadratic( TestQuadraticSrtruct DataSet );                                                                       /*���������� �������, ������� ��������� ���������*/
bool CheckAnswer ( TestQuadraticSrtruct DataSet, double x1, double x2, int NumRootsReal );
bool CheckDoubleEquality( double Num1, double Num2 );

int main()
    {
    /*-----------------------������ ����� ������------------------------------------------*/
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    TestQuadratic();
    QuadraticInput ( &a, &b, &c );
    /*------------------------------------------------------------------------------------*/

    /*-----------------------������ ������� �� ����� ����������---------------------------*/
    int SwitchReturn = SolutionOfQuadratic( a, b, c, &x1, &x2 );
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
    *x1 = NAN;
    *x2 = NAN;

    if ( CheckDoubleEquality( a, 0 ) )
        {
        if ( CheckDoubleEquality( b, 0 ) )
            {
            return ( CheckDoubleEquality( c, 0 ) )? ALLNUMBERS : 0;
            }
        else
            {
            *x1 = -c / b;
            return 1;
            }
    }
    else
        {
        if ( CheckDoubleEquality( b, 0 ) and (-c/a) >= 0 )
            {
            *x1 =   sqrt(-c/a);
            *x2 = - sqrt(-c/a);
            return 2;
            }
        if ( CheckDoubleEquality( b, 0 ) and (c/a) < 0 )
            {
            return 0;
            }
        else
            {
            double discriminant = b*b - 4*a*c;

            if ( CheckDoubleEquality( discriminant, 0 ) )
                {
                *x1 = (- b + sqrt(discriminant))/(2*a);
                return 1;
                }

            else if ( discriminant < 0 )
                {
                return 0;
                }
            else
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
    while ( SuccessfulInput != 3 )
        {
        printf  ( "#���� ���������� ���������.\n");
        printf  ( "#������� ����������� ����� ������� � ������� ������ a,b,c:" );
        SuccessfulInput = scanf ("%lg,%lg,%lg", a, b, c );
        if ( SuccessfulInput != 3 )
            {
            int DelBuffer = getchar();
            while ( DelBuffer != EOF and DelBuffer != '\n' )
                {
                DelBuffer = getchar();
                }

            printf ( "\n#�� ����� �������� ��������, ���������� ��� ���.\n\n" );
            }
        }
    printf  ( "�� �����: %lg, %lg, %lg\n", *a, *b, *c );
    return 0;
    }
    /*------------------------------------------------------------------------------------*/

    /*-----------------------������ ������ ����������-------------------------------------*/
int AnswerOutput ( int SwitchReturn, double x1, double x2 )
    {
    switch ( SwitchReturn )
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

    /*-----------------------������ ������������ ���������--------------------------------*/
int TestQuadratic()
    {
    int TestResult = 0;
    TestQuadraticSrtruct Test1 = { 1, 0, 0, 0, NAN, NAN, ALLNUMBERS };
    TestResult += AppealToQuadratic( Test1 );

    TestQuadraticSrtruct Test2 = { 2, 0, 0, 1, NAN, NAN, 0 };
    TestResult += AppealToQuadratic( Test2 );

    TestQuadraticSrtruct Test3 = { 3, 0, 10.01, -10.01, 1, NAN, 1 };
    TestResult += AppealToQuadratic( Test3 );

    TestQuadraticSrtruct Test4 = { 4, 0.1, 0, -2.5, 5, -5, 2 };
    TestResult += AppealToQuadratic( Test4 );

    TestQuadraticSrtruct Test5 = { 5, 0.1, 0, 2.5, NAN, NAN, 0 };
    TestResult += AppealToQuadratic( Test5 );

    TestQuadraticSrtruct Test6 = { 6, 5.5, -11, 5.5, 1, NAN, 1 };
    TestResult += AppealToQuadratic( Test6 );

    TestQuadraticSrtruct Test7 = { 7, 5.5, 1.1, 5.5, NAN, NAN, 0 };
    TestResult += AppealToQuadratic( Test7 );

    TestQuadraticSrtruct Test8 = { 8, 5.5, -5.5, -20.625, 2.5, -1.5, 2 };
    TestResult += AppealToQuadratic( Test8 );

    assert ( TestResult == 0 );
    return 0;
    }

int AppealToQuadratic( TestQuadraticSrtruct DataSet )
    {
    double x1 = 0, x2 = 0;
    int NumRootsReal = SolutionOfQuadratic( DataSet.a, DataSet.b, DataSet.c, &x1, &x2);
    if ( !CheckAnswer ( DataSet, x1, x2, NumRootsReal ) )
        {
        printf
            (
            "������ � ���� ���������!\n"
            "������ � ����� ��� �������:%d.\n"
            "a = %lg, b = %lg, c = %lg\n"
            "���������  ����������: x1 = %lg, x2 = %lg, ���������� ������� = %d\n"
            "���������� ����������: x1 = %lg, x2 = %lg, ���������� ������� = %d\n\n",
            DataSet.NumberTest, DataSet.a, DataSet.b, DataSet.c,
            DataSet.x1Supposed, DataSet.x2Supposed, DataSet.NumRootsSup, x1, x2, NumRootsReal
            );
        return 1;
        }
    else
        {
        return 0;
        }
    }
bool CheckAnswer ( TestQuadraticSrtruct DataSet, double x1, double x2, int NumRootsReal )
    {
    if (   NumRootsReal == DataSet.NumRootsSup and NumRootsReal == 0 )
        {
        return true;
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == ALLNUMBERS )
        {
        return true;
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == 1 )
        {
        return CheckDoubleEquality( x1, DataSet.x1Supposed );
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == 2 )
        {
        return CheckDoubleEquality( x1, DataSet.x1Supposed ) and CheckDoubleEquality( x2, DataSet.x2Supposed );
        }
    return false;
    }

    /*------------------------------------------------------------------------------------*/

    /*-----------------------������ �������� �������� double------------------------------*/
bool CheckDoubleEquality( double Num1, double Num2 )
    {
     return fabs( Num1 - Num2) < EPS;
    }

    /*------------------------------------------------------------------------------------*/
