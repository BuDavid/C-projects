#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <utility>

class Matrix {
public:
    Matrix() = default;
    Matrix(int row, int col);
    Matrix(int size);
    Matrix(const std::vector<std::vector<double>>& matrix);
public:
    void fill(double x = 0.f);
    void fill_random(int seed = 0);
    void augmant(const std::vector<double>& vec);
    void show_matrix() const; 
    void clear(); 
    Matrix transpose() const;
    Matrix solve_system() const;
    Matrix get_inverse() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& matrix);
private:
    Matrix solve(bool is_augmanted, bool is_inverted) const;
    std::vector<double> sub_vec(const std::vector<double>& vec1, const std::vector<double>& vec2) const;
    std::vector<double> mul_row(double row, const double value) const;
    std::vector<double> div_row(double row, const double value) const;
private:
    int m_row;
    int m_col;
    std::vector<std::vector<double>> m_matrix;
    std::vector<double> m_augmanted;
};

#endif  // MATRIX_H_
