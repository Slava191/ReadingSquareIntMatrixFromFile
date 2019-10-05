//
//  MatrixLoadingAndProcessing.cpp
//
//
//  Created by Вячеслав on 28.10.2018.
//  Copyright © 2018 Вячеслав. All rights reserved.
//

#include "ReadIntMatrixFromFile.hpp"

bool check_element(string s){
    
    int x;
    
    stringstream ss;
    ss = stringstream(s);
    
    ss >> x;
    
    if(ss.fail() || !ss.eof()){
        return false;
    }else{
        return true;
    }
    
}




checkMatrixType check_matrix(ifstream &file){
    
    checkMatrixType result;
    
    int k=0, m=0, n=0, previous_m=0;
    
    string s;
    string full_string;
    
    
    // Мой метод
    
    
    while(!file.eof()){
        
        
        getline(file, full_string);
        
        
        //cout << "|"<<full_string<<"|\n";
        
        stringstream ss;
        ss = stringstream(full_string);
        
        
        while(!ss.eof()){
            if(ss >> s) {
                
                
                if(!check_element(s)){
                    //file.close();
                    
                    result.typeError = ElementError;
                    result.n = n;
                    result.m = m;
                    result.symbol = s;
                    
                    return result;
                    
                }
                
                m++; //Количество элементов в строке
            }
            
        }
        
        //cout << m << "\n";
        if(m!=0){
            n++; //Количество строк
            k+=m; //Количество чисел в файле
            
            //cout << k << "\n\n";
            //cout << n << "\n\n";
            //cout << previous_m << "\n\n";
            //cout << m << "\n\n";
            if(previous_m!=0 && m!=previous_m){
                
                result.typeError = SquareError;
                
                return result;
            }
            
            /*
             if(previous_m!=0 && m!=previous_m){
             
             result.typeError = SquareError;
             
             return result;
             
             }
             */
            
            previous_m = m;
            //Обнуляем колчество строк в каждой итерации
            m = 0;
        }
        
        
    }
    
    /*
     if(n!=previous_m){
     
     result.typeError = SquareError;
     
     return result;
     }
     */
    
    
    result.typeError = NoError;
    result.n = n;
    result.m = previous_m;
    
    
    return result;
    
}


void freeing_memory(int **ary, int n){
    
    
    for (int i = 0; i < n; i++) {
        delete [] ary[i];
    }
    delete [] ary;
    
    
}

int** memmory_alloc(int n, int m){
    
    int **ary;
    
    ary = new(nothrow) int * [n];
    
    if(ary == NULL){
        return ary;
    }
    
    for (int i = 0; i < n; i++){
        ary[i] = new(nothrow) int [m];
        if(ary[i] == NULL) {
            freeing_memory(ary, i);
            return NULL;
        }
    }
    
    //В случае выполнения с ошибкой функция вернет nullptr
    return ary;
}



int** make_main_array(int **ary, int n, int m, ifstream &file)
{
    
    //file.clear();
    //file.seekg(0);
    
    //int **ary = memmory_alloc(n, m);
    
    
    if(ary!=NULL){
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                file>>ary[i][j];
            }
        }
        
    }
    
    return ary;
    
}



bool make_file_stream(ifstream &file, string file_name){
    
    file.open(file_name, ios_base::binary);
    
    if(!file.fail()) {
        return true;
    }else{
        return false;
    }
    
}

bool check_by_empty_file(ifstream &file){
    
    
    string s;
    while(!file.eof()){
        if(file>>s){
            file.clear();
            file.seekg(0);
            return false;
        }
    }
    
    return true;
    
    
    /*
     if (file.peek() == EOF) {
     
     file.close();
     return true;
     
     }else{
     return false;
     }
     */
    
}

void print_matrix(int **ary, int n, int m, int w){
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << setw(w) << ary[i][j];
        }
        cout << endl;
    }
}



void print_error_massage(int err_type, int n, int m, string s){
    
    switch(err_type)
    {
        case(ElementError):
            cerr << "Error: Incorrect element '"<< s <<"' in [" << (n+1) << ", "<< (m+1) <<"].";
            break;
        case(SquareError):
            cerr << "Error: Matrix is not square.";
            break;
        case(EmptyFileError):
            cerr << "Error: file is empty.";
            break;
        case(OpenFileError):
            cerr << "Error: opening the file error.";
            break;
        case(MemoryAllocationError):
            cerr << "Error: Memory allocation error.";
            break;
    }
    
    
    
}



Matrix set_matrix_from_file(string file_name){
    
    ifstream file;
    
    Matrix result;
    
    if(!make_file_stream(file, file_name)) {
        //Ошибка октыртия файла
        //file.close();
        result.check.typeError = OpenFileError;
        return result;
    }
    
    if(check_by_empty_file(file)){
        //Ошибка - файл пустой
        file.close();
        result.check.typeError = EmptyFileError;
        return result;
    }
    
    result.ary = nullptr;
    result.check = check_matrix(file);
    
    
    
    if(result.check.typeError!=NoError){
        
        file.close();
        return result;
        
    }
    
    int n = result.check.n;
    int m = result.check.m;
    
    
    
    
    result.ary = memmory_alloc(n, m);
    
    if(result.ary==nullptr){
        
        file.close();
        result.check.typeError = MemoryAllocationError;
        return result;
        
    }
    
    file.clear();
    file.seekg(0);
    
    make_main_array(result.ary, n, m, file);
    
    
    
    file.close();
    
    return result;
}

