// PHYS 30762 Programming in C++
// Lauren Pearson
// Assignment 2 Week 2

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<algorithm>

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
    int number_courses;

    // Ask user to enter filename
    std::string data_file = "courselist.dat";

    // Open file and check if successful
    std::fstream course_stream(data_file);
    if(!course_stream.good ()) {
        // Print error message and exit;
        std::cerr <<"Error: file could not be opened"<<std::endl;
        return(1); 
    }

    // Allocate memory for data 
    std::vector<std::string> data;
    std::vector<std::string> courses;
    std::vector<std::string> grades;
    std::vector<std::string> titles; 
    std::vector<int> codes;
    std::vector<std::pair<int, std::string>> name_sort_pairs;
    std::vector<std::string> ordered_courses;
    std::vector<std::string> year_grades;
    std::vector<std::string> year_ordered_courses;

    // Read data from file
    std::string line;
    while(std::getline(course_stream, line)) 
    {
        data.push_back(line);
    }

    // Close file
    course_stream.close();

    // Print number of courses read in
    number_courses = data.size();
    std::cout<<"Number of courses: "<<number_courses<<std::endl;

    // Separate grades from course code and title
    for(int i{};i<number_courses;i++) {
        std::istringstream ss(data[i]);
        std::string grade_string;
        ss>>grade_string;
        courses.push_back(data[i].substr(grade_string.length()+1)); 
        grades.push_back(grade_string);
    }

    // Separate course code from title and make vector pair of the two for sorting
    for(int i{};i<number_courses;i++) {
        std::istringstream ss(courses[i]);
        std::string code_string;
        ss>>code_string;
        titles.push_back(courses[i].substr(code_string.length()+2)); 
        codes.push_back(std::stoi(code_string));
        name_sort_pairs.push_back(std::make_pair(codes[i], titles[i]));
    }

    // Ask for sorting by year or course name
    std::string order;
    std::cout<<"Would you like the course list sorted by year or course name? Please enter year/name: ";
    std::cin>>order;

    // Sort by year or course and print out full list
    if (order == "year") {
        std::cout<<"Course list by year: "<<std::endl;
        std::sort(name_sort_pairs.begin(), name_sort_pairs.end(), [](const std::pair<int,std::string> &a,const std::pair<int,std::string> &b)
        { return a.first<b.first; });
        
        ordered_courses.clear();
        for (int i{};i<number_courses;i++) {
            ordered_courses.push_back(std::to_string(name_sort_pairs[i].first) + name_sort_pairs[i].second);
        }
        for(std::vector<std::string>::iterator it=courses.begin(); it!=courses.end(); ++it) {
            std::cout<<"PHYS"<<*it<<std::endl;
        }
    } else if (order=="name") {
        std::cout<<"Course list by name: "<<std::endl;
        std::sort(name_sort_pairs.begin(), name_sort_pairs.end(), [](const std::pair<int,std::string> &a,const std::pair<int,std::string> &b)
        { return a.second<b.second; });
        ordered_courses.clear();
        
        for (int i{};i<number_courses;i++) {
            ordered_courses.push_back(std::to_string(name_sort_pairs[i].first) + name_sort_pairs[i].second);
        }
        for(std::vector<std::string>::iterator it=ordered_courses.begin(); it!=ordered_courses.end(); ++it) {
            std::cout<<"PHYS"<<*it <<std::endl;
        }  
    } else { 
        return 0;
    }
    
    // Ask for statistics on specific year or for all courses
    std::string year;
    std::cout<<"Which year would you like the mean, standard deviation and standard error for? Please enter 1/2/3/4/all: ";
    std::cin>>year;


    // Create list of grades for data set specified
    // If specific year selected, print out new smaller list, sorted in same way as first specified
    if (year == "all") {
        for(int i{};i<number_courses;i++) {
            year_grades.push_back(grades[i]);
        }    
    } else {
        for(int i{};i<number_courses;i++) {
            if (courses[i].substr(0,1)==year) {
                year_ordered_courses.push_back(courses[i]);
                year_grades.push_back(grades[i]);
            }
        }

        if (order!="year") {
            titles.clear();
            codes.clear();
            name_sort_pairs.clear();
            for(int i{};i<year_ordered_courses.size();i++) {    
                std::istringstream ss(year_ordered_courses[i]);
                std::string code_string;
                ss>>code_string;
                titles.push_back(year_ordered_courses[i].substr(code_string.length()+2)); 
                codes.push_back(std::stoi(code_string));
                name_sort_pairs.push_back(std::make_pair(codes[i], titles[i])); 
                }
            std::sort(name_sort_pairs.begin(), name_sort_pairs.end(), [](const std::pair<int,std::string> &a, const std::pair<int,std::string> &b)
            { return a.second<b.second; });
            ordered_courses.clear();
            
            for (int i{};i<year_ordered_courses.size();i++) {
            ordered_courses.push_back(std::to_string(name_sort_pairs[i].first) + name_sort_pairs[i].second);
            }
            for(std::vector<std::string>::iterator it=ordered_courses.begin(); it!=ordered_courses.end(); ++it) {
            std::cout<<"PHYS"<<*it <<std::endl;
            }
        } else {
            for(std::vector<std::string>::iterator it=year_ordered_courses.begin(); it!=year_ordered_courses.end(); ++it) {
                std::cout<<"PHYS"<<*it<<std::endl;
            }
        }
    }

    //Calulate mean, standard deviation and standard error for list of data specified and print
    double mean=0;
    for(int i{};i<year_grades.size();i++) {
        std::istringstream ss(year_grades[i]);
        double d;
        ss>>d;
        mean += mean_function(year_grades.size(), d);
    }
    std::cout<<"Mean is: "<<mean<<std::endl;

    double std_dev=0;
    for(int i{};i<year_grades.size();i++) {
        std::istringstream ss(year_grades[i]);
        double d;
        ss>>d;
        std_dev += standard_deviation_function(year_grades.size(), d, mean);
    }
    std::cout<<"Standard deviation is: "<< sqrt(std_dev)<< std::endl;

    double std_error;
    std_error = sqrt(std_dev/year_grades.size());
    std::cout<<"Standard error is: "<<std_error<<std::endl;

    // Free memory
    data.clear();
    courses.clear();
    grades.clear();
    titles.clear(); 
    codes.clear();
    name_sort_pairs.clear();
    ordered_courses.clear();
    year_grades.clear();
    year_ordered_courses.clear();

    return 0;
}