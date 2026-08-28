//---------------------------------------------------------------------------------------
//! @file   Use_Tests.cpp
//! @brief  Функции для запуска и выполнения юнит-тестов решения уравнений
//! @author Станислав Литвин
//! @date   26.08.2026
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//! @brief     Запускает один юнит-тест
//! @param[in] Coeffs_Eq_Addr Указатель на структуру с коеффициентами
//! @param[in] Roots_Eq_Ref_Addr Указатель на структуру с эталонными корнями
//! @return    True, если обработка успешна, и False в противном случае
//! @note      Вызывает Solve_Quad_Equation; с помощью Double_Comparison_With_Zero
//!            сравнивает double с 0; Sort_Roots сортирует корни по возрастанию в структуре
//!            (для удобного сравнения)
//! @warning   Указатели на структуры должны быть не 0
//---------------------------------------------------------------------------------------
bool Run_One_Test(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Ref_Addr)
{
    assert(Coeffs_Eq_Addr);
    assert(Roots_Eq_Ref_Addr);

    Roots Roots_Eq = {NAN, NAN, Roots_Incorrect};
    bool Flag_Correct_Comparison_With_Ref = true;

    Solve_Quad_Equation(Coeffs_Eq_Addr, &Roots_Eq);

    if (Roots_Eq.Number_Of_Roots != Roots_Eq_Ref_Addr->Number_Of_Roots)
        Flag_Correct_Comparison_With_Ref = false;

    else
    {
        switch(Roots_Eq.Number_Of_Roots)
        {
            case Roots_0:   if (!isnan(Roots_Eq.Root1) || !isnan(Roots_Eq.Root2))
                                Flag_Correct_Comparison_With_Ref = false;
                            break;

            case Roots_Inf: if (!isnan(Roots_Eq.Root1) || !isnan(Roots_Eq.Root2))
                                Flag_Correct_Comparison_With_Ref = false;
                            break;

            case Roots_1:   if (!Double_Comparison_With_Zero(Roots_Eq.Root1 -
                                Roots_Eq_Ref_Addr->Root1))
                                Flag_Correct_Comparison_With_Ref = false;
                            break;

            case Roots_2:   Sort_Roots(&Roots_Eq);
                            Sort_Roots(Roots_Eq_Ref_Addr);
                            if (!Double_Comparison_With_Zero(Roots_Eq.Root1 -
                                                             Roots_Eq_Ref_Addr->Root1) ||
                                !Double_Comparison_With_Zero(Roots_Eq.Root2 -
                                                             Roots_Eq_Ref_Addr->Root2))
                                Flag_Correct_Comparison_With_Ref = false;
                            break;

            default:        break;
        }
    }

    if (!Flag_Correct_Comparison_With_Ref)
        printf(RED "Test FAILED: a = %lg, b = %lg, c = %lg\n"
               "EXPECTED: %d roots, x1_Ref = %lg, x2_Ref = %lg\n"
               "GOT:      %d roots, x1     = %lg, x2     = %lg\n" RESET,
                Coeffs_Eq_Addr->Coeff_a, Coeffs_Eq_Addr->Coeff_b, Coeffs_Eq_Addr->Coeff_c,
                Roots_Eq_Ref_Addr->Number_Of_Roots, Roots_Eq_Ref_Addr->Root1,
                Roots_Eq_Ref_Addr->Root2,
                Roots_Eq.Number_Of_Roots, Roots_Eq.Root1, Roots_Eq.Root2);

    return Flag_Correct_Comparison_With_Ref;
}

//---------------------------------------------------------------------------------------
//! @brief   Запускает полный набор юнит-тестов
//! @return  Процент успешного выполнения юнит-тестов
//! @note    Данные считываются с файла "Tests.txt"
//! @note    Для каждого юнит-теста вызывается Run_One_Test
//! @warning Если файл не открылся, то функция выведет 0% выполнения тестов
//! @warning Для работы с файлом требуется файл "Tests.txt" в директории программы
//---------------------------------------------------------------------------------------
double Run_Tests(void)
{
    int Total = 0, Right = 0;

    Coeffs Coeff[MAX_NUMBER_OF_TESTS] = {};
    Roots Root[MAX_NUMBER_OF_TESTS] = {};

    FILE* File = NULL;
    if (File_Open(&File, "Tests.txt"))
        return 0.0;

    char Root1_Str[MAX_STR_LEN] = "", Root2_Str[MAX_STR_LEN] = "",
                                      Number_Of_Roots_Str[MAX_STR_LEN] = "";

    while (Total < MAX_NUMBER_OF_TESTS &&
           fscanf(File, "%lg %lg %lg %s %s %s",
                  &Coeff[Total].Coeff_a, &Coeff[Total].Coeff_b, &Coeff[Total].Coeff_c,
                  Root1_Str, Root2_Str, Number_Of_Roots_Str) == 6)
    {
        Process_Scaned_Roots_And_Number_Of_Roots(Root1_Str, Root2_Str,
                                                 Number_Of_Roots_Str, &Root[Total]);
        Total++;
    }

    File_Close(File);

    if (!Total)
    {
        printf(RED "Количество тестов равно 0\n\n" RESET);
        return 0.0;
    }

    printf(BLUE "%d тестов загружено из файла\n\n" RESET, Total);

    for (int i = 0; i < Total; i++)
    {
        if (Run_One_Test(&Coeff[i], &Root[i]))
            Right++;
    }

    return (100 * Right) / Total;
}

//---------------------------------------------------------------------------------------
//! @brief      Обрабатывает считанные строки корней уравнения и их количества
//! @param[in]  Root1_Str Строка, содержащая первый корень уравнения
//! @param[in]  Root2_Str Строка, содержащая второй корень уравнения
//! @param[in]  Number_Of_Roots_Str Строка, содержащая количество корней уравнения
//! @param[out] Roots_Eq_Addr Указатель на структуру Ref корней
//! @note       Вызывается из Run_Tests
//---------------------------------------------------------------------------------------
void Process_Scaned_Roots_And_Number_Of_Roots(const char *Root1_Str, const char *Root2_Str,
                                              const char *Number_Of_Roots_Str,
                                              struct Roots *Roots_Eq_Addr)
{
    if (!strcmp(Root1_Str, "NAN"))
        Roots_Eq_Addr->Root1 = NAN;
    else
        Roots_Eq_Addr->Root1 = atof(Root1_Str);

    if (!strcmp(Root2_Str, "NAN"))
        Roots_Eq_Addr->Root2 = NAN;
    else
        Roots_Eq_Addr->Root2 = atof(Root2_Str);

    if (!strcmp(Number_Of_Roots_Str, "INF"))
        Roots_Eq_Addr->Number_Of_Roots = Roots_Inf;
    else
        Roots_Eq_Addr->Number_Of_Roots = atoi(Number_Of_Roots_Str);

    return;
}
