#include "hw1.h"

Matrix algebra::zeros(size_t n, size_t m)
{
    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp(m);
        output.push_back(temp);
    }
    return output;
}

Matrix algebra::ones(size_t n, size_t m)
{
    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp(m, 1);
        output.push_back(temp);
    }
    return output;
}

Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    if (min > max)
        throw std::logic_error("min cannot be greater than max");

    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp;
        for (size_t j {}; j < m; j++) {
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<double> distr(min, max); // Range is Min to Max
            temp.push_back(distr(eng));
        }
        output.push_back(temp);
    }
    return output;
}

void algebra::show(const Matrix& matrix)
{
    std::cout << std::endl;
    for (size_t i {}; i < matrix.size(); i++) {
        std::cout << std::setw(10) << std::left << "|";
        for (size_t j {}; j < matrix[0].size(); j++) {
            std::cout << std::setw(10) << std::left << std::setprecision(3)
                      << std::showpos << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}
Matrix algebra::multiply(const Matrix& matrix, double c)
{
    Matrix temp { matrix };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            temp[i][j] *= c;

    return temp;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2)
{
    if (matrix1[0].size() == matrix.size())
        throw std::logic_error("matrices with wrong dimensions cannot be multiplied");

    Matrix Output = algebra::zeros(matrix1.size(), matrix2[0].size());
}