
#include "hw1.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (true) // make false to run unit-tests
    {
        // std::cout << algebra::determinant(Matrix matrix { { 2, 2 }, { 3, 4 } });
        // Matrix matrix { { 0, 0, -1.75, -2 }, { 1, 0, -2.75, -3 }, { 3, 5, 0, -4 }, { 4, 4.5, 4.75, 0 } };
        Matrix matrix { { 1, 2, 3 }, { 4, 7, 5 }, { 6, 1, 3 } };
        // Matrix matrix { { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 } };
        algebra::upper_triangular(matrix);

        //  debug section
    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}