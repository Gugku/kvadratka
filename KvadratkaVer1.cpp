#include <TXLib.h>
#include <stdio.h>
#include <math.h>



const double EPS = 1e-8;       ///< The error of double number

/*!
    *   @brief The ability to convey the number of solutions in words
    *   @param NumberTest           Number Test type int
    *   @param a                    The first  coefficient of the quadratic equation type double
    *   @param b                    The second coefficient of the quadratic equation type double
    *   @param c                    The third  coefficient of the quadratic equation type double
    *   @param x1Supposed           The first  supposed root type double
    *   @param x2Supposed           The second supposed root type double
    *   @param NumRootsSup          The quantity supposed roots type int
    *   @author LZK
*/

struct TestQuadraticSrtruct
    {
    int    NumberTest;
    double a, b, c;
    double x1Supposed, x2Supposed;
    int    NumRootsSup;
    };

 /*!
    *   @enum quadraticresult
    *   @brief The ability to convey the number of solutions in words
    *   @author LZK
*/

enum quadraticresult                                                                        /*The ability to convey the number of solutions in words*/
    {
    AllNumbers = -1,        ///< -1
    NoRoots,                ///<  0
    OneRoot,                ///<  1
    TwoRoots                ///<  2
    };

/*!
    *   @enum processresult
    *   @brief The ability to convey the process result in words
    *   @author LZK
*/

enum processresult                                                                          /*The ability to convey the process result in words*/
    {
    Success = 0,            ///<  0
    Failure                 ///<  1
    };

int SolutionOfQuadratic ( double a, double b, double c, double* x1, double* x2 );           ///< The function solving the quadratic equation
int LinearEquation ( double b, double c, double* x1 );                                      ///< The function that solves a linear equation
int SolutionQuadraticNotLinnear ( double a, double b, double c, double* x1, double* x2 );   ///< The function that solves a quadratic equation, where a != 0
int SucssefulTesting ( int TestQuadratic );                                                 ///< The function that draws conclusions from the function that runs the test
int QuadraticInput ( double* a, double* b, double* c );                                     ///< The input function
int AnswerOutput ( int SwitchReturn, double x1, double x2 );                                ///< The output function
int TestQuadratic();                                                                        ///< The function that tests a quadratic equation
int AppealToQuadratic ( TestQuadraticSrtruct DataSet );                                     ///< The function that addresses the solution of a quadratic equation
int FuncFileReader();                                                                       ///< The function that open file with test
int ScanTestFile ( FILE *DataFile, int* fscresult, int* FileTestsNumFailure );              ///< The function that scan test file
int FileTestSuccess ( FILE *DataFile );                                                     ///< The function that print file test success
int FileTestFailure ( FILE *DataFile );                                                     ///< The function that print file test failure
int CloseFile ( FILE *DataFile);                                                            ///< The function that close file
bool CheckAnswer ( TestQuadraticSrtruct DataSet, double x1, double x2, int NumRootsReal );  ///< The function that checks the test values and the resulting
bool CheckDoubleEquality ( double Num1, double Num2 );                                      ///< The function that compares numbers of the double type


    /*---------------Main-----------------------------------------------------------------*/

/*!
    * @param a      The first  coefficient of the quadratic equation
    * @param b      The second coefficient of the quadratic equation
    * @param c      The third  coefficient of the quadratic equation
    * @param x1     The root of the equation
    * @param x2     The root of the equation
    * @author LZK
    */

int main()
    {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    FuncFileReader ();

    if (SucssefulTesting ( TestQuadratic () ) == Failure)                                   /*Testing Quadratic*/
        {
        return Failure;
        }

    QuadraticInput ( &a, &b, &c );                                                          /*Input*/

    int SwitchReturn = SolutionOfQuadratic( a, b, c, &x1, &x2 );

    AnswerOutput ( SwitchReturn, x1, x2 );                                                  /*Output*/

    return Success;
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------Calculation module (a function that will find the roots)-------------*/

/*!
    * @brief        Solves a quadratic equation by dividing into linear and non-linear cases
    * @param a  [in]     The first  coefficient of the quadratic equation
    * @param b  [in]     The second coefficient of the quadratic equation
    * @param c  [in]     The third  coefficient of the quadratic equation
    * @param x1 [out]    Adress to the root of the equation
    * @param x2 [out]    Adress to the root of the equation
    * @retval LinearEquation( b, c, x1 ) If a == 0
    * @retval SolutionQuadraticNotLinnear ( a, b, c, x1, x2 ) If a != 0
    * @author LZK
    */

int SolutionOfQuadratic( double a, double b, double c, double* x1, double* x2 )
    {
    assert ( isfinite (a) );
    assert ( isfinite (b) );
    assert ( isfinite (c) );
    assert ( x1 != NULL );
    assert ( x2 != NULL );
    assert ( x1 != x2 );

    if ( CheckDoubleEquality( a, 0 ) )
        {
        return LinearEquation( b, c, x1 );
        }
    else
        {
        return SolutionQuadraticNotLinnear ( a, b, c, x1, x2 );
        }
    }

/*!
    * @brief        Linear case a = 0
    * @param b  [in]     The second coefficient of the quadratic equation
    * @param c  [in]     The third  coefficient of the quadratic equation
    * @param x1 [out]    Adress to the root of the equation
*/

int LinearEquation ( double b, double c, double* x1 )
    {

    assert ( isfinite (b) );
    assert ( isfinite (c) );
    assert ( x1 != NULL );

    if ( CheckDoubleEquality( b, 0 ) )
            {
            return ( CheckDoubleEquality( c, 0 ) )? AllNumbers : NoRoots;
            }
        else
            {
            *x1 = -c / b;
            return OneRoot;
            }
    }

/*!
    * @brief        Quadratic case a != 0
    * @param a  [in]     The first  coefficient of the quadratic equation
    * @param b  [in]     The second coefficient of the quadratic equation
    * @param c  [in]     The third  coefficient of the quadratic equation
    * @param x1 [out]    Adress to the root of the equation
    * @param x2 [out]    Adress to the root of the equation
*/

int SolutionQuadraticNotLinnear ( double a, double b, double c, double* x1, double* x2 )
    {

    assert ( isfinite (a) );
    assert ( isfinite (b) );
    assert ( isfinite (c) );
    assert ( x1 != NULL );
    assert ( x2 != NULL );
    assert ( x1 != x2 );

    double discriminant = b*b - 4*a*c;

    if ( CheckDoubleEquality( discriminant, 0 ) )
        {
        *x1 = - b / (2*a);
        return OneRoot;
        }

    else if ( discriminant < 0 )
        {
        return NoRoots;
        }
    else
        {
        double DisSqrt = sqrt(discriminant);
        *x1 = (- b + DisSqrt)/(2*a);
        *x2 = (- b - DisSqrt)/(2*a);
        return TwoRoots;
        }
    }



    /*------------------------------------------------------------------------------------*/


    /*---------------User input module----------------------------------------------------*/
int QuadraticInput ( double* a, double* b, double* c )
    {
    int SuccessfulInput = 0;
    while ( SuccessfulInput != 3 )
        {
        printf  ( "#Реши квадратное уравнение.\n");
        printf  ( "#Введите коэффиценты через запятую с дробной частью a,b,c:" );
        SuccessfulInput = scanf ("%lg,%lg,%lg", a, b, c );
        if ( SuccessfulInput != 3 )
            {
            int DelBuffer = getchar();
            while ( DelBuffer != EOF and DelBuffer != '\n' )
                {
                DelBuffer = getchar();
                }

            printf ( "\nВы ввели неверные значения, попробуйте еще раз.\n\n" );
            }
        }
    printf  ( "Вы ввели: %lg, %lg, %lg\n", *a, *b, *c );
    return Success;
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------The output module of the result--------------------------------------*/
int AnswerOutput ( int SwitchReturn, double x1, double x2 )
    {
    switch ( SwitchReturn )
        {
        case  NoRoots: printf("Нет решений\n");
                break;

        case  OneRoot: printf("x = %lg\n", x1);
                break;

        case  TwoRoots: printf("x1 = %lg, x2 = %lg\n", x1, x2);
                break;

        case  AllNumbers: printf("Решением является любое число");
                break;

        default: printf ("main(): ERROR: SwitchReturn = %d\n", SwitchReturn);
                return Failure;
        }
    return Success;
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------The program testing module-------------------------------------------*/
int TestQuadratic()
    {
    printf ( "Запущены тесты, немного подождите..\n" );
    int TestResult = 0;
    const int NumOfTests = 8;

    struct TestQuadraticSrtruct Array[NumOfTests] =
    //** NumberTest,        a,      b,      c, x1Supposed, x2Supposed, NumRootsSup **//
       {{         1,        0,      0,      0,        NAN,        NAN,  AllNumbers },
        {         2,        0,      0,      1,        NAN,        NAN,     NoRoots },
        {         3,        0,  10.01, -10.01,          1,        NAN,     OneRoot },
        {         4,      0.1,      0,   -2.5,          5,         -5,    TwoRoots },
        {         5,      0.1,      0,    2.5,        NAN,        NAN,     NoRoots },
        {         6,      5.5,    -11,    5.5,          1,        NAN,     OneRoot },
        {         7,      5.5,    1.1,    5.5,        NAN,        NAN,     NoRoots },
        {         8,      5.5,   -5.5,-20.625,        2.5,       -1.5,    TwoRoots }
       };

    for (int i = 0; i < NumOfTests; i++ )
        {
        TestResult += AppealToQuadratic( Array[i] );
        }

    if ( TestResult != 0 )
        {
        return Failure;
        }
    else
        {
        return Success;
        }
    }

int AppealToQuadratic( TestQuadraticSrtruct DataSet )
    {
    double x1 = 0, x2 = 0;
    int NumRootsReal = SolutionOfQuadratic( DataSet.a, DataSet.b, DataSet.c, &x1, &x2);
    if ( !CheckAnswer ( DataSet, x1, x2, NumRootsReal ) )
        {
        printf
            (
            "Ошибка в коде программы!\n"
            "Ошибка в тесте под номером:%d.\n"
            "a = %lg, b = %lg, c = %lg\n"
            "Ожидаемые  результаты: x1 = %lg, x2 = %lg, количество решений = %d\n"
            "Полученные результаты: x1 = %lg, x2 = %lg, количество решений = %d\n\n",
            DataSet.NumberTest, DataSet.a, DataSet.b, DataSet.c,
            DataSet.x1Supposed, DataSet.x2Supposed, DataSet.NumRootsSup, x1, x2, NumRootsReal
            );
        return Failure;
        }
    else
        {
        return Success;
        }
    }

bool CheckAnswer ( TestQuadraticSrtruct DataSet, double x1, double x2, int NumRootsReal )
    {
    if      ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == NoRoots )
        {
        return true;
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == AllNumbers )
        {
        return true;
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == OneRoot  )
        {
        return CheckDoubleEquality( x1, DataSet.x1Supposed );
        }
    else if ( NumRootsReal == DataSet.NumRootsSup and NumRootsReal == TwoRoots )
        {
        return CheckDoubleEquality( x1, DataSet.x1Supposed ) and CheckDoubleEquality( x2, DataSet.x2Supposed );
        }
    return false;
    }

int SucssefulTesting ( int TestQuadratic )
    {
    if ( TestQuadratic == 1 )
        {
        printf ( "Тесты не пройдены!\n" );
        return Failure;
        }
    else
        {
        printf ( "Тесты успешно пройдены!\n\n" );
        return Success;
        }
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------The verification module is equal to double---------------------------*/
bool CheckDoubleEquality( double Num1, double Num2 )
    {
     return fabs( Num1 - Num2) < EPS;
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------Test File Reader Module----------------------------------------------*/
int FuncFileReader ()
    {

    FILE *DataFile = NULL;
    DataFile = fopen ( "TestArray.txt", "r" );
    if ( DataFile == NULL )
        {
        perror ( "Не удалось открыть файл!\n" );
        return Failure;
        }
    else
        {
        int fscresult = 0;
        int FileTestsNumFailure = 0;
        ScanTestFile( DataFile, &fscresult, &FileTestsNumFailure );
        printf ("Успешно считанных переменных из файла: %d\n", fscresult);

        if ( FileTestsNumFailure == 0 )
            {
            return FileTestSuccess ( DataFile );
            }
        else
            {
            return FileTestFailure ( DataFile );
            }
        }

    }

int FileTestSuccess ( FILE *DataFile )
    {
    printf ( "Тест из файла успешно пройден.\n");
    return CloseFile ( DataFile );
    }

int FileTestFailure ( FILE *DataFile )
    {
    printf ( "Тест из файла провален!\n" );
    CloseFile ( DataFile );
    return Failure;
    }

int ScanTestFile ( FILE *DataFile, int* fscresult, int* FileTestsNumFailure )
    {
    struct TestQuadraticSrtruct FileStruct = {};
    int EndFile = 0;
    const int NumParamFile = 7;
    while ( (EndFile = fscanf ( DataFile, "%d,%lg,%lg,%lg,%lg,%lg,%d\n", &(FileStruct.NumberTest), &(FileStruct.a), &(FileStruct.b), &(FileStruct.c),
        &(FileStruct.x1Supposed), &(FileStruct.x2Supposed), &(FileStruct.NumRootsSup) )) != EOF )
        {
        if (EndFile != NumParamFile )
            {
            *FileTestsNumFailure += 1;
            printf ("Тест в файле имеет неверный вид!\n");
            break;
            }
        else
            {
            *FileTestsNumFailure += AppealToQuadratic( FileStruct );
            *fscresult += EndFile;
            }
        }
    return Success;
    }

    /*------------------------------------------------------------------------------------*/

    /*---------------Close File Function--------------------------------------------------*/

int CloseFile ( FILE *DataFile)
    {
    fclose ( DataFile );
    if ( DataFile != NULL )
        {
        printf ( "Файл успешно закрыт.\n\n" );
        return Success;
        }
    else
        {
        perror ( "ERROR: Файл не закрыт!\n\n" );
        return Failure;
        }
    }

    /*------------------------------------------------------------------------------------*/

