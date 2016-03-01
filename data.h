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
    double *function; // ������ �������� ������������� ������� �������
    double *fm; //������ � ���� �������� ��������� ������ ������� �����������
    double **bv; //�������� �������� �������� ���������� ������
    double **system; // ������ � ���� �������� ������������� ����� ������� �����������.
    int *sign; //������ � ���� ���� ������� ����������� �������
    int num_v;
    int num_l;
};
