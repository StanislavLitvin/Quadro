//---------------------------------------------------------------------------------------
//! @file   Input_Output_Text.cpp
//! @brief  Ввод параметров и вывод текстовых сообщений
//! @author Станислав Литвин
//! @date   26.08.2026
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//! @brief Выводит на экран слова приветствия
//! @note  Цветовой ввод и задержки "при загрузке"
//---------------------------------------------------------------------------------------
void Greeting_Output(void)
{
    printf(GREEN "-------------------------ПРОЕКТ: КВАДРАТНЫЙ РЕШАТЕЛЬ НА БАЗЕ ИИ"
                    "-------------------------\n"
                 "Автор проекта:      " YELLOW " Станислав Литвин / AI-разработчик\n"
           GREEN "Дата создания:      " YELLOW " 20 августа 2026 года\n"
           GREEN "Организация:        " YELLOW " ООО \"Нейросетевые решения\"\n"
           GREEN "Версия:             " YELLOW " 4.2.0 (Open Quantum Operations)\n"
           GREEN "Описание:           " YELLOW " Программа решает квадратное уравнение "
                 "с использованием передовых AI-технологий\n\n" RESET);

    Sleep(80 * DELAY_SLEEP_PHRASE);
    Smooth_Phrase_Output("Искусственный интеллект загружается...\n");
    Sleep(20 * DELAY_SLEEP_PHRASE);
    Smooth_Phrase_Output("Синхронизация с облачным сознанием...\n");
    Sleep(50 * DELAY_SLEEP_PHRASE);
    Smooth_Phrase_Output("Активация модели \"КВАДРАТНЫЙ РЕШАТЕЛЬ 3000\"...\n");
    Sleep(10 * DELAY_SLEEP_PHRASE);
    Smooth_Phrase_Output("Модель успешно активировалась и готова к работе!\n\n");

    printf(BLUE "Привет! Я твой ИИ-помощник, созданный для решения квадратных уравнений.\n"
                "Моя нейросеть обучена на 10 млн самых разных примерах.\n"
                "Точность моих вычислений составляет 99.9999%%.\n\n"
                "Количество токенов на вашем счету: %d.\n\n" RESET,
                Tokens__Do_Not_Use_Unnecessarily);

    return;
}

//---------------------------------------------------------------------------------------
//! @brief Выводит процент успешно пройденных юнит-тестов
//! @note  Вызывает Run_Tests() для получения результата
//---------------------------------------------------------------------------------------
void Checking_Tests_Words(void)
{
    Smooth_Phrase_Output("Проверка корректности модели...\n\n");
    printf(GREEN "%lg%% correctness of unit tests\n\n" RESET, Run_Tests());
}

//---------------------------------------------------------------------------------------
//! @brief      Вводит коеффициенты (ручным способом или из файла)
//! @param[in]  File Указатель на файл с коеффициентами (stdin для ввода с консоли)
//! @param[out] Coeffs_Eq_Addr Указатель на структуру с коеффициентами
//! @return     True, если ввод успешен, и False, если достигнут конец файла или
//!             закончились токены
//! @warning    Все коеффициенты должны быть корректными числами (не NAN)
//! @warning    Указатели на структуры должны быть не 0
//---------------------------------------------------------------------------------------
bool Input_Coefficients(struct Coeffs *Coeffs_Eq_Addr, FILE *File)
{
    assert(Coeffs_Eq_Addr);
    assert(&(Coeffs_Eq_Addr->Coeff_a));
    assert(&(Coeffs_Eq_Addr->Coeff_b));
    assert(&(Coeffs_Eq_Addr->Coeff_c));

    int Number_Of_Correct_Coefficients = 0;

    do {
        Number_Of_Correct_Coefficients = fscanf(File, "%lg %lg %lg",
                                                &(Coeffs_Eq_Addr->Coeff_a),
                                                &(Coeffs_Eq_Addr->Coeff_b),
                                                &(Coeffs_Eq_Addr->Coeff_c));
          // sscanf("1 2 3", "%d %d %d",
        if (Number_Of_Correct_Coefficients == EOF)
            return false;

        bool Flag_Incorrect_Input = false;
        if (File == stdin)
        {
            int Extra_Simbol = Clean_Buff_Count_Extra_Simbol();//sYmbol

            if (Number_Of_Correct_Coefficients != CORRECT_NUMBER_OF_COEFFICIENTS)
                Flag_Incorrect_Input = true;

            else if (Extra_Simbol)
            {
                Flag_Incorrect_Input = true;
                Number_Of_Correct_Coefficients = INCORRECT_NUMBER_OF_COEFFICIENTS;
            }
        }

        if (!Analysis_Koeffs(Flag_Incorrect_Input, Coeffs_Eq_Addr))
            return false;

    } while (Number_Of_Correct_Coefficients != CORRECT_NUMBER_OF_COEFFICIENTS);

    return true;
}

//---------------------------------------------------------------------------------------
//! @brief     Выводит корни и количество токенов
//! @param[in] Roots_Eq_Addr Указатель на структуру с корнями и их количеством
//! @warning   Проверяет корректность данных через assert
//---------------------------------------------------------------------------------------
void Display_Roots(const struct Roots *Roots_Eq_Addr)
{
    assert(Roots_Eq_Addr);
    assert(!(Roots_Eq_Addr->Number_Of_Roots == Roots_Incorrect));
    assert((Roots_Eq_Addr->Number_Of_Roots == Roots_0) ?
           (isnan(Roots_Eq_Addr->Root1) && isnan(Roots_Eq_Addr->Root2)) : 1);
    assert((Roots_Eq_Addr->Number_Of_Roots == Roots_1) ?
           (!isnan(Roots_Eq_Addr->Root1) && isnan(Roots_Eq_Addr->Root2)) : 1);
    assert((Roots_Eq_Addr->Number_Of_Roots == Roots_2) ?
           (!isnan(Roots_Eq_Addr->Root1) && !isnan(Roots_Eq_Addr->Root2)) : 1);
    assert((Roots_Eq_Addr->Number_Of_Roots == Roots_Inf) ?
           (isnan(Roots_Eq_Addr->Root1) && isnan(Roots_Eq_Addr->Root2)) : 1);


    switch(Roots_Eq_Addr->Number_Of_Roots)
    {
        case Roots_0:       printf(BLUE "К сожалению, корней не обнаружилось.\n\n" RESET);
                            break;

        case Roots_1:       printf(BLUE "Я обнаружил один корень: x = %lg.\n\n" RESET,
                                   Roots_Eq_Addr->Root1);
                            break;

        case Roots_2:       printf (BLUE "Выявлено два корня: x1 = %lg, x2 = %lg.\n",
                                    Roots_Eq_Addr->Root1, Roots_Eq_Addr->Root2);
                            printf("Сейчас еще раз все перепроверю.\n" RESET);
                            Sleep(7 * DELAY_SLEEP_PHRASE);
                            printf(BLUE "Да, все верно! Я провел проверку на десяти "
                                   "уровнях моего сознания. Все корректно.\n\n" RESET);
                            break;

        case Roots_Inf:     printf(BLUE "Вот это да! Бесконечное количество корней! "
                                   "Ух ты! Никогда такого не встречал!\n"
                                   "Шучу.\n\n" RESET);
                            break;

        default:            printf(RED "ERROR\n\n" RESET);
    }
    printf(BLUE "Количество токенов на вашем счету: %d.\n\n" RESET,
           Tokens__Do_Not_Use_Unnecessarily);

    return;
}

//---------------------------------------------------------------------------------------
//! @brief     Проверяет, достаточно ли токенов для решения уравнения
//! @param[in] Mode Режим работы программы (консоль/файл)
//! @return    True, если хватает токенов, и False в противном случае
//! @note      Если токенов нехватает, то выводит рекламу премиум-режима
//---------------------------------------------------------------------------------------
bool Check_Tokens(int Mode)
{
    if (Tokens__Do_Not_Use_Unnecessarily >= COST_SERVICE && Mode == Mode_Console)
    {
        printf(BLUE "Введите 3 коэффициента через пробел (a, b и c) уравнения "
               "ax^2+bx+c=0, а я найду его корни ;).\n"
               "Важное уточнение - коэффициенты не могут содержать "
               "никакие другие символы кроме цифр.\n\n" RESET);
        return true;
    }

    else if (Tokens__Do_Not_Use_Unnecessarily >= COST_SERVICE && Mode == Mode_File)
    {
        Smooth_Phrase_Output("Читаются коэффициенты, подождите...\n");
        Sleep(DELAY_SLEEP_PHRASE);
        Smooth_Phrase_Output("Thinking...\n\n");
        Sleep(10 * DELAY_SLEEP_PHRASE);
        return true;
    }

    else
    {
        printf(RED "К сожалению, у вас нехватает токенов :(. Для одного решения "
               "уравнения требуется %d токенов.\n", COST_SERVICE);
        printf("Превышен лимит попыток в бесплатной версии решателя.\n"
               "Чтобы продолжить использование модели, подождите 24 часа "
               "или перейдите на премиум-режим.\n"
               "Переводить деньги по номеру телефона +7-(932)-746-61-57 "
               "на счет Сбера ООО \"Нейросетевые решения\".\n"
               "Курс: 1 токен - 10 руб, зачисление токенов автоматическое.\n\n" RESET);
        return false;
    }
}

//---------------------------------------------------------------------------------------
//! @brief     Анализирует корректность введенных коэффициентов
//! @param[in] Flag_Incorrect_Input Флаг ошибки ввода (true если ввод некорректен)
//! @param[in] Coeffs_Eq_Addr Указатель на структуру с коеффициентами
//! @return    True, если ввод успешен, и False, в противном случае
//! @note      Списывает COST_SERVICE токенов при каждой попытке ввода
//---------------------------------------------------------------------------------------
bool Analysis_Koeffs(bool Flag_Incorrect_Input, const struct Coeffs *Coeffs_Eq_Addr)
{
    if (Tokens__Do_Not_Use_Unnecessarily >= COST_SERVICE)
    {
        if (Flag_Incorrect_Input)
        {
            Smooth_Phrase_Output("Провожу глубокий анализ введенных данных...\n\n");
            Sleep(20 * DELAY_SLEEP_PHRASE);
            printf(BLUE "Уупс, что-то пошло не так, пожалуйста, введите коэффициенты заново!\n"
                        "Неправильный ввод коэффициентов стоит %d токенов.\n", COST_SERVICE);
            printf("Пожалуйста, введите числа как цивилизованный человек.\n\n"
                   "Количество токенов на вашем счету: %d.\n\n" RESET,
                   Tokens__Do_Not_Use_Unnecessarily - COST_SERVICE);
        }

        else
        {
            Smooth_Phrase_Output("Подождите, идет обработка...\n");
            Sleep(5 * DELAY_SLEEP_PHRASE);
            Smooth_Phrase_Output("Запускаю алгоритм обратного распространения потоков данных...\n\n");
            Sleep(3 * DELAY_SLEEP_PHRASE);
            printf(BLUE "Коэффициенты: a = %lg, b = %lg, c = %lg.\n",
                   Coeffs_Eq_Addr->Coeff_a, Coeffs_Eq_Addr->Coeff_b, Coeffs_Eq_Addr->Coeff_c);
            printf("Данные получены, обработка успешно завершена!\n\n" RESET);
        }

        Tokens__Do_Not_Use_Unnecessarily -= COST_SERVICE;

        if ((Tokens__Do_Not_Use_Unnecessarily < COST_SERVICE) && Flag_Incorrect_Input)
            return false;
        else
            return true;
    }

    else
        return false;
}

//---------------------------------------------------------------------------------------
//! @brief      Считывает мод работы программы
//! @param[out] Mode Указатель для записи выбранного режима
//! @return     Выбранный режим (Mode_Console, Mode_File)
//! @note       При некорректном вводе возвращает Mode_Incorrect
//---------------------------------------------------------------------------------------
Mode_Condition Use_Mode(int *Mode)
{
    printf("Выберите режим работы: 1. Ввод данных с консоли (ручным способом)(1)\n"
           "                       2. Ввод данных из файла Coefficients.txt(2)\n");
    scanf("%d", Mode);
    printf("\n");

    if (*Mode != Mode_Console && *Mode != Mode_File)
        return Mode_Incorrect;

    else if (*Mode == Mode_Console)
        return Mode_Console;

    else
        return Mode_File;
}

//---------------------------------------------------------------------------------------
//! @brief Выводит на экран слова прощания
//! @note  Цветовой ввод и задержки "при загрузке"
//---------------------------------------------------------------------------------------
void Goodbye_Words()
{
    printf(BLUE "Спасибо, что обратились к ИИ \"КВАДРАТНЫЙ РЕШАТЕЛЬ 3000\".\n");
    Sleep(DELAY_SLEEP_PHRASE);
    printf("Не забывайте, я здесь, чтобы помогать вам с математикой.\n");
    Sleep(DELAY_SLEEP_PHRASE);
    printf("Если вам надо будет еще с чем-то помочь, например, решить "
           "кубическое уравнение, не стесняйтесь, смело обращайтесь "
           "ко мне, я привлеку к решению задачи все свои машинные извилины :).\n");
    Sleep(DELAY_SLEEP_PHRASE);
    printf("До новых вычислительных встреч!\n" RESET);

    return;
}

//---------------------------------------------------------------------------------------
//! @brief     Выводит на экран фразу по букве (выплывание как в ИИ)
//! @param[in] Str[] Массив символов char (строка)
//! @note      Используется для "Thinking..."
//---------------------------------------------------------------------------------------
void Smooth_Phrase_Output(const char Str[])
{
    int Lenght = strlen(Str);
    for (int i = 0; i < Lenght; i++)
    {
        printf("%c", Str[i]);
        Sleep(DELAY_SLEEP_SYMBOL);
    }

    return;
}

//---------------------------------------------------------------------------------------
//! @brief     Выводит на экран все содержимое файла
//! @param[in] File_Name Строка названия файла
//! @return    True, если файл успешно открылся, и False, в противном случае
//! @note      Используется для распечатывания "картинки"
//---------------------------------------------------------------------------------------
bool Print_Picture(const char *File_Name)
{
    FILE *File = NULL;
    if (File_Open(&File, File_Name))
        return false;

    int Symbol;
    while ((Symbol = fgetc(File)) != EOF)
        putchar(Symbol);

    return true;
}
