// Assignment 1
// Lauren Pearson
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<sstream>
#include<limits>

double energy_level_function(double atomic_number, double principle_quantum_number) 
  // calulate the energy of a level given atomic number and principle quantum number
{
  double energy;
  energy = 13.6 * (atomic_number*atomic_number) * (1/(principle_quantum_number*principle_quantum_number));
  return energy;
}

int main()
{
  std::string decision = "y";
  while (decision == "y") 
  { 

    // define variables  
    int atomic_number{0};
    int initial_quantum_number{0};
    int final_quantum_number{0};
    std::string energy_units;
    double delta_energy{0};
    
    // input atomic number
    std::cout<<"Enter atomic number Z: ";
    std::cin >>atomic_number;

    // verify atomic number input validity
    while (atomic_number <= 0 || std::cin.peek() != '\n') {
      std::cout<<"Invalid Input! Please re-enter a positive integer only: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin>>atomic_number;
    }
    
    // input initial principle quantum number
    std::cout<<"Enter initial prinicple quantum number: ";
    std::cin>>initial_quantum_number;

    // verify initial principle quantum number input validity
    while (initial_quantum_number <= 1 || std::cin.peek() != '\n') {
      std::cout<<"Invalid Input! Please re-enter an integer greater than 1: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin>>initial_quantum_number;
    }

    // input final principle quantum number
    std::cout<<"Enter final principle quantum number: ";

    // verify final principle quantum number input validity
    while (true) {
      std::cin>>final_quantum_number;
      while (final_quantum_number<= 0 || std::cin.peek() != '\n') {
          std::cout<<"Invalid Input! Please re-enter an integer greater than 0: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin>>final_quantum_number;
        }

      if (final_quantum_number >= initial_quantum_number ) {
        std::cout<<"Invalid Input! The final principle quantum number must be less than the initial. Please enter a valid final principle quantum number: ";
      } else {
          break;
      }
    }

    // input choice of units and validate
    std::cout<<"Would you like your transition energy in J or eV? Please enter J/eV: ";

    while (energy_units != "eV" && energy_units != "J") {
      std::cin>>energy_units;
      if (energy_units != "eV" && energy_units != "J") {
        std::cout<<"Invalid input! Please type eV or J only (case sensitive): ";
      } else {
          break;
      }
    }

    // convert variables to doubles for calulation purposes
    double atomic_number_calc = atomic_number;
    double inital_quantum_number_calc = initial_quantum_number;
    double final_quantum_number_calc = final_quantum_number;
    
    // calculate energy of required transition in required units
    if (energy_units == "J") {
      delta_energy = (energy_level_function(atomic_number_calc,final_quantum_number_calc) - energy_level_function(atomic_number_calc,inital_quantum_number_calc)) * 1.6e-19;
      std::cout<<"The energy for this transition is "<<std::setprecision(3)<<delta_energy<<energy_units<<"\n"; 
    } else {
        delta_energy = (energy_level_function(atomic_number_calc,final_quantum_number_calc) - energy_level_function (atomic_number_calc,inital_quantum_number_calc));
        std::cout<<"The energy for this transition is "<<std::setprecision(3)<<delta_energy<<energy_units<<"\n";
    }


    // input to recalculate or end program
    std::cout<<"Would you like to find another transition energy? Please enter y/n: ";
    std::cin>>decision;

    if (decision == "n") {
      std::cout<<"Ok, goodbye!";
      break;
    }

    // validate y/n input and recalulate or end program as required
    while (decision != "y" && decision != "n") {
      std::cout<<"Invalid Input! Please enter y/n (case sensitive): ";
      std::cin>>decision;
      
      if (decision == "y") {
      } else if (decision == "n") {
          std::cout<<"Ok, goodbye!";
          break;
      }
    }

  } // end program loop

  return 0;
}
