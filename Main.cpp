//---------------------------------------------------------------------------------------
//! @file   Main.cpp
//! @brief  Главный модуль программы решения квадратного уравнения
//! @author Станислав Литвин
//! @date   26.08.2026
//---------------------------------------------------------------------------------------

#include "Ads.h"
#include "Solve_Quad.cpp"
#include "Input_Output_Text.cpp"
#include "Use_File.cpp"
#include "Use_Tests.cpp"

//---------------------------------------------------------------------------------------
//! @brief   Главная функция программы
//! @return  Код завершения программы:
//!          - Not_Error            - при успешном выполнении программы
//!          - Error_Incorrect_Mode - при вводе некорректного режима работы
//!          - Error_File_Open      - при неудачном открытии файла
//!          - Error_File_Close     - при неудачном закрытии файла
//! @note    Программа использует токены, как валюту для имитации ИИ
//! @warning Для работы с файлом требуется файл "Coefficients.txt" в директории программы
//---------------------------------------------------------------------------------------
int main()
{
    Greeting_Output();

    Checking_Tests_Words();

    int Mode = Use_Mode(&Mode);
    if (Mode == Mode_Incorrect)
    {
        printf(RED "ERROR, введите корректный режим работы\n" RESET);
        return Error_Incorrect_Mode;
    }

    FILE* File = NULL;

    if (Mode == Mode_Console)
        File = stdin;

    else if (Mode == Mode_File && File_Open(&File))
    {
        printf(RED "ERROR, не удалось открыть файл\n" RESET);
        return Error_File_Open;
    }

    bool End_Of_File = false;

    while (Check_Tokens(Mode))
    {
        Coeffs Coeffs_Eq = {NAN, NAN, NAN};
        Roots Roots_Eq = {NAN, NAN, Roots_Incorrect};

        if (!Input_Coefficients(&Coeffs_Eq, File))
        {
            End_Of_File = true;
            break;
        }

        Solve_Quad_Equation(&Coeffs_Eq, &Roots_Eq);

        Display_Roots(&Roots_Eq);
    }

    if (End_Of_File && (Mode == Mode_File))
        printf(BLUE "Достигнут конец файла. Все коеффициенты прочитаны.\n\n" RESET);

    if (Mode == Mode_File && File_Close(File))
    {
        printf(RED "ERROR, не удалось закрыть файл\n" RESET);
        return Error_File_Close;
    }

    Goodbye_Words();

    return Not_Error;
}
