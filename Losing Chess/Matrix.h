//
// DD1388 - Lab 2: The matrix
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
using namespace std;

template <typename T>
class Matrix {

    // Assert Matrix is move-constructible and move-assignable
    static_assert(std::is_move_constructible<T>::value,"T must be move-constructible");
    static_assert(std::is_move_assignable<T>::value,"T must be move-assignable");

public:
    // constructors and assignment operators
    /* TODO: Make the appropriate constructor(s) explicit */
    explicit Matrix();
    explicit Matrix(size_t dim);
    explicit Matrix(size_t rows, size_t cols);
    explicit Matrix(const std::initializer_list<T> & list);
    Matrix(Matrix<T> & other);
    explicit Matrix(Matrix<T> && other) noexcept;

    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix<T> & operator=(Matrix<T> && other) noexcept;
    bool operator==(const Matrix<T>& other);

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);
    

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;  //Contains number of elements in the matrix
    T * m_vec;
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m);

// functions
template<typename T>
Matrix<T> identity(size_t dim);


//
// Implementations
//

template<typename T> // Make empty matrix
Matrix<T>::Matrix() : m_rows(0), m_cols(0), m_capacity(0){
    m_vec = nullptr;
}

template<typename T>
Matrix<T>::Matrix(size_t dim) : m_rows(dim), m_cols(dim), m_capacity(dim*dim){// Make nxn matrix
    m_vec = new T[m_capacity]{};
}

template<typename T> // Make nxm matrix
Matrix<T>::Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_capacity(rows*cols){ 
    m_vec = new T[m_capacity]{};
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
/*:  Initialize members here */ {
    int sr = sqrt(list.size());
    if(sr*sr == list.size()){
        m_rows = sr; 
        m_cols = sr;
        m_capacity = sr*sr;
        m_vec = new T[m_capacity];
        for (int i=0; i<m_capacity; i++){
            m_vec[i] = list.begin()[i];
        }
    }
    else{
        throw std::out_of_range("Insert square matrices only");
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> & other) {   //Copy constructor
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = new T[other.m_capacity]{};
    for(int i = 0; i < other.m_capacity; i++){
        m_vec[i] = other.m_vec[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept  //Move constructor
    : m_rows(other.m_rows), 
    m_cols(other.m_cols),
    m_capacity(other.m_capacity){   
    m_vec = other.m_vec;

    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
    other.m_vec = nullptr;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) { //Copy assignment
    if (this!=&other){
        delete[] m_vec; // Prevent memory leak
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;
        m_vec = new T[m_capacity]{};
        for (int i = 0; i < other.m_capacity; i++){
            m_vec[i] = other.m_vec[i];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept { // Move assignment
    if (this!=&other){
        delete[] m_vec; // Prevent memory leak
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;
        m_vec = other.m_vec;
        
        other.m_vec = nullptr; // Prevent memory leak
        other.m_rows = 0;
        other.m_cols = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other){
    for(int i=0; i < m_rows; i++){
        for(int j=0; j < m_cols; j++)
            if(m_vec[m_cols*i+j]!=other.m_vec[m_cols*i+j]){
                return false;
            }
    }
    return true;
}

template<typename T>
Matrix<T>::~Matrix() {  // Destructor
    delete[] m_vec; // Delete whole array
}

template<typename T>
size_t Matrix<T>::rows() const {    // Return number of rows
    return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {    // Return number of columns
    return m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) { // Return element in Matrix[row,col], allows to be written over
    return m_vec[m_cols*row+col];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const { // Return element in Matrix[row,col], read-only
    return m_vec[m_cols*row+col];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const { // return new Matrix after doing matrix multiplication
    if (m_cols == other.m_rows){
        Matrix<T> m_prod(m_rows,other.m_cols);
        for(int i = 0; i < m_rows; i++){
            for (int j=0; j < other.m_cols; j++){
                for(int k=0; k < m_cols; k++){
                    m_prod.m_vec[m_cols*i+j] += m_vec[m_cols*i+k] * other.m_vec[other.m_cols*k+j];
                }
            }
        }
        return m_prod;
    }
    else{
        throw std::out_of_range("The matrices must have correct dimensions for matrix multiplication");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const { // return new Matrix after doing matrix addition
    if(m_rows == other.m_rows && m_cols == other.m_cols){
        Matrix<T> m_sum(m_rows,m_cols);
        for(int i = 0; i < m_capacity; i++){
            m_sum.m_vec[i] = m_vec[i] + other.m_vec[i];
        }
        return m_sum;
    }
    else{
        throw std::out_of_range("The matrices must have the same dimensions");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const { // return new Matrix after doing matrix subtraction
    if(m_rows == other.m_rows && m_cols == other.m_cols){
        Matrix<T> m_sum(m_rows,m_cols);
        for(int i = 0; i < m_capacity; i++){
            m_sum.m_vec[i] = m_vec[i] - other.m_vec[i];
        }
        return m_sum;
    }
    else{
        throw std::out_of_range("The matrices must have the same dimensions");
    }
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) { // Matrix multiplication but no return
    *this = *this * other;
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    if(m_rows == other.m_rows && m_cols == other.m_cols){
        for (int i=0; i < m_capacity; i++){
            m_vec[i] += other.m_vec[i];
        }
    }
    else{
        throw std::out_of_range("The matrices must have the same dimensions");
    }
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    if(m_rows == other.m_rows && m_cols == other.m_cols){
        for (int i=0; i < m_capacity; i++){
            m_vec[i] -= other.m_vec[i];
        }
    }
    else{
        throw std::out_of_range("The matrices must have the same dimensions");
    }
}

template<typename T>
void Matrix<T>::reset() {
    // Implementation goes here
    delete[] m_vec; // Delete each row
    m_vec = new T[m_capacity]{};
}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    // Implementation goes here
    if (row<=(m_rows-1)){
        Matrix<T> tempMatrix(m_rows+1,m_cols);
        for (int i = 0; i < m_rows+1; i++){
            for (int j = 0; j < m_cols; j++){
                if(i < row){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                else if(i==row){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = T{};
                }
                else if(i > row){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*(i-1)+j];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given row is out of range. First row is row = 0");
    }
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    // Implementation goes here
    if (row<=(m_rows-1)){
        Matrix<T> tempMatrix(m_rows+1,m_cols);

        for (int i = 0; i < m_rows+1; i++){
            for (int j = 0; j < m_cols; j++){
                if(i <= row){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                else if(i==row+1){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = T{};
                }
                else if(i > row+1){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*(i-1)+j];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given row is out of range. First row is row = 0");
    }
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    // Implementation goes here
    if (row<=(m_rows-1)){
        Matrix<T> tempMatrix(m_rows-1,m_cols);

        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                if(i < row){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                else if(i > row){
                    tempMatrix.m_vec[tempMatrix.m_cols*(i-1)+j] = m_vec[m_cols*i+j];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given row is out of range. First row is row = 0");
    }
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    // Implementation goes here
    if (col<=(m_cols-1)){
        Matrix<T> tempMatrix(m_rows,m_cols+1);

        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols+1; j++){
                if(j < col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                else if(j==col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = T{};
                }
                else if(j > col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+(j-1)];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given column is out of range. First column is column = 0");
    }
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    if (col<=(m_cols-1)){
        Matrix<T> tempMatrix(m_rows,m_cols+1);

        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols+1; j++){
                if(j <= col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                else if(j==col+1){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = T{};
                }
                else if(j > col+1){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+(j-1)];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given column is out of range. First column is column = 0");
    }
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    // Implementation goes here
    if (col<=(m_cols-1)){
        Matrix<T> tempMatrix(m_rows,m_cols-1);

        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                if(j < col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+j] = m_vec[m_cols*i+j];
                }
                if(j > col){
                    tempMatrix.m_vec[tempMatrix.m_cols*i+(j-1)] = m_vec[m_cols*i+j];
                }
            }
        }
        *this = tempMatrix;
    }
    else{
        throw std::out_of_range("Given column is out of range. First column is column = 0");
    }
    
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return &m_vec[0];
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    return &m_vec[m_capacity-1];
}

template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    // Implementation goes here
    std::string matrixRow;
    int columns = 0;
    int rows = 0;
    std::vector<T> elementVector;

    while(getline(is,matrixRow)){
        rows += 1;
        matrixRow.erase(remove(matrixRow.begin(), matrixRow.end(), '['), matrixRow.end());
        matrixRow.erase(remove(matrixRow.begin(), matrixRow.end(), '\n'), matrixRow.end());
        matrixRow.erase(remove(matrixRow.begin(), matrixRow.end(), ']'), matrixRow.end());
        std::stringstream ss(matrixRow);

        if (rows==1){
            columns = std::distance(matrixRow.begin(),matrixRow.end()); //Counts columns
        }
        T element;
        while(ss >> element){
            elementVector.push_back(element);   //Appends element
        }
    }

    Matrix<T> tempMatrix(rows,columns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j< columns; j++){
            tempMatrix(i,j) = elementVector[columns*i + j];
        }
    }
    m = tempMatrix;
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    // Implementation goes here
    os << "[";
    for(int i=0; i<m.rows(); i++){
        for(int j=0; j<m.cols(); j++){
            if(j!=(m.cols()-1)){
                os << m(i,j) << " ";
            }
            else{
                os << m(i,j);
            }
        }
        if(i!=(m.rows()-1)){
            os << endl << " ";
        }
        else{
            os << "]" << endl;
        }
    }
    return os;
}

template<typename T>
Matrix<T> identity(size_t dim){
    Matrix<T> identityMatrix(dim);
    for (int i=0; i<dim; i++){
        identityMatrix(i,i) = 1;
    }
    return identityMatrix;
}



#endif //MATRIX_H