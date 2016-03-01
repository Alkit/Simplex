#include "data.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>


using namespace std;

void Data::get_data_from_user()
{
    string num_limits, num_vars, s_var, fr_m, sn, func, w;
    int i, j;
    bool validator = false;


    do {
        cout << "Введите количество ограничений в системе: ";
        getline(cin, num_limits);
        if (atoi(num_limits.c_str()) < 2)
            error(1);
        else if (atoi(num_limits.c_str()) > 500)
            error(2);
        else
            validator = true;

    } while (!validator);

    num_l = atoi(num_limits.c_str());
    validator = false;

    do {
        cout << "Введите количество переменных в системе ограничений: ";
        getline(cin, num_vars);
    if (atoi(num_vars.c_str()) < 2)
        error(3);
    else if (atoi (num_vars.c_str()) > 500)
        error(4);
    else
        validator = true;
    } while (!validator);

    num_v = atoi(num_vars.c_str());
    validator = false;

    function = new double [num_v];
    system = new double *[num_l];
    for (i = 0; i < num_l; i++)
        system[i] = new double [num_v];
    fm = new double [num_l];
    sign = new int [num_l];

    cout << "\nЗаполните коэффициенты при целевой функции.\n" << endl;

    for (i = 0; i < num_v; i++) {
        do {
            cout << "Введите коэффициент целевой фукнции при x" << i + 1 << ": ";
            getline(cin, func);

                validator = true;
                function[i] = atof(func.c_str());

        } while (!validator);
        validator = false;
    }

    cout << "\nЗаполните систему ограничений.\n" << endl;

    for (i = 0; i < num_l; i++) {
        cout << "Заполните " << i + 1 << "-е ограничение.\n" << endl;
        for (j = 0; j < num_v; j++) {
            do {
                cout << "Введите коэффициэнт при x" << j + 1 << ": ";
                getline(cin, s_var);
                if (atof(s_var.c_str()) == 0)

                 validator = true;
                else {
                    validator = true;
                }
            } while (!validator);
            system[i][j] = atof(s_var.c_str());
            validator = false;
        }

        do {
            cout << "Введите знак при " << i + 1 << "-м ограничении ( <=, =, >= ) : ";
            getline(cin, sn);
            if (sn == "<=" || sn == "=" || sn == ">=") {
                validator = true;
                if (sn == "<=")
                    sign[i] = 0;
                if (sn == "=")
                    sign[i] = 1;
                if (sn == ">=")
                    sign[i] = 2;
                }
            else
                error(0);
            cout << sign[i] << endl;
        } while (!validator);

        validator = false;

        do {
            cout << "Введите свободный член при " << i + 1 << "-м ограничении: ";
            getline(cin, fr_m);
                validator = true;
        } while (!validator);

        fm[i] = atof(fr_m.c_str());
        validator = false;

        cout << endl;
    }

}

void error(int err)
{
    switch(err) {
        case 0:
            cout << "\nНекоректние даные.Повторите ввод." << endl;
            break;
        case 1:
            cout << "\nВы не можете задать менее двух ограничений." << endl;
            break;
        case 2:
            cout << "\nВы не можете задать больше 500 ограничений." << endl;
            break;
        case 3:
            cout << "\nВы не можете задать менее двух переменных." << endl;
            break;
        case 4:
            cout << "\nВы не можете задать более 500 уравнений." << endl;
            break;
        case 5:
            cout << "\n Не корректный ввод. Пiдеш на осiнь! " << endl;
    }
}
