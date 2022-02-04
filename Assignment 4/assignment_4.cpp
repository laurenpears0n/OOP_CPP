// PHYS 30762 Programming in C++
// Assignment 5
// Lauren Pearson

// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
  friend std::ostream & operator<<(std::ostream &os, const complex &z);
  friend std::istream & operator>>(std::istream &is, complex &z);

private:

  double re,im;

public:

  // Constructors & destructor
  complex()
  {
    re=im=0;
  }

  complex(const double real_part, const double im_part)
  {
    re=real_part; 
    im=im_part;
  }
  
  ~complex(){}

  // Return real component
  double real_component() const
  {
    return re;
  }

  // Return imaginary component
  double imaginary_component() const
  {
    return im;
  }

  // Return modulus
  double modulus() const
  {
    return sqrt(re*re + im*im);
  }

  // Return argument
  double argument() const
  {
    return atan(im/re);
  }

  // Return complex conjugate
  complex complex_conj() const
  {
    return complex(re,-im);
  }

  // Overload + operator for addition 
  complex operator+(const complex& z) const
  {
    return complex(re + z.re, im + z.im);
  }

  // Overload - operator for subtraction
  complex operator-(const complex& z) const
  {
    return complex(re - z.re, im - z.im);
  }

  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex& z) const
  {
    return complex((re*z.re)-(im*z.im), (re*z.im)+(im*z.re));
  }

  // Overload / operator for division, z1/z2
  complex operator /(const complex& z) const
  {
    return complex(((re*z.re)+(im*z.im))/((z.re*z.re)+(z.im*z.im)), ((im*z.re)-(re*z.im))/((z.re*z.re)+(z.im*z.im)));
  }

};

// Function to overload << operator for complex numbers
std::ostream& operator<<(std::ostream& os, const complex& z)
  {
    if (z.im>=0) {
    os<< z.re << "+" << z.im<<"i";
    return os;
    } else {
    os<< z.re << z.im<<"i";
    return os;   
    }
  }    

  std::istream& operator>>(std::istream& is, complex& z)
  {
    is>>z.re>>z.im;
    return is;
  }  

int main()
{  
  std::cout.precision(3);

  // Create two complex numbers
  complex a{3,4};
  complex b{1,-2};

 // Get real and imaginary components, modulus and argument
  double real_a = a.real_component();
  double real_b = b.real_component();
  double im_a = a.imaginary_component();
  double im_b = b.imaginary_component();
  double mod_a = a.modulus();
  double mod_b = b.modulus();
  double arg_a = a.argument();
  double arg_b = b.argument();

  // Get conjugates
  complex conj_a = a.complex_conj();
  complex conj_b = b.complex_conj();

  // Get sum, difference, product and quotient of a and b
  complex sum=a+b;
  complex difference=a-b;
  complex product=a*b;
  complex quotient=a/b;

  // Print out results, also demonstrating use of overloaded operator<<
  std::cout<<"a = "<<a<<std::endl;
  std::cout<<"b = "<<b<<std::endl;
  std::cout<<"Real part of a = "<< real_a<<std::endl;
  std::cout<<"Real part of b = "<< real_b<<std::endl;
  std::cout<<"Complex part of a = "<< im_a<<std::endl;
  std::cout<<"Complex part of b = "<< im_b<<std::endl;
  std::cout<<"Modulus of a = "<< mod_a<<std::endl;
  std::cout<<"Modulus of b = "<< mod_b<<std::endl;
  std::cout<<"Argument of a = "<< arg_a<<std::endl;
  std::cout<<"Argument of b = "<< arg_b<<std::endl;
  std::cout<<"Complex conjugate of a = "<< conj_a<<std::endl;
  std::cout<<"Complex conjugate of b = "<< conj_b<<std::endl;

  // Show results of overloading arithmetic operators
  std::cout<<"a + b = "<<sum<<std::endl;
  std::cout<<"a - b = "<<difference<<std::endl;
  std::cout<<"a * b = "<<product<<std::endl;
  std::cout<<"a / b = "<<quotient<<std::endl;

  // Challenge 
  // Allow user input of complex number ans extract real and imaginary parts
  complex input{};
  std::cout<<"Enter complex number in the form a+bi or a-bi: ";
  std::cin>>input;
  std::cout<<"Your complex number = "<<input<<std::endl;
  std::cout<<"Real part of your input = "<<input.real_component()<<std::endl;
  std::cout<<"Imaginary part of your input = "<<input.imaginary_component()<<std::endl;

  return 0;
}