#include "min.h"

void Min::init()
{
    // cout << "init вызов" << endl;
    int i, j;
    func = 0;
    sv = new double *[num_l];
    for (i = 0; i < num_l; i++)
        sv[i] = new double  [num_v + num_l];
    for (i = 0; i < num_l; i++) {
        for (j = 0; j < num_v; j++)
            sv[i][j] = system[i][j];
        for (; j < ( num_v + num_l); j++)
            if (i + num_v == j)
                    sv[i][j] = 1;
            else
                sv[i][j] = 0;
    }
    istr = new double [num_v + num_l];
    bv = new double *[num_l];
    for (i = 0; i < num_l; i++) {
        bv[i] = new double [2];
        bv[i][0] = i + num_v;
        bv[i][1] = fm[i];
    }
    for (i = 0; i < num_v + num_l; i++)
        if (i < num_v)
            istr[i] = function[i] * -1;
        else
            istr[i] = 0;
    th = new double [num_l];
    alm = findalm();
    // cout << "Ведущий елемент:" << alm << " .Ведущая строка: " << i_lrow << ". Ведущий столбец: " << i_lcol << endl;
    print_result_to_file(0);
}
bool Min::plane_is_valid()
{
    int i;
    bool result = true;
        for (i = 0; i < num_v + num_l; i++)
            if (istr[i] > 0)
            {
                result = false;
                break;
            }

    return result;
}
void Min::gen_plane()
{
    // cout << "get plane вызов" << endl;
    int i, j, it_num = 0;
    double A, B;
    while (!plane_is_valid() && function_is_undefined()) {
    A = bv[i_lrow][1];
    B = istr[i_lcol];
    func -= A * B / alm;
    double *tmp_bv = new double [num_l];
    bv [i_lrow][0] = i_lcol;
    A = bv[i_lrow][1];
    for (i = 0; i < num_l; i++) {
        B = sv[i][i_lcol];
        tmp_bv[i] = bv[i_lrow][1];
        if (i != i_lrow)
            tmp_bv[i] = bv[i][1] - A * B / alm;
        else
            tmp_bv[i] /= alm;
    }
    for (i = 0; i < num_l; i++)
        bv[i][1] = tmp_bv[i];
    double *tmp_istr = istr;
    B = istr[i_lcol];
    for (i = 0; i < num_v + num_l; i++) {
        A = sv[i_lrow][i];
        tmp_istr[i] = istr[i] - A * B / alm;
    }
    istr = tmp_istr;
    double **tmp_sv = new double *[num_l];
    for (i = 0; i < num_l; i++)
        tmp_sv[i] = new double [num_v + num_l];
    for (i = 0; i < num_l; i++)
        for (j = 0; j < num_v + num_l; j++) {
            tmp_sv[i][j] = sv[i][j];
            A = sv[i_lrow][j];
            B = sv[i][i_lcol];
            if (i == i_lrow)
                tmp_sv[i][j] /= alm;
            else
                tmp_sv[i][j] = sv[i][j] - A * B / alm;
        }
         sv = tmp_sv;
        alm = findalm();
      //   cout << "Ведущий елемент:" << alm << " .Ведущая строка: " << i_lrow << ". Ведущий столбец: " << i_lcol << endl;
        it_num++;
        print_result_to_file(it_num);
    }

    if (!function_is_undefined())
            cout << "\nЦелевая фукнция не ограничена, данная задача решений не имеет\n" << endl;
    else {
        cout << "\nf(x) = " << func << "\n" << endl;
        cout << "\nВсе вычисления были записаны в файл min.txt\n" << endl;
    }
}
void Min::print_result_to_file(int it_num)
{
 //   cout << "print result to file вызов" << endl;
    int i, j;
    if (!it_num) {
    table << "Задана целевая функция:\n" << endl;
    stringstream f_x;
    f_x << "f(x) = ";
    for (i = 0; i < num_v; i++) {
        if (!i)
            f_x << function[i] << "x" << i + 1 << " ";
        else {
            if (function[i] < 0)
                f_x << "- " << fabs(function[i]) << "x" << i + 1 << " ";
            if (function[i] > 0)
                f_x << "+ " << function[i] << "x" << i + 1 << " ";
        }
    }

    f_x << "=> min \n" << endl;
    table << f_x.str();
    table << "И система ограничений:\n" << endl;
    stringstream math_sys;
    string math_sign;
    for (i = 0; i < num_l; i++) {
        for (j = 0; j < num_v; j++) {
            if (!j)
                math_sys << system[i][j] << "x" << j + 1 << " ";
            else
                if (system[i][j] == 1)
                    if (!j)
                        math_sys << "x" << j + 1 << " ";
                    else
                        math_sys << "+ x" << j + 1 << " ";
                else
                    if (system[i][j] == -1)
                    if (!j)
                        math_sys << "-x" << j + 1 << " ";
                    else
                        math_sys << "- x" << j + 1 << " ";
                    else {
                        if (system[i][j] < 0)
                            math_sys << "- " << fabs(system[i][j])<< "x" << j + 1 << " ";
                        else
                            math_sys << "+ " << system[i][j] << "x" << i + 1 << " ";
                        if (!sign[i])
                                math_sign = "<=";
                        if (sign[i] == 1)
                            math_sign = "=";
                         if (sign[i] == 2)
                            math_sign = ">=";
                }
        }

        math_sys << math_sign << " " << fm[i];
        math_sys << endl;
    }

    table << math_sys.str() << endl;
    table << "Решим данную задачу на минимум методом симплексных таблиц.\nПостроим первый опорный план:\n" << endl;
    }
    for (i = 0; i < num_l; i++) {

        table << "x" << bv[i][0] + 1 << "\t" << bv[i][1] << "\t";
        for (j = 0; j < num_v + num_l; j++)
            table << sv[i][j] << "\t";
        if (!plane_is_valid())
            table << th[i];
        table << "\n" << endl;
    }
    table << "f(x)\t" << func << "\t";
    for (i = 0; i < num_v + num_l; i++)
        table << istr[i] << "\t";
    table << "\n";
    if (plane_is_valid()) {
        if (plane_is_valid() && function_is_undefined())
            table << "\nДанный план является оптимальным и не требует улучшения. Решение найдено." << endl;
            ofstream outfile ("min.txt");
            outfile << table.str();
            cout <<  table.str();
    }
    else {
        string ln_or_gn;
            ln_or_gn = "положительные";
        stringstream num_of_plane;
        if (!it_num)
            num_of_plane << "Первый опорный план";
        else
            num_of_plane << it_num + 1 << "-й план также";
        table << "\n" << num_of_plane.str() << " не является оптимальным, поскольку\nв индексной строке присутствуют " << ln_or_gn << " элементы.\nErо необходимо улучшить.\n" << endl;
    }

}


double Min::findalm()
{
    for (int i = 0; i < num_v + num_l; i++)
       for (int j = 0; j <  num_v + num_l; j++){
            if (istr[i] < istr[j])
                i_lcol = j;
    }

    for (int i = 0; i < num_l; i++)
        th[i] = bv[i][1] / sv[i][i_lcol];
    for (int i = 0; i < num_l; i++){
        for (int j = 0;j < num_l; j++)
            if (th[j]>0){
        if (th[i] < th[j] )
            i_lrow = i;
}
       }
    return sv[i_lrow][i_lcol];
}
