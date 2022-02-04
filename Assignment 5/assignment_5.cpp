// PHYS 30762 Programming in C++
// Assignment 5
// Lauren Pearson

// Class for matrices

#include<iostream>
#include<cmath>


class matrix
{
    // Friend functions to overload input and output
    friend std::ostream & operator<<(std::ostream &os, matrix &a);
    friend std::istream & operator>>(std::istream &is, matrix &a);

private:
    int rows, columns;
    double *data;
    int size = rows*columns;
    
public:
    // Constructors and destructor
    matrix() = default;

    matrix(const int number_rows, const int number_columns, double matrix_data[]) :
        rows{number_rows}, columns{number_columns}, data{new double[size]}
        {
            for(int i{}; i<size; i++){
            data[i]=matrix_data[i];
            }
        }

    ~matrix() 
    {
        delete[] data;
    }

    // Overload assignment operator for deep copying
    matrix operator=(matrix &a)
    {
        if(&a == this){
            return *this;
        }
        delete[] data; 
        data=nullptr; 
        size=0;
        rows=a.rows;
        columns=a.columns;
        size=a.rows*a.columns;
        if(size>0) {
            data=new double[size];
            for(int i{};i<size;i++) 
            {
                data[i] = a.data[i];
            }
        }
        return *this;
    }

    // Copy constructor for deep copying
    matrix(matrix &a)
    {
        data = nullptr;
        rows = a.rows;
        columns = a.columns;
        size=a.size;
        data=new double[size];
        for(int i{};i<size;i++) 
        {
            data[i] = a.data[i];
        }
    }

    // Move assignment
    matrix& operator=(matrix&& a)
    {
        std::swap(rows,a.rows);
        std::swap(columns,a.columns);
        std::swap(size,a.size);
        std::swap(data,a.data);
        return *this;
    }

    // Move constructor
    matrix(matrix&& a)
    {
        size=a.size;
        data=a.data;
        rows=a.rows;
        columns=a.columns;
        a.rows=0;
        a.columns=0;
        a.size=0;
        a.data=nullptr;
    }

    // Overload + operator for addition of matrices
    matrix operator+(matrix &a)
    {
        matrix add_matrix{};
        if (rows != a.rows && columns != a.columns) {
            std::cout<<"Cannot perform addition as matrices have different dimension. "<<std::endl;
        } else {
            add_matrix.rows = a.rows;
            add_matrix.columns = a.columns;
            add_matrix.size = a.size;
            add_matrix.data = new double[a.size];
            for (int i{}; i<a.size; i++)
            {
                add_matrix.data[i]=data[i]+a.data[i]; 
            }
        }
        return add_matrix;
    }

    // Overload - operator for subtraction of matrices
    matrix operator-(matrix &a)
    {
        matrix subtract_matrix{};
        if (rows != a.rows && columns != a.columns) {
            std::cout<<"Cannot perform subtraction as matrices have different dimension. "<<std::endl;
        } else {
            subtract_matrix.rows = a.rows;
            subtract_matrix.columns = a.columns;
            subtract_matrix.size = a.size;
            subtract_matrix.data = new double[a.size];
            for (int i{}; i<a.size; i++)
            {
                subtract_matrix.data[i]=data[i]-a.data[i]; 
            }
        }
        return subtract_matrix;
    }

    // Overload * operator for multiplication of matrices
    matrix operator*(matrix &a)
    {
        matrix multiply_matrix{};
        if (rows != a.columns) {
            std::cout<<"Cannot perform multiplication as matrices have incompatible dimension. "<<std::endl;
        } else {
            multiply_matrix.rows = rows;
            multiply_matrix.columns = a.columns;
            multiply_matrix.size = rows*a.columns;
            multiply_matrix.data = new double[multiply_matrix.size];
                for(int i{}; i<rows; i++)
                {
                    for (int j{}; j<a.columns; j++)
                    {
                        multiply_matrix.data[i*a.columns + j] = 0;
                        for(int k{}; k<a.columns; k++) 
                        {
                        multiply_matrix.data[i*a.columns + j] += (data[i*a.columns + k]*a.data[k*a.columns + j]);
                        }
                    }
                }  
            } 
        return multiply_matrix;
    }

    // Return matrix with row i and column j deleted
    matrix delete_i_j(int delete_row, int delete_column)
    {
        matrix deleted_matrix{};
        deleted_matrix.rows = rows-1;
        deleted_matrix.columns = columns-1;
        deleted_matrix.size = deleted_matrix.rows*deleted_matrix.columns;       
        deleted_matrix.data = new double[deleted_matrix.size];

        int k = 0; 
        for (int i{}; i<rows; i++)
        {
            for (int j{}; j<columns; j++)
             {
                if (i != delete_row-1 && j != delete_column-1) {                                    
                {                        
                    deleted_matrix.data[k] = data[i*columns + j];
                    k ++;
                }
            }
            }
        }
        return deleted_matrix;
    }

    // Return determinant of matrix
    double determinant() 
    {
        double det=0.0;
        if (rows != columns) {
            std::cout<<"Cannot calulate determinant of non-square matrix"<<std::endl;
            return 0;
        } else {
        if (size == 4) {
            det += data[0]*data[3] - data[1]*data[2];
        } else {
            int i=1;
            for (int j{}; j<columns; j++)
            {
                det += pow(-1, i+1+j+1) * data[i*columns + j] * delete_i_j(i+1,j+1).determinant();
            }
        }
        return det;
        }
    }

};

// Overload << operator to output matrix in useful format
std::ostream& operator<<(std::ostream& os, matrix &a)
{
    for(int i{};i<a.rows;i++)
        {
        os<<"[";
        for(int j{}; j<a.columns; j++)
        {
            os<<" "<<a.data[(i*a.columns) + j]<<" ";
        }
        os<<"]"<<std::endl;
    }
    return os;
}

// Overload >> operator to input matrix data one element at a time
std::istream& operator>>(std::istream& is, matrix &a)
{
    std::cout<<"Number of rows = ";
    is>>a.rows;
    std::cout<<"Number of columns = ";
    is>>a.columns;
    a.size = a.rows*a.columns;
    a.data = new double[a.size];
    for(int i{}; i<a.rows; i++) {
        for(int j{};j<a.columns; j++) {
            std::cout<<"Enter element A_"<<i+1<<j+1<<": ";
            is>>a.data[(i)*a.columns+(j)];
        }
    }
    return is;
}

int main ()
{
    double empty_elements[4] = {0,0,0,0};
    double matrix_elements_1[4] = {23,1,-89,6};
    double matrix_elements_2[4] = {72,-13,4,9};
    double matrix_elements_3[4] = {-52,-7,42,65};
    double matrix_elements_4[9] = {12,65,-7,-56,2,0,17,22,-55};

    matrix matrix_1{2,2,matrix_elements_1};
    matrix matrix_2{2,2,matrix_elements_2};
    
    std::cout<<"Example Matrix 1: "<<std::endl<<matrix_1;
    std::cout<<"Example Matrix 2: "<<std::endl<<matrix_2<<std::endl;

    matrix matrix_3{};
    matrix_3 = matrix_2;
    std::cout<<"Setting new matrix, Matrix 3 = Matrix 2 using overloaded assignment operator: "<<std::endl;
    std::cout<<"Matrix 3: "<<std::endl<<matrix_3<<"Matrix 2 (unchanged): "<<std::endl<<matrix_2<<std::endl;

    matrix_1=matrix_1;
    std::cout<<"Self assigning Matrix 1 to Matrix 1: "<<std::endl;
    std::cout<<"Matrix 1: "<<std::endl<<matrix_1<<std::endl;;
    
    matrix matrix_4(matrix_1);
    std::cout<<"Using copy constructor to make create new matrix, Matrix 4 from Matrix 1: "<<std::endl;
    std::cout<<"Matrix 4: "<<std::endl<<matrix_4<<"Matrix 1 (unchanged): "<<std::endl<<matrix_1<<std::endl;

    matrix matrix_5(std::move(matrix_1));
    std::cout<<"Using move constructor to move data from Matrix 1 to new matrix, Matrix 5:"<<std::endl;
    std::cout<<"Matrix 5: "<<std::endl<<matrix_5<<"Matrix 1: "<<std::endl<<matrix_1<<std::endl;

    matrix matrix_6{2,2,empty_elements};
    matrix_6 = std::move(matrix_2);
    std::cout<<"Using move assignment operator to move data from Matrix 2 to new matrix, Matrix 6:"<<std::endl;
    std::cout<<"Matrix 6: "<<std::endl<<matrix_6<<"Matrix 2: "<<std::endl<<matrix_2<<std::endl;

    matrix matrix_add(matrix_5+matrix_6);
    std::cout<<"Matrix 5 + Matrix 6 = "<<std::endl<<matrix_add<<std::endl;

    matrix matrix_sub(matrix_5-matrix_6);
    std::cout<<"Matrix 5 - Matrix 6 = "<<std::endl<<matrix_sub<<std::endl;

    matrix matrix_multi(matrix_5*matrix_6);
    std::cout<<"Matrix 5 * Matrix 6 = "<<std::endl<<matrix_multi<<std::endl;

    matrix matrix_8{3,3,matrix_elements_4};
    std::cout<<"Matrix 8, for demonstrating delete row i and column j: "<<std::endl<<matrix_8;
    int delete_row;
    int delete_column;
    std::cout<<"Which row would you like to delete? Enter i: ";
    std::cin>>delete_row;
    std::cout<<"Which column would you like to delete? Enter j: ";
    std::cin>>delete_column;
    matrix matrix_deleted(matrix_8.delete_i_j(delete_row, delete_column));
    std::cout<<"Matrix 8 with row "<<delete_row<<" and column "<<delete_column<< " deleted: "<<std::endl<<matrix_deleted<<std::endl;

    std::cout<<"Demonstration of determinant calulations: "<<std::endl;
    std::cout<<"(2x2) Determinant of Matrix 6 = "<<matrix_6.determinant()<<std::endl;
    std::cout<<"(3x3) Determinant of Matrix 8 = "<<matrix_8.determinant()<<std::endl<<std::endl;

    matrix matrix_10{};
    std::cout<<"Input your own matrix A: "<<std::endl;
    std::cin>>matrix_10;
    std::cout<<"Your matrix is: "<<std::endl<<matrix_10<<std::endl;
    std::string decision;
    std::cout<<"Would you like to calulate the determinant of your matrix? Enter y/n: ";
    std::cin>>decision;
    if (decision == "y"){
        double determinent;
        determinent = matrix_10.determinant();
        if (determinent !=0) {
            std::cout<<"The determinent is: "<<determinent<<std::endl;
        }

    } else{
        std::cout<<std::endl;
    }

    std::cout<<"Example of multiplication with dimension error (3x3 * 2x2): "<<std::endl;
    std::cout<<"Matrix 8 * Matrix 5 = "<<std::endl;
    matrix matrix_err(matrix_8*matrix_5);

    return 0;
}