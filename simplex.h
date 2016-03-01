#pragma once
#include "data.h"

class Simplex : public Data
{
public:
      virtual void init()=0;
      virtual void gen_plane()=0;
      virtual bool plane_is_valid()=0;
      virtual void print_result_to_file(int it_num)=0;
      bool function_is_undefined();// проверка на неограниченность функции
      virtual double findalm()=0; // поиск ведущего элемента
protected:
    double func; //содержит значение целевой фукнции.
    double **sv; // Матрица коэффициентов при переменных задачи
    double *istr; //индексная строка
    double *th; // для проверки на неограниченость соотношение ограничений к элементам разрешающего столбца
    double alm; // ведущий(разрешающий) элемент
    int i_lrow; // индекс ведущей строки
    int i_lcol; //индекс ведущего столбца
    stringstream table; // симплекс таблици
};

