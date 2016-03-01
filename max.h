#pragma once
#include "simplex.h"
class Max : public Simplex
{
public:
    double findalm();
    void init();
    void gen_plane();
    bool plane_is_valid();
    void print_result_to_file(int it_num);
};
