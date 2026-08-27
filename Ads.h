//---------------------------------------------------------------------------------------
//! @file   Ads.h
//! @brief  Заголовочный файл с #include, #define, enum и struct
//! @author Станислав Литвин
//! @date   26.08.2026
//---------------------------------------------------------------------------------------

#include "Config.h"

//---------------------------------------------------------------------------------------
//! @brief   Количество токенов на счету
//! @warning Это глобальная переменная! Использовать очень осторожно!
//---------------------------------------------------------------------------------------
int Tokens__Do_Not_Use_Unnecessarily = 1000;

//---------------------------------------------------------------------------------------
//! @brief Константы (по названию понятно что обозначают)
//---------------------------------------------------------------------------------------
const int INCORRECT_NUMBER_OF_COEFFICIENTS  = -1;
const int CORRECT_NUMBER_OF_COEFFICIENTS    = 3;
const double ACCURACY_CONSTANT              = 1e-5;
const int DELAY_SLEEP                       = 50;
const int NUMBER_OF_TESTS                   = 12;

//---------------------------------------------------------------------------------------
//! @brief Функции, непосредственно решающие уравнение
//---------------------------------------------------------------------------------------
void Solve_Quad_Equation(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Addr);
void Solve_Linear_Equation(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Addr);
bool Double_Comparison_With_Zero(double Number);
int Clean_Buff_Count_Extra_Simbol(void);
void Sort_Roots(struct Roots *Roots_Eq_Addr);

//---------------------------------------------------------------------------------------
//! @brief Функции, отвечающие за считывание, вывод на экран и работу с текстом
//---------------------------------------------------------------------------------------
void Greeting_Output(void);
void Checking_Tests_Words(void);
bool Input_Coefficients(struct Coeffs *Coeffs_Eq_Addr, FILE *File);
void Display_Roots(const struct Roots *Roots_Eq_Addr);
bool Check_Tokens(int Mode);
bool Analysis_Koeffs(bool Flag, const struct Coeffs *Coeffs_Eq_Addr);
Mode_Condition Use_Mode(int *Mode);
void Goodbye_Words(void);
void Smooth_Phrase_Output(const char Str[]);

//---------------------------------------------------------------------------------------
//! @brief Функции, отвечающие за работу с файлом
//---------------------------------------------------------------------------------------
bool File_Open(FILE **File);
bool File_Close(FILE *File);

//---------------------------------------------------------------------------------------
//! @brief Функции, отвечающие за работу со встроенными тестами
//---------------------------------------------------------------------------------------
bool Run_One_Test(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Ref_Addr);
double Run_Tests(void);
