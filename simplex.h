#pragma once
#include "data.h"

class Simplex : public Data
{
public:
      virtual void init()=0;
      virtual void gen_plane()=0;
      virtual bool plane_is_valid()=0;
      virtual void print_result_to_file(int it_num)=0;
      bool function_is_undefined();// �������� �� ���������������� �������
      virtual double findalm()=0; // ����� �������� ��������
protected:
    double func; //�������� �������� ������� �������.
    double **sv; // ������� ������������� ��� ���������� ������
    double *istr; //��������� ������
    double *th; // ��� �������� �� ��������������� ����������� ����������� � ��������� ������������ �������
    double alm; // �������(�����������) �������
    int i_lrow; // ������ ������� ������
    int i_lcol; //������ �������� �������
    stringstream table; // �������� �������
};

