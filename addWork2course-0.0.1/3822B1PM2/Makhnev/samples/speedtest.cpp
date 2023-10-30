//ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
//Copyright(c) Сысоев А.В.
//
//Тестирование матриц


#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include "tcompressedsparserow.h"
#include "tmatrix.h"
//---------------------------------------------------------------------------
using namespace std;
//template <typename T1, typename T2>
//chrono::duration<double> test(size_t size, T1(*funk1)(const T1&, const T1&), T2 (*funk2)(const T2&, const T2&) = nullptr, bool check_result = false) {
//    T2 m1(size), m2(size);
//    T1 first = m1;
//    T1 second = m2;
//    for (size_t i = 0; i < size; i++)
//    {
//        for (size_t j = 0; j < size; j++)
//        {
//            m1[i][j] = 2 * i + j;
//            m2[i][j] = 3 * i + j;
//        }
//    }
//    auto start = chrono::high_resolution_clock::now();
//    T1 result = funk1(m1, m2);
//    auto end = chrono::high_resolution_clock::now();
//    chrono::duration<double> duraion = end - start;
//    if (check_result) {
//        T2 m3 = m1 * m2;
//        T1 matrix_result(m3);
//        if (result == matrix_result) {
//            std::cout << "OK" << std::endl;
//        }
//        else
//        {
//            std::cout << "ERROR" << std::endl;
//        }
//    }
//    return duraion;
//}
template <typename T>
chrono::duration<double> test(T(*funk1)(const T&, const T&), const T& first, const T& second, T& result) {
    
    auto start = chrono::high_resolution_clock::now();
    result = funk1(first, second);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duraion = end - start;
    return duraion;
}
template <typename T>
auto multiple = [](const T& m1, const T& m2) { return m1 * m2; };

template <typename T>
auto summary = [](const T& m1, const T& m2) { return m1 + m2; };

template <typename T>
auto substraction = [](const T& m1, const T& m2) { return m1 - m2; };

template <typename T>
TDynamicMatrix<T> generator(size_t size) {
    TDynamicMatrix<T> randmatrix(size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            randmatrix[i][j] = rand();
        }
    }
    return randmatrix;
}
#define SETW_SIZE 15
void main()
{
    srand(500);
    std::cout << std::setw(SETW_SIZE) << "size" << std::setw(SETW_SIZE) << "TDynamicMatrix" << std::setw(SETW_SIZE) << "CSR" << std::endl;
    for (size_t i = 10; i < 500; i+=10)
    {
        TDynamicMatrix<int> m1 = generator<int>(i);
        TDynamicMatrix<int> m2 = generator<int>(i);
        TCompressedSparseRow<int> CSR1(m1);
        TCompressedSparseRow<int> CSR2(m2);
        TDynamicMatrix<int> m3;
        TCompressedSparseRow<int> CSR3;
        std::cout  << std::setw(SETW_SIZE) << i 
            << std::setw(SETW_SIZE) << test<TDynamicMatrix<int>>(multiple<TDynamicMatrix<int>>, m1, m2, m3).count()
            << std::setw(SETW_SIZE) << test<TCompressedSparseRow<int>>(multiple<TCompressedSparseRow<int>>, CSR1, CSR2, CSR3).count()
            << std::endl;
    }

    

  //TDynamicMatrix<int> a(5), b(5), c(5);
  //int i, j;

  //setlocale(LC_ALL, "Russian");
  //cout << "Тестирование класс работы с матрицами"
  //  << endl;
  //for (i = 0; i < 5; i++)
  //  for (j = 0; j < 5; j++ )
  //  {
  //    a[i][j] =  i * 10 + j;
  //    b[i][j] = (i * 10 + j) * 100;
  //  }
  //c = a + b;
  //cout << "Matrix a = " << endl << a << endl;
  //cout << "Matrix b = " << endl << b << endl;
  //cout << "Matrix c = a + b" << endl << c << endl;
}
//---------------------------------------------------------------------------
