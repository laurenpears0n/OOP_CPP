// PHYS 30762 Programming in C++
// Assignment 4
// Lauren Pearson
// Simple demonstration of a C++ class
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  std::string name;
  std::string hubble_type;
  double redshift;
  double total_mass;
  double stellar_mass_fraction;
  std::vector<galaxy> satellite_galaxy;

public:
  // Constructors
  galaxy() = default;

  galaxy(std::string galaxy_name, std::string galaxy_hubble_type , double galaxy_redshift , double galaxy_total_mass, double galaxy_stellar_mass_fraction, std::vector<galaxy> galaxy_satellite_galaxy ):
  name{galaxy_name},hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass},
  stellar_mass_fraction{galaxy_stellar_mass_fraction}, satellite_galaxy{galaxy_satellite_galaxy}
  {}

  // Destructor
  ~galaxy() {}

  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() 
  {
    return stellar_mass_fraction * total_mass;
  }

  // Change galaxy's Hubble type
  void change_type(std::string new_type) 
  {
    hubble_type = new_type; 
  }

  // Prototype for function to print out an object's data
  void print_data();

  // Add satellite galaxy
  void add_satellite_galaxy(galaxy satellite)
  {
    satellite_galaxy.push_back(satellite);
  }

  // Overload the operator <<
  friend std::ostream& operator<<(std::ostream& os, const galaxy& satellite_info);

};

  // Print out an object's data

  // Overload the operator <<
  std::ostream& operator<<(std::ostream& os, const galaxy& satellite_info)
  {
    os<< "["<<satellite_info.name<<", "<<satellite_info.hubble_type<<", "<< satellite_info.redshift<<", "<<satellite_info.total_mass<<", "<<satellite_info.stellar_mass_fraction<<"]";
    return os;
  }

  void galaxy::print_data()
  {
    std::cout.precision (3); // 2 significant figures
    std::cout<<"Galaxy: [name, type, z, M, f] = ["<<name<<", "<<hubble_type<<", "<< redshift<<", "<<total_mass<<", "<<stellar_mass_fraction<<"]"<<std::endl;
    std::cout<<"This galaxy has "<<satellite_galaxy.size()<< " satellite(s)  "<<std::endl;
    if (satellite_galaxy.size()>0 ) {
        for(std::vector<galaxy>::iterator it=satellite_galaxy.begin(); it!=satellite_galaxy.end(); ++it) {
        std::cout<<"Satellite galaxy: [name, type, z, M, f] ="<<*it<<std::endl;
        std::cout<<"This satellite galaxy has stellar mass = "<<it->stellar_mass()<<" Solar masses."<<std::endl;
        std::cout<<std::endl;
        }
    } else {
        return;
    }
  }  

// End of class and associated member functions

// Main program
int main()
{
  // Example using default constructor
  galaxy galaxy1; 

  // Example using parameterised constructor
  std::vector<galaxy> no_satellite;
  galaxy galaxy2("Galaxy 2", "Irr", 9.9, 1.09e8, 0.02, no_satellite);
  galaxy galaxy3("Galaxy 3", "Sa", 1.11, 9.63e11, 0.0453, no_satellite);

  std::vector<galaxy> galaxy_data;
  galaxy_data.push_back(galaxy1);
  galaxy_data.push_back(galaxy2);
  galaxy_data.push_back(galaxy3);
  
  // Print out data
  for(auto galaxy_it=galaxy_data.begin(); galaxy_it<galaxy_data.end(); ++galaxy_it)
    {
    galaxy_it->print_data();
    std::cout<<"This galaxy has stellar mass = "<<galaxy_it->stellar_mass()<<" Solar masses."<<std::endl;
    std::cout<<std::endl;
    }

  std::cout<<"Galaxies again after editing: "<<std::endl;

  // Change Hubble type from Irr to S0
  galaxy2.change_type("S0");

  // Add satellite galaxies
  galaxy satellite1("Satellite 1", "E0", 1.11, 1.7e7, 0.0129, no_satellite);
  galaxy satellite2("Satellite 2", "SBc", 1.11, 7.2e10, 0.033, no_satellite);
  galaxy3.add_satellite_galaxy(satellite1);
  galaxy3.add_satellite_galaxy(satellite2);

  // Print edited galaxies again
  std::vector<galaxy> galaxy_data_updated;
  galaxy_data_updated.push_back(galaxy1);
  galaxy_data_updated.push_back(galaxy2);
  galaxy_data_updated.push_back(galaxy3);

  for(auto galaxy_it1=galaxy_data_updated.begin(); galaxy_it1<galaxy_data_updated.end(); ++galaxy_it1)
  {
    galaxy_it1->print_data();
    std::cout<<std::endl;
  }

  return 0;
}