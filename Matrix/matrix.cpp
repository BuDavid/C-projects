#include "matrix.hpp"

Matrix::Matrix(int row, int col) : m_matrix(row, std::vector<double>(col, 0.f)), m_row(row), m_col(col) {}

Matrix::Matrix(int size) : m_matrix(size, std::vector<double>(size, 0.f)), m_row(size), m_col(size) {
    for (int i = 0; i < size; i++) {
        m_matrix[i][i] = 1.0;
    }
}

Matrix::Matrix(const std::vector<std::vector<double>>& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("The matrix must have values.");
    }

    int cols = matrix[0].size();

    for (auto& row : matrix) {
        if (row.size() != cols) {
            throw std::invalid_argument("The matrix must have equal amount of columns.");
        }
    }
    m_row = matrix.size(); 
    m_col = cols;
    m_matrix = matrix;
}

void Matrix::fill(double x) {
    for (auto& vec : m_matrix) {
        for (auto& element : vec) {
            element = x;
        }
    }
}

void Matrix::fill_random(int seed) {
    if (!seed) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000);
    gen.seed(seed);
    for (auto& vec : m_matrix) {
        for (auto& element : vec) {
            element = dis(gen) / 100.f;
        }
    }
}

void Matrix::augmant(const std::vector<double>& vec) {
    if (vec.size() != m_row) {
        throw std::invalid_argument("The augmanted matrix is the wrong size.");
    }
    m_augmanted = vec;
}

void Matrix::show_matrix() const {
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            std::cout << std::setw(10) << m_matrix[i][j];
        }
        if (!m_augmanted.empty()) {
            std::cout << std::setw(3) << '|' << std::setw(3) <<  m_augmanted[i] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::clear() {
    m_matrix.clear();
    m_augmanted.clear();
    m_row = 0;
    m_col = 0;
}


Matrix Matrix::transpose() const {
    Matrix tmp(m_col, m_row);
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            tmp.m_matrix[j][i] = m_matrix[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::solve_system() const {
    if (m_augmanted.empty()) {
        throw std::invalid_argument("Can't solve non augmanted matrix.");
    }
    return solve(true, false); 
}

Matrix Matrix::get_inverse() const {
    if (m_col != m_row) {
        throw std::invalid_argument("Matrix must be square to be inverted.");
    }
    return solve(false, true); 
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (m_col != other.m_col || m_row != other.m_row) {
        throw std::invalid_argument("The matrices can't be added.");
    }
    Matrix tmp(m_row, m_col);
    for (int i = 0; i < m_row; i++) { 
        for (int j = 0; j < m_col; j++) { 
            tmp.m_matrix[i][j] = m_matrix[i][j] + other.m_matrix[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (m_col != other.m_row) {
        throw std::invalid_argument("The matrices can't be multiplied.");
    }
    Matrix tmp(m_row, other.m_col);
    for (int i = 0; i < tmp.m_row; i++) {
        for (int j = 0; j < tmp.m_col; j++) {
            double sum = 0.0;
            for (int k = 0; k < m_col; k++) { 
                sum += m_matrix[i][k] * other.m_matrix[k][j]; 
            }
            tmp.m_matrix[i][j] = sum;
        }
    }
    return tmp;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix tmp(m_row, m_col);
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            tmp.m_matrix[i][j] = m_matrix[i][j] * scalar;
        }
    }
    return tmp;
}

Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

Matrix Matrix::solve(bool is_augmanted, bool is_inverted) const {
    Matrix identity(m_row);
    Matrix tmp(*this);
    for (int i = 0; i < tmp.m_row; i++) {
        if (tmp.m_matrix[i][i] == 0) {
            int j = i + 1;
            while (j < tmp.m_row && tmp.m_matrix[i][j] == 0 && j++);
            if (j == tmp.m_row) {
                continue;
            }
            std::swap(tmp.m_matrix[i], tmp.m_matrix[j]);
            if (is_inverted) {
                std::swap(identity.m_matrix[i], identity.m_matrix[j]);
            }
            if (is_augmanted) {
                std::swap(tmp.m_augmanted[i], tmp.m_augmanted[j]);
            }
        }

        double pivot = tmp.m_matrix[i][i];
        if (pivot == 0) {
            continue;
        }

        tmp.m_matrix[i] = tmp.div_row(i, pivot);
        if (is_inverted) {
            identity.m_matrix[i] = identity.div_row(i, pivot);
        }
        if (is_augmanted) {
            tmp.m_augmanted[i] /= pivot;
        }

        for (int j = 0; j < tmp.m_row; j++) {
            double tmp_value = tmp.m_matrix[j][i];
            if (j != i && tmp_value) {
                tmp.m_matrix[j] = sub_vec(tmp.m_matrix[j], tmp.mul_row(i, tmp_value));
                if (is_inverted) {
                    identity.m_matrix[j] = sub_vec(identity.m_matrix[j], identity.mul_row(i, tmp_value));
                }
                if (is_augmanted) {
                    tmp.m_augmanted[j] = tmp.m_augmanted[j] - tmp.m_augmanted[j] * tmp.m_augmanted[i];
                }
            }
        }
    }
    return is_inverted ? identity : tmp;
}

std::vector<double> Matrix::sub_vec(const std::vector<double>& vec1, const std::vector<double>& vec2) const {
    std::vector<double> tmp;
    for (int i = 0; i < vec1.size(); i++) {
        tmp.push_back(vec1[i] - vec2[i]);
    }
    return tmp;
}

std::vector<double> Matrix::mul_row(double row, const double value) const {
    std::vector<double> tmp = m_matrix[row];
    for (auto& element : tmp) {
        element *= value;
    }
    return tmp;
}

std::vector<double> Matrix::div_row(double row, const double value) const {
    std::vector<double> tmp = m_matrix[row];
    for (auto& element : tmp) {
        element /= value;
    }
    return tmp;
}

