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
//------------------------------------------------------------------------------------------
Matrix algebra::ones(size_t n, size_t m)
{
    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp(m, 1);
        output.push_back(temp);
    }
    return output;
}
//------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------
void algebra::show(const Matrix& matrix)
{
    std::cout << std::endl;
    for (size_t i {}; i < matrix.size(); i++) {
        std::cout << std::fixed << "|";
        for (size_t j {}; j < matrix[0].size(); j++) {
            std::cout << std::setw(7) << std::fixed << std::setprecision(3)
                      << std::showpos << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}
//------------------------------------------------------------------------------------------
Matrix algebra::multiply(const Matrix& matrix, double c)
{
    Matrix temp { matrix };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            temp[i][j] *= c;

    return temp;
}
//------------------------------------------------------------------------------------------
Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2)
{
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix {};
    } else if (matrix1.empty() || matrix2.empty())
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");

    if (matrix1[0].size() != matrix2.size())
        throw std::logic_error("matrices with wrong dimensions cannot be multiplied");

    else {
        Matrix Output { algebra::zeros(matrix1.size(), matrix2[0].size()) };
        for (size_t i {}; i < matrix1.size(); i++)
            for (size_t j {}; j < matrix2[0].size(); j++)
                for (size_t k {}; k < matrix2.size(); k++)
                    Output[i][j] += matrix1[i][k] * matrix2[k][j];
        return Output;
    }
}
//------------------------------------------------------------------------------------------
Matrix algebra::sum(const Matrix& matrix, double c)
{
    if (matrix.empty())
        return Matrix {};

    Matrix temp { matrix };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            temp[i][j] += c;

    return temp;
}
//------------------------------------------------------------------------------------------
Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2)
{
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix {};
    } else if (matrix1.empty() || matrix2.empty())
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");

    Matrix Summ { algebra::zeros(matrix1.size(), matrix1[0].size()) };
    if (matrix1.size() == matrix2.size()
        && matrix1[0].size() == matrix2[0].size()) {
        for (size_t i {}; i < matrix1.size(); i++)
            for (size_t j {}; j < matrix1[0].size(); j++)
                Summ[i][j] += matrix1[i][j] + matrix2[i][j];
    } else
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");
    return Summ;
}
//------------------------------------------------------------------------------------------
Matrix algebra::transpose(const Matrix& matrix)
{
    if (matrix.empty())
        return Matrix {};

    Matrix Trans { algebra::zeros(matrix[0].size(), matrix.size()) };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            Trans[j][i] = matrix[i][j];
    return Trans;
}
//------------------------------------------------------------------------------------------
Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m)
{
    if (matrix.empty())
        return Matrix {};

    Matrix Temp { matrix };
    Temp.erase(Temp.begin() + n);
    Temp = algebra::transpose(Temp);
    Temp.erase(Temp.begin() + m);
    return algebra::transpose(Temp);
}
//------------------------------------------------------------------------------------------
double algebra::determinant(const Matrix& matrix)
{
    if (matrix.empty())
        return 1;
    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no determinant");

    // if (matrix.size() == 2 && matrix[0].size() == 2)
    //     return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    if (matrix.size() == 1 && matrix[0].size() == 1)
        return matrix[0][0];

    Matrix Temp { matrix };
    double Det {};
    for (size_t i {}; i < Temp[0].size(); i++)
        Det += std::pow(-1, 1 + i + 1) * Temp[0][i]
            * algebra::determinant(algebra::minor(Temp, 0, i));

    return Det;
}
//------------------------------------------------------------------------------------------
Matrix algebra::inverse(const Matrix& matrix)
{
    if (matrix.empty())
        return Matrix {};

    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no inverse");
    if (algebra::determinant(matrix) == 0)
        throw std::logic_error("singular matrices have no inverse");

    Matrix output { algebra::zeros(matrix.size(), matrix[0].size()) };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            output[i][j] = std::pow(-1, i + j + 2)
                * algebra::determinant(algebra::minor(matrix, i, j));

    output = algebra::transpose(output);
    output = algebra::multiply(output, (1 / algebra::determinant(matrix)));
    return output;
}
//------------------------------------------------------------------------------------------
Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
{
    if (axis == 0 && matrix1[0].size() != matrix2[0].size())
        throw std::logic_error("matrices with wrong dimensions cannot be concatenated");
    if (axis == 1 && matrix1.size() != matrix2.size())
        throw std::logic_error("matrices with wrong dimensions cannot be concatenated");

    Matrix Temp { matrix1 };

    if (axis == 0) {
        for (size_t i {}; i < matrix2.size(); i++)
            Temp.push_back(matrix2[i]);
        return Temp;
    }

    else {
        Temp = algebra::transpose(Temp);
        for (size_t i {}; i < matrix2[0].size(); i++)
            Temp.push_back(algebra::transpose(matrix2)[i]);

        return algebra::transpose(Temp);
    }
}
//------------------------------------------------------------------------------------------
Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2)
{
    if (r1 >= matrix.size() || r2 >= matrix.size())
        throw std::logic_error("r1 or r2 inputs are out of range");

    Matrix output { matrix };
    output[r1].swap(output[r2]);
    return output;
}
//------------------------------------------------------------------------------------------
Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c)
{
    Matrix output { matrix };
    output[r].swap(algebra::multiply(matrix, c)[r]);
    return output;
}
//------------------------------------------------------------------------------------------
Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
{
    Matrix output { matrix };
    Matrix temp { algebra::ero_multiply(matrix, r1, c) };
    temp[r2].swap(temp[r1]);
    temp = algebra::sum(temp, matrix);
    output[r2].swap(temp[r2]);
    return output;
}
//------------------------------------------------------------------------------------------
Matrix algebra::upper_triangular(const Matrix& matrix)
{
    if (matrix.empty())
        return Matrix {};

    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no upper triangular form");

    Matrix output { matrix };
    std::vector<size_t> r {};

    for (size_t j {}; j < matrix[0].size(); j++)
        for (size_t i { j }; i < matrix.size(); i++)
            if (matrix[i][j] != 0) {
                output[j].swap(output[i]);
                break;
            }
    for (size_t k {}; k < matrix.size(); k++)
        for (size_t z { k + 1 }; z < matrix.size(); z++)
            output = algebra::ero_sum(output, k, -output[z][k] / output[k][k], z);

    // algebra::show(matrix);
    // algebra::show(output);

    return output;
}
//------------------------------------ The End :)) ---------------------------------