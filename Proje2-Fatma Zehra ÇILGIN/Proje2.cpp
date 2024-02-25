/**
 * Proje2
 * complex sayılar, vectörler ve matrixlerle ilgili bazı işlemler.
 * Proje 2
 * 01.01.2024
 * Fatma Zehra ÇILGIN
 */
#include <iostream>
#include <vector>

class Imaginary
{
private:
    double im;

public:
    Imaginary(double imaginary) : im(imaginary) {}

    double getIm() const
    {
        return im;
    }
    void setIm(double newIm)
    {
        im = newIm;
    }
};

class Complex : public Imaginary
{
private:
    double re;
    double im;

public:
    Complex(double realPart, double imaginaryPart) : re(realPart), Imaginary(imaginaryPart) {}

    double getRe() const
    {
        return re;
    }

    // toplama
    Complex operator+(const Complex &other) const
    {
        return Complex(re + other.re, getIm() + other.getIm());
    }
    // çıkarma
    Complex operator-(const Complex &other) const
    {
        return Complex(re - other.re, getIm() - other.getIm());
    }
    // çarpma
    Complex operator*(const Complex &other) const
    {
        double resultRe = re * other.re - getIm() * other.getIm();
        double resultIm = re * other.getIm() + getIm() * other.re;
        return Complex(resultRe, resultIm);
    }
    // bölme
    Complex operator/(const Complex &other) const
    {
        double denominator = other.re * other.re + other.getIm() * other.getIm();
        double resultRe = (re * other.re + getIm() * other.getIm()) / denominator;
        double resultIm = (getIm() * other.re - re * other.getIm()) / denominator;
        return Complex(resultRe, resultIm);
    }
    // eşlenik
    Complex operator~() const
    {
        return Complex(re, -getIm());
    }
    // Atama (=) operatörü aşırı yükleme
    Complex &operator=(const Complex &other)
    {
        if (this != &other)
        {
            re = other.re;
            setIm(other.getIm());
        }
        return *this;
    }
    // Toplama atama (+=) operatörü aşırı yükleme
    Complex &operator+=(const Complex &other)
    {
        re += other.re;
        setIm(getIm() + other.getIm());
        return *this;
    }
    // Çıkarma atama (-=) operatörü aşırı yükleme
    Complex &operator-=(const Complex &other)
    {
        re -= other.re;
        setIm(getIm() - other.getIm());
        return *this;
    }
    // Çarpma atama (*=) operatörü aşırı yükleme
    Complex &operator*=(const Complex &other)
    {
        double resultRe = re * other.re - getIm() * other.getIm();
        double resultIm = re * other.getIm() + getIm() * other.re;
        re = resultRe;
        setIm(resultIm);
        return *this;
    }
    // Bölme atama (/=) operatörü aşırı yükleme
    Complex &operator/=(const Complex &other)
    {
        double denominator = other.re * other.re + other.getIm() * other.getIm();
        double resultRe = (re * other.re + getIm() * other.getIm()) / denominator;
        double resultIm = (getIm() * other.re - re * other.getIm()) / denominator;
        re = resultRe;
        setIm(resultIm);
        return *this;
    }
    // Eşit mi (==) operatörü aşırı yükleme
    bool operator==(const Complex &other) const
    {
        return (re == other.re) && (getIm() == other.getIm());
    }
    bool operator!=(const Complex &other) const
    {
        return (re != other.re) || (getIm() != other.getIm());
    }

    void print() const
    {
        std::cout << re << " "
                  << "+ " << getIm() << "i";
    }
};

class Vector
{
private:
    size_t size;
    std::vector<Complex> elements;

public:
    Vector(size_t s, const std::vector<Complex> &elems) : size(s), elements(elems) {}

    size_t getSize() const
    {
        return size;
    }

    const std::vector<Complex> &getElements() const
    {
        return elements;
    }

    Vector operator+(const Vector &other) const
    {
        if (size != other.getSize())
        {
            throw std::invalid_argument("Vector sizes must be the same for addition.");
        }

        std::vector<Complex> resultElements;
        for (size_t i = 0; i < size; ++i)
        {
            resultElements.push_back(elements[i] + other.getElements()[i]);
        }

        return Vector(size, resultElements);
    }

    Vector operator-(const Vector &other) const
    {
        if (size != other.getSize())
        {
            throw std::invalid_argument("Vector sizes must be the same for subtraction.");
        }

        std::vector<Complex> resultElements;
        for (size_t i = 0; i < size; ++i)
        {
            resultElements.push_back(elements[i] - other.getElements()[i]);
        }

        return Vector(size, resultElements);
    }

    Vector operator*(const Vector &other) const
    {
        if (size != other.getSize())
        {
            throw std::invalid_argument("Vector sizes must be the same for subtraction.");
        }

        std::vector<Complex> resultElements;
        for (size_t i = 0; i < size; ++i)
        {
            resultElements.push_back(elements[i] * other.getElements()[i]);
        }

        return Vector(size, resultElements);
    }

    Vector &operator=(const Vector &other)
    {
        size = other.size;
        elements = other.elements;
        return *this;
    }

    Vector &operator+=(const Vector &other)
    {
        *this = *this + other;
        return *this;
    }

    Vector &operator-=(const Vector &other)
    {
        *this = *this - other;
        return *this;
    }

    Vector &operator*=(const Vector &other)
    {
        if (size != other.size)
        {
            // Uyumsuz boyutlar
            throw std::invalid_argument("Vector dimensions are incompatible for dot product");
        }

        for (size_t i = 0; i < size; ++i)
        {
            elements[i] = elements[i] * other.elements[i];
        }

        return *this;
    }

    bool operator==(const Vector &other) const
    {
        return (size == other.getSize()) && (elements == other.getElements());
    }

    void print() const
    {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i)
        {
            elements[i].print();
            if (i < size - 1)
                std::cout << ", ";
        }
        std::cout << "] ";
    }
};

class Matrix
{
private:
    size_t row;
    size_t col;
    std::vector<std::vector<Complex>> elements;

public:
    Matrix(size_t r, size_t c, const std::vector<std::vector<Complex>> &elems) : row(r), col(c), elements(elems) {}
    Matrix(size_t c, const std::vector<std::vector<Complex>> &elems) : col(c), elements(elems) {}

    size_t getRow() const
    {
        return row;
    }

    size_t getCol() const
    {
        return col;
    }

    const std::vector<std::vector<Complex>> &getElements() const
    {
        return elements;
    }

    Matrix operator+(const Matrix &other) const
    {
        if (row != other.getRow() || col != other.getCol())
        {
            throw std::invalid_argument("Matrix dimensions must be the same for addition.");
        }

        std::vector<std::vector<Complex>> resultElements;
        for (size_t i = 0; i < row; ++i)
        {
            std::vector<Complex> rowElements;
            for (size_t j = 0; j < col; ++j)
            {
                rowElements.push_back(elements[i][j] + other.getElements()[i][j]);
            }
            resultElements.push_back(rowElements);
        }

        return Matrix(row, col, resultElements);
    }

    Matrix operator-(const Matrix &other) const
    {
        if (row != other.getRow() || col != other.getCol())
        {
            throw std::invalid_argument("Matrix dimensions must be the same for subtraction.");
        }

        std::vector<std::vector<Complex>> resultElements;
        for (size_t i = 0; i < row; ++i)
        {
            std::vector<Complex> rowElements;
            for (size_t j = 0; j < col; ++j)
            {
                rowElements.push_back(elements[i][j] - other.getElements()[i][j]);
            }
            resultElements.push_back(rowElements);
        }

        return Matrix(row, col, resultElements);
    }

    Matrix operator*(const Matrix &other) const
    {
        if (col != other.getRow())
        {
            throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for multiplication.");
        }

        std::vector<std::vector<Complex>> resultElements(row, std::vector<Complex>(other.getCol(), Complex(0, 0)));
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < other.getCol(); ++j)
            {
                for (size_t k = 0; k < col; ++k)
                {
                    resultElements[i][j] = resultElements[i][j] + (elements[i][k] * other.getElements()[k][j]);
                }
            }
        }

        return Matrix(row, other.getCol(), resultElements);
    }

    Matrix &operator=(const Matrix &other)
    {
        row = other.row;
        col = other.col;
        return *this;
    }

    Matrix &operator+=(const Matrix &other)
    {
        if (row != other.getRow() || col != other.getCol())
        {
            throw std::invalid_argument("Matrix dimensions must be the same for addition.");
        }

        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                elements[i][j] += other.getElements()[i][j];
            }
        }

        return *this;
    }

    Matrix &operator-=(const Matrix &other)
    {
        if (row != other.getRow() || col != other.getCol())
        {
            throw std::invalid_argument("Matrix dimensions must be the same for subtraction.");
        }

        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                elements[i][j] -= other.getElements()[i][j];
            }
        }

        return *this;
    }

    Matrix &operator*=(const Matrix &other)
    {
        if (col != other.getRow())
        {
            throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for multiplication.");
        }

        std::vector<std::vector<Complex>> resultElements(row, std::vector<Complex>(other.getCol(), Complex(0, 0)));
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < other.getCol(); ++j)
            {
                for (size_t k = 0; k < col; ++k)
                {
                    resultElements[i][j] = resultElements[i][j] + (elements[i][k] * other.getElements()[k][j]);
                }
            }
        }

        // Update the current matrix with the result
        row = resultElements.size();
        col = resultElements[0].size();
        elements = resultElements;

        return *this;
    }

    bool operator==(const Matrix &other) const
    {
        return (row == other.getRow()) && (col == other.getCol()) && (elements == other.getElements());
    }

    void print() const
    {
        for (std::size_t i = 0; i < row; ++i)
        {
            for (std::size_t j = 0; j < col; ++j)
            {
                elements[i][j].print();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix transpose() const
    {
        std::vector<std::vector<Complex>> resultElements(col, std::vector<Complex>(row, Complex(0, 0)));
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                resultElements[j][i] = elements[i][j];
            }
        }

        return Matrix(col, row, resultElements);
    }

    double determinant() const
    {
        if (row != col)
        {
            throw std::invalid_argument("Determinant can only be calculated for square matrices.");
        }

        return elements[0][0].getRe() * elements[1][1].getRe() - elements[0][1].getRe() * elements[1][0].getRe();
    }
};

class SquareMatrix : public Matrix
{
public:
    SquareMatrix(size_t size, const std::vector<std::vector<Complex>> &elems) : Matrix(size, size, elems)
    {
        if (size != elems.size() || size != elems[0].size())
        {
            throw std::invalid_argument("Kare matrix degil");
        }
    }
};

class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix(size_t size) : Matrix(size, generateIdentityMatrix(size)) {}

private:
    static std::vector<std::vector<Complex>> generateIdentityMatrix(size_t size)
    {
        std::vector<std::vector<Complex>> identityMatrix(size, std::vector<Complex>(size, Complex(0, 0)));
        for (size_t i = 0; i < size; ++i)
        {
            identityMatrix[i][i] = Complex(1, 0);
        }
        return identityMatrix;
    }
};

class TriangleMatrix : public Matrix
{
public:
    TriangleMatrix(size_t size, const std::vector<std::vector<Complex>> &elems) : Matrix(size, size, elems) {}

private:
    static bool isTriangleMatrix(const std::vector<std::vector<Complex>> &elems)
    {
        size_t size = elems.size();
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                if (j <= i && elems[i][j] != Complex(0, 0))
                {
                    return false; // Not a triangle matrix
                }
            }
        }
        return true;
    }
};

class LinearAlgebraObject
{
public:
    virtual void print() const = 0;
    virtual size_t getSize() const = 0;
    virtual bool operator==(const LinearAlgebraObject &other) const = 0;
    virtual LinearAlgebraObject operator+(const LinearAlgebraObject &other) const = 0;
    virtual LinearAlgebraObject operator-(const LinearAlgebraObject &other) const = 0;
    virtual LinearAlgebraObject operator*(const LinearAlgebraObject &other) const = 0;
    virtual LinearAlgebraObject transpose() const = 0;
    virtual double determinant() const = 0;
    virtual ~LinearAlgebraObject() = default;
};

int main()
{

    // Birinci kompleks sayı
    Complex complex1(2.0, 3.0);
    std::cout << "Complex Number 1: ";
    complex1.print();
    std::cout << std::endl;

    // İkinci kompleks sayı
    Complex complex2(1.0, -2.0);
    std::cout << "Complex Number 2: ";
    complex2.print();
    std::cout << std::endl;

    // Toplama işlemi
    Complex sum = complex1 + complex2;
    std::cout << "TOPLAM: ";
    sum.print();
    std::cout << std::endl;

    // Çıkarma işlemi
    Complex difference = complex1 - complex2;
    std::cout << "FARK: ";
    difference.print();
    std::cout << std::endl;

    // Çarpma işlemi
    Complex product = complex1 * complex2;
    std::cout << "CARPIM: ";
    product.print();
    std::cout << std::endl;

    // Bölme işlemi
    Complex quotient = complex1 / complex2;
    std::cout << "BOLUM: ";
    quotient.print();
    std::cout << std::endl;

    // eşlenik
    Complex conjugateComplex = ~complex1;
    std::cout << "COMPLEX1 ESLENIGI: ";
    conjugateComplex.print();
    std::cout << std::endl;

    // Atama işlemleri
    Complex compoundSum = complex1;
    compoundSum += complex2;

    Complex compoundDifference = complex1;
    compoundDifference -= complex2;

    Complex compoundProduct = complex1;
    compoundProduct *= complex2;

    Complex compoundQuotient = complex1;
    compoundQuotient /= complex2;

    std::cout << "Compound Sum: ";
    compoundSum.print();
    std::cout << std::endl;

    std::cout << "Compound Difference: ";
    compoundDifference.print();
    std::cout << std::endl;

    std::cout << "Compound Product: ";
    compoundProduct.print();
    std::cout << std::endl;

    std::cout << "Compound Quotient: ";
    compoundQuotient.print();
    std::cout << std::endl;

    // Eşitlik kontrolü
    bool areEqualComplex = complex1 == complex2;
    std::cout << "Complex sayilar esit mi: " << std::boolalpha << areEqualComplex << std::endl;
    std::cout << "*********************************************************" << std::endl;

    std::vector<Complex> vec1 = {Complex(1, 2), Complex(3, 4), Complex(5, 6)};
    Vector vector1(vec1.size(), vec1);

    std::vector<Complex> vec2 = {Complex(7, 8), Complex(9, 10), Complex(11, 12)};
    Vector vector2(vec2.size(), vec2);

    // Birinci vektör
    std::cout << "Vector 1:";
    vector1.print();
    std::cout << "\n\n";
    // İkinci vektör
    std::cout << "Vector 2:";
    vector2.print();
    std::cout << "\n\n";
    // Toplama işlemi
    std::cout << "TOPLAM: ";
    Vector vectorSum = vector1 + vector2;
    vectorSum.print();
    std::cout << "\n\n";
    // çıkarma işlemi
    std::cout << "FARK:";
    Vector vectorDifference = vector1 - vector2;
    vectorDifference.print();
    std::cout << "\n\n";
    // çarpma işlemi
    std::cout << "CARPIM:";
    Vector vectorProduct = vector1 * vector2;
    vectorProduct.print();
    std::cout << "\n\n";

    // Atama İşlemleri
    std::cout << "Compound sum: ";
    vector1 += vector2;
    vector1.print();
    std::cout << "\n\n";

    std::cout << "Compound difference: ";
    vector1 -= vector2;
    vector1.print();
    std::cout << "\n\n";

    std::cout << "Compund product: ";
    vector1 *= vector2;
    vector1.print();
    std::cout << "\n\n";

    // Eşitlik kontrolü
    bool areEqualVector = vec1 == vec2;
    std::cout << "Vektorler esit mi?: " << std::boolalpha << areEqualVector << std::endl;
    std::cout << "*********************************************************" << std::endl;

    std::vector<std::vector<Complex>>
        mat1 = {
            {Complex(1, 2), Complex(3, 4)},
            {Complex(5, 6), Complex(7, 8)}};
    Matrix matrix1(mat1.size(), mat1[0].size(), mat1);

    std::vector<std::vector<Complex>> mat2 = {
        {Complex(9, 10), Complex(11, 12)},
        {Complex(13, 14), Complex(15, 16)}};
    Matrix matrix2(mat2.size(), mat2[0].size(), mat2);

    // Matrix 1
    std::cout << "\nMatrix 1:\n";
    matrix1.print();
    std::cout << std::endl;
    // Matrix 2
    std::cout << "Matrix 2:\n";
    matrix2.print();
    std::cout << std::endl;

    // Toplama işlemi
    std::cout << "TOPLAM:\n";
    Matrix toplam = matrix1 + matrix2;
    toplam.print();
    std::cout << std::endl;

    // çıkarma işlemi
    std::cout << "FARK:\n";
    Matrix fark = matrix1 - matrix2;
    fark.print();
    std::cout << std::endl;

    // çarpma işlemi
    Matrix carpim = matrix1 * matrix2;
    std::cout << "CARPIM:\n";
    carpim.print();
    std::cout << std::endl;

    // Atama İşlemleri
    std::cout << "Compound sum:\n";
    matrix1 += matrix2;
    matrix1.print();
    std::cout << "\n";

    std::cout << "Compound difference:\n";
    matrix1 -= matrix2;
    matrix1.print();
    std::cout << "\n";

    std::cout << "Compund product:\n";
    matrix1 *= matrix2;
    matrix1.print();
    std::cout << "\n";

    // Transpose işlemi
    Matrix transposedMatrix = matrix2.transpose();
    std::cout << "\nMatrix 2'in transpozu:" << std::endl;
    for (size_t i = 0; i < transposedMatrix.getRow(); ++i)
    {
        for (size_t j = 0; j < transposedMatrix.getCol(); ++j)
        {
            std::cout << transposedMatrix.getElements()[i][j].getRe() << "+"
                      << transposedMatrix.getElements()[i][j].getIm() << "i"
                      << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Determinant İslemi
    double det = matrix1.determinant();
    std::cout << "Matrix 1'in determinanti: " << det << std::endl;
    std::cout << std::endl;

    // eşitlik kontrolü
    bool areEqualMatrix = (matrix1 == matrix2);
    std::cout << "Matrixler esit mi? " << std::boolalpha << areEqualMatrix << std::endl;
    std::cout << "*********************************************************" << std::endl;

    // Test SquareMatrix
    std::vector<std::vector<Complex>> squareMatrixElements = {{Complex(1, 2), Complex(3, 4)},
                                                              {Complex(5, 6), Complex(7, 8)}};
    SquareMatrix squareMatrix(squareMatrixElements.size(), squareMatrixElements);
    std::cout << "Square Matrix:" << std::endl;
    squareMatrix.print();
    std::cout << std::endl;

    std::vector<std::vector<Complex>> triangleMatrixElements = {
        {Complex(1, 0), Complex(2, 0), Complex(3, 0)},
        {Complex(0, 0), Complex(4, 0), Complex(5, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(6, 0)}};
    TriangleMatrix triangleMatrix(3, triangleMatrixElements);
    std::cout << "Triangle Matrix:" << std::endl;
    triangleMatrix.print();

    // Test IdentityMatrix
    size_t identitySize = 2;
    IdentityMatrix identityMatrix(identitySize);
    std::cout << "\nIdentity Matrix:" << std::endl;
    identityMatrix.print();
    std::cout << std::endl;

    return 0;
}