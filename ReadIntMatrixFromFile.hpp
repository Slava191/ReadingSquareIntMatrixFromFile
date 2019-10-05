//
//  MatrixLoadingAndProcessing.hpp
// 
//
//  Created by Вячеслав on 28.10.2018.
//  Copyright © 2018 Вячеслав. All rights reserved.
//

#ifndef ReadIntMatrixFromFile_hpp
#define ReadIntMatrixFromFile_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

enum MatrixError{
    NoError = 0,
    OpenFileError = 100,
    EmptyFileError = 200,
    ElementError= 300,
    SquareError = 400,
    MemoryAllocationError = 500
};

struct checkMatrixType{
    MatrixError typeError;
    int n = 0;
    int m = 0;
    string symbol;
};

struct Matrix{
    checkMatrixType check;
    int **ary = nullptr;
};

bool check_element(string s);
checkMatrixType check_matrix(ifstream &file);
void freeing_memory(int **ary, int n);
int** memmory_alloc(int n, int m);
int** make_main_array(int **ary, int n, int m, ifstream &file);
bool make_file_stream(ifstream &file, string file_name);
bool check_by_empty_file(ifstream &file);
void print_matrix(int **ary, int n, int m, int w);
void print_error_massage(int err_type, int n, int m, string s);
Matrix set_matrix_from_file(string file_name);


#endif /* ReadIntMatrixFromFile_hpp */
