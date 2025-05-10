#include "Matrices-5.h"

namespace Matrices
{
    ///Construct a matrix of the specified size.
    ///Initialize each element to 0.
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        a.resize(rows, vector<double>(cols,0.0));
    }

    ///Add each corresponding element.
    ///usage:  c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if(a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix matrixC(a.getRows(),a.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                matrixC(i,j) = a(i,j) + b(i,j);
            }
        }

        return matrixC;
    }

    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if(a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix matrixC(a.getRows(),b.getCols());

        for(int i = 0; i < a.getRows(); i++)
        {
            for(int k = 0; k < b.getCols(); k++)
            {
                for(int j = 0; j < a.getCols(); j++)
                {
                    matrixC(i,k) += a(i,j) * b(j,k);
                }
            }
        }
        return matrixC;
    }

    ///Matrix comparison.  See description.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if(a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for(int i = 0; i < a.getRows(); i++)
        {
            for(int j = 0; j < a.getCols(); j++)
            {
                if(abs(a(i,j) - b(i,j)) < 0.001)
                {
                    return false;
                }
            }
        }

        return true;
    }

    ///Matrix comparison.  See description.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a==b);
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for(int i = 0; i < a.getRows(); i++)
        {
            for(int j = 0; j < a.getCols(); j++)
            {
                os << setw(10) << a(i,j) << " ";
            }
            os << endl;
        }
        return os;
    }
}
