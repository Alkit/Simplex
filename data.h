#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

void error(int err);

class Data
{
public:
    void get_data_from_user();
protected:
    double *function; // хранит значения коэффициентов целевой функции
    double *fm; //хранит в себе значения свободных членов системы ограничений
    double **bv; //Содержит значения базисных переменных задачи
    double **system; // хранит в себе значения коэффициентов самой системы ограничений.
    int *sign; //хранит в себе знак каждого ограничения системы
    int num_v;
    int num_l;
};
