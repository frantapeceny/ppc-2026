
/* Tento soubor se odevzdava. Zde implementujte vsechny potrebne funkce */

#include "matrix.hpp"

using namespace std;

/*** CONSTRUCTORS & DESTRUCTOR ***/
Matrix::Matrix(int nrow, int ncol)
{
    if (nrow < 0 || ncol < 0) throw matrix_negative_size();
    nrows = nrow;
    ncols = ncol;
    data = vector <value> (nrow*ncol, 0);
}

Matrix::Matrix(int rowscols)
{
    if (rowscols < 0) throw matrix_negative_size();
    nrows = rowscols;
    ncols = rowscols;
    data = vector <value> (rowscols * rowscols, 0);
}

Matrix::Matrix(const Matrix &m)
{
    nrows = m.nrows;
    ncols = m.ncols;
    data = m.data;
}

Matrix::Matrix(const std::vector<value> &v)
{
    nrows = v.size();
    ncols = v.size();
    data = vector <value> (nrows*ncols, 0);

    for (int i = 0; i < nrows; i++){
        data[i*ncols + i] = v[i];
    }
}

Matrix::~Matrix()
{

}

/*** L1 Matrix:: FUNCTIONS ***/
void Matrix::zeros()
{
    data = vector <value> (nrows * ncols, 0);
    // nebo lowkey: uniform(0);
}

void Matrix::uniform(value element)
{
    data = vector <value> (nrows * ncols, element);
}

void Matrix::eye()
{
    for (int r = 0; r < nrows; r++){
        for (int c = 0; c < ncols; c++){
            if (r == c){
                data[c + r*ncols] = 1;
            } else {
                data[c + r*ncols] = 0;
            }
        }
    }
}

void Matrix::bias(value b)
{
    for (int i = 0; i < nrows*ncols; i++){
        data[i] = data[i] + b;
    }
}

/*** L2 Matrix:: FUNCTIONS ***/
void Matrix::scale(value s)
{
    for (auto &d : data){
        d = d*s;
    }
}   

void Matrix::transpose()
{
    vector <value> dataCopy(nrows*ncols);
    for (int r = 0; r < nrows; r++){
        for (int c = 0; c < ncols; c++){
            dataCopy[c * nrows + r] = data [r * ncols + c];
        }
    }
    data = dataCopy;

    int something = nrows;
    nrows = ncols;
    ncols = something;
    //swap(nrows, ncols);
}

/*** L3 Matrix:: FUNCTIONS ***/
void Matrix::changedim(int rows, int cols)
{
    if (rows < 0 || cols < 0) throw matrix_negative_size();

    vector<value> novaData(rows * cols, 0);
    
    int minRows = min(rows, nrows);
    int minCols = min(cols, ncols);
    for (int r = 0; r < minRows; r++){
        for (int c = 0; c < minCols; c++){
            novaData[r*cols + c] = data[r*ncols + c];
        }
    }
    nrows = rows;
    ncols = cols;
    data = novaData;
}

/*** L1 Matrix:: Operators ***/
value Matrix::operator () (int row, int col) const
{
    if (row >= nrows || row < 0) throw std::out_of_range("Row index is out of range");
    if (col >= ncols || col < 0) throw std::out_of_range("Column index is out of range");
    return data[row*ncols + col];
}

value & Matrix::operator () (int row, int col)
{
    if (row >= nrows || row < 0) throw std::out_of_range("Row index is out of range");
    if (col >= ncols || col < 0) throw std::out_of_range("Column index is out of range");
    return data[row*ncols + col];
}

bool Matrix::operator==(const Matrix &m)
{
    if (nrows == m.nrows && ncols == m.ncols){
        for (int i = 0; i < nrows*ncols; i ++){
            if (data[i] != m.data[i]){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

Matrix & Matrix::operator=(const Matrix &m)
{
    nrows = m.nrows;
    ncols = m.ncols;
    data = m.data;
    return *this;
}

/*** L3 Matrix:: Operators ***/
std::vector<value> Matrix::operator () (void) const
{
    vector <value> v;
    int minimum = min(nrows, ncols);

    for (int i = 0; i < minimum; i++){
        v.push_back(data[i * ncols + i]);
    }
    return v;
}

/*** L1 NON-MEMBER FUNCTIONS/OPERATORS ***/
std::ostream & operator<<(std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < (int)m.data.size(); i++){
        os << setw(6) << m.data[i];
        if (i % m.ncols == m.ncols - 1){os << endl;}
    }
    if (m.nrows == 0 || m.ncols == 0){os << endl;}
    return os;
}

void loadMatrixFile(Matrix & m, string fname)
{
    ifstream file(fname);
    if (!file.is_open()) throw cannot_open_file();

    string line;
    if (!getline(file, line)) throw matrix_in_bad_header();
    
    istringstream header(line);
    int rows, cols;
    if (!(header >> rows >> cols)) throw matrix_in_bad_header();
    
    int nadbytecne;
    if (header >> nadbytecne) throw matrix_in_bad_header();

    if (rows < 0 || cols < 0) throw matrix_in_bad_header();

    Matrix matice(rows, cols);
    for (int i = 0; i < rows * cols; i++){
        if (!(file >> matice.data[i])) throw matrix_in_bad_body();
    }

    int zbytky;
    if (file >> zbytky) throw matrix_in_bad_body();

    m = matice;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.ncols != rhs.ncols || lhs.nrows != rhs.nrows) throw matrix_bad_sizes();
    Matrix vyslednaMatice(lhs.nrows, lhs.ncols);

    for (int i = 0; i < lhs.nrows * lhs.ncols; i++ ){
        vyslednaMatice.data[i] = lhs.data[i] + rhs.data[i];
    }
    return vyslednaMatice;
}

Matrix operator+(const value & lhs, const Matrix &rhs)
{
    Matrix vyslednaMatice(rhs.nrows, rhs.ncols);
    for (int i = 0; i < rhs.nrows * rhs.ncols; i++ ){
        vyslednaMatice.data[i] = lhs + rhs.data[i];
    }
    return vyslednaMatice;
}

Matrix operator+(const Matrix &lhs, const value & rhs) 
{
    Matrix vyslednaMatice(lhs.nrows, lhs.ncols);
    for (int i = 0; i < lhs.nrows * lhs.ncols; i++ ){
        vyslednaMatice.data[i] = rhs + lhs.data[i];
    }
    return vyslednaMatice;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.ncols != rhs.ncols || lhs.nrows != rhs.nrows) throw matrix_bad_sizes();
    Matrix vyslednaMatice(lhs.nrows, lhs.ncols);

    for (int i = 0; i < lhs.nrows * lhs.ncols; i++ ){
        vyslednaMatice.data[i] = lhs.data[i] - rhs.data[i];
    }
    return vyslednaMatice;
}

Matrix operator-(const value & lhs, const Matrix &rhs)
{
    Matrix vyslednaMatice(rhs.nrows, rhs.ncols);
    for (int i = 0; i < rhs.nrows * rhs.ncols; i++ ){
        vyslednaMatice.data[i] = lhs - rhs.data[i];
    }
    return vyslednaMatice;
}

Matrix operator-(const Matrix &lhs, const value & rhs) 
{
    Matrix vyslednaMatice(lhs.nrows, lhs.ncols);
    for (int i = 0; i < lhs.nrows * lhs.ncols; i++){
        vyslednaMatice.data[i] = lhs.data[i] - rhs;
    }
    return vyslednaMatice;
}

/*** L2 NON-MEMBER FUNCTIONS/OPERATORS ***/

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.ncols != rhs.nrows) throw matrix_bad_sizes();
    Matrix rhsT = rhs;
    rhsT.transpose();

    Matrix vyslednaMatice(lhs.nrows, rhs.ncols);

    for (int r = 0; r < lhs.nrows; r++){
        for (int c = 0; c < rhs.ncols; c++){
            for (int k = 0; k < lhs.ncols; k++){
                vyslednaMatice.data[r * rhs.ncols + c] += lhs.data[r * lhs.ncols + k] * rhsT.data[c * rhs.nrows + k];
            }
        }
    }
    return vyslednaMatice;
}

Matrix operator*(const value & lhs, const Matrix &rhs)
{
    Matrix vyslednaMatice(rhs.nrows, rhs.ncols);
    for (int i = 0; i < rhs.nrows * rhs.ncols; i++){
        vyslednaMatice.data[i] = rhs.data[i] * lhs;
    }
    return vyslednaMatice;
}

Matrix operator*(const Matrix &lhs, const value & rhs) 
{
    return rhs * lhs;
}

Matrix hadamard(const Matrix &lhs, const Matrix &rhs)
{
    if (rhs.nrows != lhs.nrows || rhs.ncols != lhs.ncols) throw matrix_bad_sizes();
    Matrix vyslednaMatice(rhs.nrows, rhs.ncols);
    for (int i = 0; i < rhs.nrows * rhs.ncols; i++){
        vyslednaMatice.data[i] = rhs.data[i] * lhs.data[i];
    }
    return vyslednaMatice;
}

Matrix power(const Matrix &m, unsigned int pow)
{
    if (m.nrows != m.ncols) throw matrix_bad_sizes();

    Matrix vyslednaMatice(m.nrows, m.ncols);
    vyslednaMatice.eye();

    for (unsigned int p = 0; p < pow; p++){
        vyslednaMatice = vyslednaMatice*m;
    }
    return vyslednaMatice;
}

/*** L3 NON-MEMBER FUNCTIONS/OPERATORS ***/
Matrix horzcat(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.nrows != rhs.nrows) throw matrix_bad_sizes();

    int rows = lhs.nrows;
    int cols = lhs.ncols + rhs.ncols;
    vector <value> novaData;
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < lhs.ncols; c++){
            novaData.push_back(lhs.data[r*lhs.ncols + c]);
        }
        for (int c = 0; c < rhs.ncols; c++){
            novaData.push_back(rhs.data[r*rhs.ncols + c]);
        }
    }
    Matrix matice (rows, cols);
    matice.data = novaData;
    return matice;
}

Matrix vertcat(const Matrix &top, const Matrix &bot)
{
    if (top.ncols != bot.ncols) throw matrix_bad_sizes();

    int rows = top.nrows + bot.nrows;
    int cols = top.ncols;
    vector <value> novaData;
    for (int i = 0; i < (int)top.data.size(); i++){
        novaData.push_back(top.data[i]);
    }
    for (int i = 0; i < (int)bot.data.size(); i++){
        novaData.push_back(bot.data[i]);
    }

    Matrix matice (rows, cols);
    matice.data = novaData;
    return matice;
}

Matrix blkdiag (const Matrix & lhs, const Matrix & rhs)
{
    //cout << "DEBUG: blkdiag(Matrix, Matrix) called, lhs=" << lhs.nrows << "x" << lhs.ncols << " rhs=" << rhs.nrows << "x" << rhs.ncols << endl;
    if (lhs.nrows != lhs.ncols || rhs.nrows != rhs.ncols) throw matrix_bad_sizes();

    if (lhs.nrows == 0) return rhs;
    if (rhs.nrows == 0) return lhs;

    Matrix rhsNull(lhs.nrows, rhs.ncols);
    Matrix lhsNull(rhs.nrows, lhs.ncols);

    Matrix horniCast = horzcat(lhs, rhsNull);
    Matrix spodniCast = horzcat(lhsNull, rhs);
    Matrix matice = vertcat(horniCast, spodniCast);
    return matice;
}

Matrix blkdiag (const value & lhs, const Matrix & rhs) 
{
    Matrix jednoPrvkovaMatice (1, 1);
    jednoPrvkovaMatice.data[0] = lhs;

    Matrix matice = blkdiag(jednoPrvkovaMatice, rhs);
    return matice;
}

Matrix blkdiag (const Matrix & lhs, const value & rhs) 
{
    //cout << "DEBUG: blkdiag(Matrix, value) called, lhs=" << lhs.nrows << "x" << lhs.ncols << " rhs=" << rhs << endl;
    Matrix jednoPrvkovaMatice (1, 1);
    jednoPrvkovaMatice.data[0] = rhs;

    Matrix matice = blkdiag(lhs, jednoPrvkovaMatice);
    return matice;
}

Matrix blkdiag (const value & lhs, const value & rhs) 
{
    Matrix matice(2, 2);
    matice.data = {lhs, 0, 0, rhs};
    return matice;
}

Matrix kronecker(const Matrix &lhs, const Matrix &rhs)
{
    Matrix vyslednaMatice(0, rhs.ncols * lhs.ncols);
    
    for (int r = 0; r < lhs.nrows; r++){
        if (lhs.ncols == 0) continue;
        Matrix spojenyRadek = rhs * lhs.data[r * lhs.ncols + 0];
        for (int c = 1; c < lhs.ncols; c++){
            spojenyRadek = horzcat(spojenyRadek, rhs * lhs.data[r * lhs.ncols + c]);
        }
        vyslednaMatice = vertcat(vyslednaMatice, spojenyRadek);
    }
    return vyslednaMatice;
}

