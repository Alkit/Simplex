#include <QCoreApplication>
#include "max.h"
#include "min.h"
#include "simplex.h"

void run( Simplex *pSimplex)
{
    pSimplex->get_data_from_user();
    pSimplex->init();
    pSimplex->gen_plane();
}

int main(int argc, char *argv[])
{
    bool path = true;
    bool b = false;
    string w;
    Max *max = new Max;
    Min *min = new Min;
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL,"Russian");
    cout << "\t\tДобро пожаловать в програму решения Симплекс метода\n"<< endl;

    do {
         cout << "Введите направление целевой функции ( min, max ) : ";
    getline(cin, w);
    if (w == "max" || w == "MAX" || w == "min" || w == "MIN") {
        b = true;
        if (w == "max" || w == "MAX")
        {
            cout << "Функция будет максимизирована" << endl;
            path = true;
        }
        else
        {
           path = false;
          cout << "Функция будет минимизирована" << endl;}
    }
    else
        cout << "Вы ввели неверное значение" << endl;
    } while (!b);
    if(path)
        run(max);
    else run(min);

    system("pause");
    return a.exec();
}

