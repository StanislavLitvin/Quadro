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
    bool Flag = true;

    Solve_Quad_Equation(Coeffs_Eq_Addr, &Roots_Eq);

    if (Roots_Eq.Number_Of_Roots != Roots_Eq_Ref_Addr->Number_Of_Roots)
        Flag = false;

    else
    {
        switch(Roots_Eq.Number_Of_Roots)
        {
            case Roots_0:   if (!isnan(Roots_Eq.Root1) || !isnan(Roots_Eq.Root2))
                                Flag = false;
                            break;

            case Roots_Inf: if (!isnan(Roots_Eq.Root1) || !isnan(Roots_Eq.Root2))
                                Flag = false;
                            break;

            case Roots_1:   if (!Double_Comparison_With_Zero(Roots_Eq.Root1 -
                                Roots_Eq_Ref_Addr->Root1))
                                Flag = false;
                            break;

            case Roots_2:   Sort_Roots(&Roots_Eq);
                            Sort_Roots(Roots_Eq_Ref_Addr);
                            if (!Double_Comparison_With_Zero(Roots_Eq.Root1 -
                                                             Roots_Eq_Ref_Addr->Root1) ||
                                !Double_Comparison_With_Zero(Roots_Eq.Root2 -
                                                             Roots_Eq_Ref_Addr->Root2))
                                Flag = false;
                            break;

            default:        break;
        }
    }

    if (!Flag)
        printf(RED "Test FAILED: a = %lg, b = %lg, c = %lg\n"
               "EXPECTED: %d roots, x1_Ref = %lg, x2_Ref = %lg\n"
               "GOT:      %d roots, x1     = %lg, x2     = %lg\n" RESET,
                Coeffs_Eq_Addr->Coeff_a, Coeffs_Eq_Addr->Coeff_b, Coeffs_Eq_Addr->Coeff_c,
                Roots_Eq_Ref_Addr->Number_Of_Roots, Roots_Eq_Ref_Addr->Root1,
                Roots_Eq_Ref_Addr->Root2,
                Roots_Eq.Number_Of_Roots, Roots_Eq.Root1, Roots_Eq.Root2);

    return Flag;
}

//---------------------------------------------------------------------------------------
//! @brief   Запускает полный набор юнит-тестов
//! @return  Процент успешного выполнения юнит-тестов
//! @note    Содержит 12 тестовых случаев, которые покрывют все случаи выполнения программы
//! @note    Для каждого юнит-теста вызывается Run_One_Test
//! @warning Если тестов 0 штук, то произойдет деление на 0 (ERROR)
//---------------------------------------------------------------------------------------
double Run_Tests(void)
{
    int i = 0, Right = 0;

    Coeffs Coeff[NUMBER_OF_TESTS] = { {0,  0,   0},
                                      {0,  0,  10},
                                      {0,  5,   0},
                                      {0,  5,  10},
                                      {1,  0,   0},
                                      {1,  0, -25},
                                      {1,  5,   0},
                                      {1, -5,   6},
                                      {1,  2,   1},
                                      {4,  1,   5},
                                      {1,  4,   4},
                                      {1,  5,   6} };

    Roots Root[NUMBER_OF_TESTS] = { {NAN, NAN, Roots_Inf},
                                    {NAN, NAN, Roots_0},
                                    {  0, NAN, Roots_1},
                                    { -2, NAN, Roots_1},
                                    {  0, NAN, Roots_1},
                                    { -5,   5, Roots_2},
                                    { -5,   0, Roots_2},
                                    {  2,   3, Roots_2},
                                    { -1, NAN, Roots_1},
                                    {NAN, NAN, Roots_0},
                                    { -2, NAN, Roots_1},
                                    { -2,  -3, Roots_2} };

    for (; i < NUMBER_OF_TESTS; i++)
    {
        if (Run_One_Test(&Coeff[i], &Root[i]))
            Right++;
    }

    return (100 * Right) / i;
}
