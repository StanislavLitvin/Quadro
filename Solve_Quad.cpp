//---------------------------------------------------------------------------------------
//! @file   Solve_Quad.cpp
//! @brief  Решение квадратных и линейных уравнений с проверкой на корректность
//! @author Станислав Литвин
//! @date   26.08.2026
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//! @brief      Решает квадратное уравнение вида ax^2 + bx + c = 0
//! @param[in]  Coeffs_Eq_Addr Указатель на структуру с коеффициентами
//! @param[out] Roots_Eq_Addr Указатель на структуру с корнями и их количеством
//! @note       Если a = 0, то уравнение решается как линейное
//! @warning    Все коеффициенты должны быть корректными числами (не NAN)
//---------------------------------------------------------------------------------------
void Solve_Quad_Equation(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Addr)
{
    assert(Coeffs_Eq_Addr);
    assert(Roots_Eq_Addr);
    assert(!isnan(Coeffs_Eq_Addr->Coeff_a));
    assert(!isnan(Coeffs_Eq_Addr->Coeff_b));
    assert(!isnan(Coeffs_Eq_Addr->Coeff_c));

    if (Double_Comparison_With_Zero(Coeffs_Eq_Addr->Coeff_a))
        Solve_Linear_Equation(Coeffs_Eq_Addr, Roots_Eq_Addr);

    else
    {
        double Discriminant = Coeffs_Eq_Addr->Coeff_b * Coeffs_Eq_Addr->Coeff_b -
                              4 * Coeffs_Eq_Addr->Coeff_a * Coeffs_Eq_Addr->Coeff_c;

        if (Double_Comparison_With_Zero(Discriminant))
        {
            Roots_Eq_Addr->Root1 = (Double_Comparison_With_Zero(Coeffs_Eq_Addr->Coeff_b))
                                   ? 0 : -Coeffs_Eq_Addr->Coeff_b / (2 * Coeffs_Eq_Addr->Coeff_a);

            Roots_Eq_Addr->Number_Of_Roots = Roots_1;
        }
        else if (Discriminant < 0)
            Roots_Eq_Addr->Number_Of_Roots = Roots_0;
        else
        {
            double Sqrt_Discriminant = sqrt(Discriminant);

            Roots_Eq_Addr->Root1 = (-Coeffs_Eq_Addr->Coeff_b + Sqrt_Discriminant) /
                                   (2 * Coeffs_Eq_Addr->Coeff_a);
            Roots_Eq_Addr->Root2 = (-Coeffs_Eq_Addr->Coeff_b - Sqrt_Discriminant) /
                                   (2 * Coeffs_Eq_Addr->Coeff_a);

            Roots_Eq_Addr->Number_Of_Roots = Roots_2;
        }
    }
    return;
}

//---------------------------------------------------------------------------------------
//! @brief      Решает линейное уравнение вида bx + c = 0
//! @param[in]  Coeffs_Eq_Addr Указатель на структуру с коеффициентами
//! @param[out] Roots_Eq_Addr Указатель на структуру с корнями и их количеством
//! @note       Вызывается автоматически из Solve_Quad_Equation (при a = 0)
//! @warning    Указатели на структуры должны быть не 0
//---------------------------------------------------------------------------------------
void Solve_Linear_Equation(const struct Coeffs *Coeffs_Eq_Addr, struct Roots *Roots_Eq_Addr)
{
    assert(Coeffs_Eq_Addr);
    assert(Roots_Eq_Addr);

    if (Double_Comparison_With_Zero(Coeffs_Eq_Addr->Coeff_b))
        Roots_Eq_Addr->Number_Of_Roots = (Double_Comparison_With_Zero(Coeffs_Eq_Addr->Coeff_c))
                                         ? Roots_Inf : Roots_0;
    else
    {
        Roots_Eq_Addr->Root1 = (Double_Comparison_With_Zero(Coeffs_Eq_Addr->Coeff_c))
                               ? 0 : -Coeffs_Eq_Addr->Coeff_c / Coeffs_Eq_Addr->Coeff_b;
        Roots_Eq_Addr->Number_Of_Roots = Roots_1;
    }
    return;
}

//---------------------------------------------------------------------------------------
//! @brief     Сравнивает значение с 0 с заданной точностью
//! @param[in] Number Число (double), которое сравнивается с 0
//! @return    True, если равно 0, и False, если не равно 0
//! @warning   Число не должно быть INF
//---------------------------------------------------------------------------------------
bool Double_Comparison_With_Zero(double Number)
{
    assert(isfinite(Number));

    return (fabs(Number) < ACCURACY_CONSTANT);
}

//---------------------------------------------------------------------------------------
//! @brief  Читает и удаляет лишние символы из буфера
//! @return Количество удаленных символов (не пробелов)
//! @note   Используется после scanf
//---------------------------------------------------------------------------------------
int Clean_Buff_Count_Extra_Simbol(void)
{
    int Extra_Simbol = 0, Symbol = 0;

    Symbol = getchar();
    while (Symbol != '\n' && Symbol != EOF)
    {
        if (Symbol != ' ' && Symbol != '\t')
            Extra_Simbol++;
        Symbol = getchar();
    }
    return Extra_Simbol;
}

//---------------------------------------------------------------------------------------
//! @brief      Сортирует корни по возрастанию в структуре корней
//! @param[in]  Roots_Eq_Addr Указатель на структуру с корнями и их количеством
//! @param[out] Roots_Eq_Addr Указатель на структуру с корнями и их количеством
//! @note       Используется для сравнения посчитанных корней с эталонными
//---------------------------------------------------------------------------------------
void Sort_Roots(struct Roots *Roots_Eq_Addr)
{
    if (Roots_Eq_Addr->Root1 < Roots_Eq_Addr->Root2)
    {
        double temp = Roots_Eq_Addr->Root1;
        Roots_Eq_Addr->Root1 = Roots_Eq_Addr->Root2;
        Roots_Eq_Addr->Root2 = temp;
    }
    return;
}
