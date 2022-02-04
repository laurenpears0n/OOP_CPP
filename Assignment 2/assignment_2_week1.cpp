// PHYS 30762 Programming in C++
// Lauren Pearson
// Assignment 2 Week 1

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>


// Functions to compute mean and standard deviation
double mean_function(double sample_size, double grade)
{
  double mean;
  mean = (1/(sample_size)) * grade;
  return mean;
}

double standard_deviation_function(double sample_size, double grade, double mean)
{ 
  double standard_deviation;
  standard_deviation= (1/(sample_size - 1)) * ((grade - mean)*(grade - mean)) ;
  return standard_deviation;
}

// Main function
int main()
{
  // Ask user to enter filename
  std::string data_file = "courselist.dat";

  // Open file and check if successful
  std::ifstream course_stream(data_file);
  if(!course_stream.good ()) {
    // Print error message and exit
    std::cerr <<"Error: file could not be opened"<<std::endl;
    return(1); 
  }

  // Determine number of courses
  int number_courses = 0;
  std::string line;
  std::ifstream file(data_file);
  while (getline(file, line)) {
      number_courses ++;
    }

  file.close();

  // Allocate memory for data
  double *my_data{new double[number_courses]};

  // Read data from file
  course_stream>>my_data[0];
  for(int i=1;i<number_courses;i++) 
    {
    getline(course_stream, line);
    course_stream >> my_data[i] ;
    }

  // Close file
  course_stream.close();

  // Print number of courses read in
  std::cout << "Numbers of courses: " << number_courses << std::endl;

  // Compute mean, standard deviation and standard error of data
  double average = 0;
  for(int i{};i<number_courses;i++)
    {
    average+= mean_function(number_courses, my_data[i]);
    }

  std::cout<<"Mean grade is "<< average << std::endl;

  double standard_dev = 0;
  for(int i{};i<number_courses;i++)
    {
    standard_dev+= standard_deviation_function(number_courses, my_data[i], average);
    }

  std::cout<<"Standard deviation is: "<< sqrt(standard_dev)<< std::endl;

  double standard_error;
  standard_error =  sqrt(standard_dev)/sqrt(number_courses);

  std::cout<<"Standard error is: "<< standard_error<< std::endl;

  // Free memory
  delete[] my_data;

  return 0;
}