//
//  main.cpp
//
//  Created by Вячеслав on 01.05.2018.
//  Copyright © 2018 Вячеслав. All rights reserved.
//


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "ReadIntMatrixFromFile.hpp"

using namespace std;

const char file_link[]="";

int** change_first_line_to_main_diagonal(int **ary, int n, int m){
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(i==j) ary[0][j] = ary[i][j];
        }
    }
    
    return ary;
}

int main(int argc, const char * argv[]) {
    
    
    ifstream file;
    string file_name;
    int **ary, n, m;
    Matrix matrix;
    
    do{
        
        cout << "Enter the file name: ";
        getline(cin, file_name);
        
        matrix = set_matrix_from_file(file_link + file_name);
        
        ary = matrix.ary;
        n = matrix.check.n;
        m = matrix.check.m;
        
        if(matrix.check.typeError!=NoError){
            print_error_massage(matrix.check.typeError, n, m, matrix.check.symbol);
            cout << "\n\nTry again. \n\n";
        }else{
            break;
        }
    
    }while(true);
    
    cout <<"\n\n"<< n << "x" << m << " BASIC MATRIX:\n\n";
    
    print_matrix(ary, n, m, 4);
    
    ary = change_first_line_to_main_diagonal(ary, n, m);

    cout <<"\n\n"<< n << "x" << m << " MATRIX AFTER CHANGE:\n\n";
    
    print_matrix(ary, n, m, 4);

    freeing_memory(ary, n);
    
    return 0;
}
