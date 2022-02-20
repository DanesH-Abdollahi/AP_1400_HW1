#include "hw1.h"

Matrix algebra::zeros(size_t n, size_t m)
{
    // If Size of The Matrix is Zero.
    if (n == 0 || m == 0)
        return Matrix {};
    // Definig The Output Matrix
    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp(m);
        output.push_back(temp);
    }
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::ones(size_t n, size_t m)
{
    // If Size of The Matrix is Zero.
    if (n == 0 || m == 0)
        return Matrix {};
    // Definig The Output Matrix
    Matrix output;
    for (size_t i {}; i < n; i++) {
        std::vector<double> temp(m, 1);
        output.push_back(temp);
    }
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    // If Size of The Matrix is Zero.
    if (n == 0 || m == 0)
        return Matrix {};
    // If The Input Min is bigger than Min
    if (min > max)
        throw std::logic_error("min cannot be greater than max");
    // Definig The Output Matrix
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
//------------------------------------------------------------------------------
void algebra::show(const Matrix& matrix)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        throw std::logic_error("Empty Matrix Can't be Shown");

    // Shohwing The Output Matrix
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
//------------------------------------------------------------------------------
Matrix algebra::multiply(const Matrix& matrix, double c)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // Definig The Output Matrix
    Matrix temp { matrix };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            temp[i][j] *= c;

    return temp;
}
//------------------------------------------------------------------------------
Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2)
{
    // If The Input Matrices is Empty.
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix {};
        // If One Of The Input Matrices is Empty.
    } else if (matrix1.empty() || matrix2.empty())
        throw std::logic_error("matrices with wrong dimensions cannot be multiplied");

    // If Matrices Dimesnsions doesn't Match !
    if (matrix1[0].size() != matrix2.size())
        throw std::logic_error("matrices with wrong dimensions cannot be multiplied");

    else {
        // Definig The Output Matrix
        Matrix Output { algebra::zeros(matrix1.size(), matrix2[0].size()) };
        for (size_t i {}; i < matrix1.size(); i++)
            for (size_t j {}; j < matrix2[0].size(); j++)
                for (size_t k {}; k < matrix2.size(); k++)
                    Output[i][j] += matrix1[i][k] * matrix2[k][j];
        return Output;
    }
}
//------------------------------------------------------------------------------
Matrix algebra::sum(const Matrix& matrix, double c)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};

    // Definig The Output Matrix
    Matrix temp { matrix };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            temp[i][j] += c;

    return temp;
}
//------------------------------------------------------------------------------
Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2)
{
    // If The Input Matrices is Empty.
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix {};
        // If One Of The Input Matrices is Empty.
    } else if (matrix1.empty() || matrix2.empty())
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");
    // Definig The Output Matrix
    Matrix Summ { algebra::zeros(matrix1.size(), matrix1[0].size()) };
    if (matrix1.size() == matrix2.size()
        && matrix1[0].size() == matrix2[0].size()) {
        for (size_t i {}; i < matrix1.size(); i++)
            for (size_t j {}; j < matrix1[0].size(); j++)
                Summ[i][j] += matrix1[i][j] + matrix2[i][j];
    } // If Matrices Dimesnsions doesn't Match !
    else
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");

    return Summ;
}
//------------------------------------------------------------------------------
Matrix algebra::transpose(const Matrix& matrix)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // Definig The Output Matrix
    Matrix Trans { algebra::zeros(matrix[0].size(), matrix.size()) };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            Trans[j][i] = matrix[i][j];
    return Trans;
}
//------------------------------------------------------------------------------
Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // Using erase Func. To Generate The Minor Matrix From Input Matrix.
    // Definig The Output Matrix
    Matrix Temp { matrix };
    Temp.erase(Temp.begin() + n);
    Temp = algebra::transpose(Temp);
    Temp.erase(Temp.begin() + m);
    return algebra::transpose(Temp);
}
//------------------------------------------------------------------------------
double algebra::determinant(const Matrix& matrix)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return 1;
    // If The Input Matrix isn't Square.
    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no determinant");
    // Defining The Initial Condition Cause We Using This Func. Recursively
    if (matrix.size() == 1 && matrix[0].size() == 1)
        return matrix[0][0];

    Matrix Temp { matrix };
    // Definig The Output Number.
    double Det {};
    for (size_t i {}; i < Temp[0].size(); i++)
        Det += std::pow(-1, 1 + i + 1) * Temp[0][i]
            * algebra::determinant(algebra::minor(Temp, 0, i));

    return Det;
}
//------------------------------------------------------------------------------
Matrix algebra::inverse(const Matrix& matrix)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // If The Input Matrix isn't Square.
    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no inverse");
    // If The Matrix Determinant is 0 .
    if (algebra::determinant(matrix) == 0)
        throw std::logic_error("singular matrices have no inverse");
    // Generating The Inverse Matrix
    Matrix output { algebra::zeros(matrix.size(), matrix[0].size()) };
    for (size_t i {}; i < matrix.size(); i++)
        for (size_t j {}; j < matrix[0].size(); j++)
            output[i][j] = std::pow(-1, i + j + 2)
                * algebra::determinant(algebra::minor(matrix, i, j));

    output = algebra::transpose(output);
    output = algebra::multiply(output, (1 / algebra::determinant(matrix)));
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
{
    // If The Input Matrices is Empty.
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix {};
        // If One Of The Input Matrices is Empty.
    } else if (matrix1.empty() || matrix2.empty())
        throw std::logic_error("matrices with wrong dimensions cannot be Summed");

    // If Matrices Dimesnsions doesn't Match !
    if (axis == 0 && matrix1[0].size() != matrix2[0].size())
        throw std::logic_error("matrices with wrong dimensions cannot be concatenated");
    if (axis == 1 && matrix1.size() != matrix2.size())
        throw std::logic_error("matrices with wrong dimensions cannot be concatenated");

    Matrix Temp { matrix1 };
    // If axis = 0
    if (axis == 0) {
        // Definig The Output Matrix
        for (size_t i {}; i < matrix2.size(); i++)
            Temp.push_back(matrix2[i]);
        return Temp;
    }
    // If axis = 1
    else {
        // Definig The Output Matrix
        Temp = algebra::transpose(Temp);
        for (size_t i {}; i < matrix2[0].size(); i++)
            Temp.push_back(algebra::transpose(matrix2)[i]);

        return algebra::transpose(Temp);
    }
}
//------------------------------------------------------------------------------
Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};

    // If r1 or r2 are Out Of Range.
    if (r1 >= matrix.size() || r2 >= matrix.size())
        throw std::logic_error("r1 or r2 inputs are out of range");
    // Definig The Output Matrix
    Matrix output { matrix };
    output[r1].swap(output[r2]);
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};

    // If r is Out Of Range.
    if (r >= matrix.size())
        throw std::logic_error("r is out of range");
    // Definig The Output Matrix
    Matrix output { matrix };
    output[r].swap(algebra::multiply(matrix, c)[r]);
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // If r1 or r2 are Out Of Range.
    if (r1 >= matrix.size() || r2 >= matrix.size())
        throw std::logic_error("r1 or r2 inputs are out of range");
    // Definig The Output Matrix
    Matrix output { matrix };
    Matrix temp { algebra::ero_multiply(matrix, r1, c) };
    temp[r2].swap(temp[r1]);
    temp = algebra::sum(temp, matrix);
    output[r2].swap(temp[r2]);
    return output;
}
//------------------------------------------------------------------------------
Matrix algebra::upper_triangular(const Matrix& matrix)
{
    // If The Input Matrix is Empty.
    if (matrix.empty())
        return Matrix {};
    // If The Input Matrix isn't Square.
    if (matrix.size() != matrix[0].size())
        throw std::logic_error("non-square matrices have no upper triangular form");

    Matrix output { matrix };
    std::vector<size_t> r {};
    // Sortting Matrix's Rows To Avoid Having Zero On Main Diagonal
    for (size_t j {}; j < matrix[0].size(); j++)
        for (size_t i { j }; i < matrix.size(); i++)
            if (matrix[i][j] != 0) {
                output[j].swap(output[i]);
                break;
            }
    // Generating The Upper_Trianglura Matrix
    for (size_t k {}; k < matrix.size(); k++)
        for (size_t z { k + 1 }; z < matrix.size(); z++)
            output = algebra::ero_sum(output, k, -output[z][k] / output[k][k], z);

    return output;
}
//-------------------------------- The End :)) ---------------------------------