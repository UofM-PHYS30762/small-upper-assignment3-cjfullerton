// PHYS 30762 Programming in C++
// Assignment 3
// Simple demonstration of a C++ class
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class galaxy {
private:
  std::string hubble_type;
  std::vector<std::string> allowed_hubble_type{
      "E0", "E1", "E2", "E3", "E4",  "E5",  "E6",  "E7",
      "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
  double redshift;
  double total_mass;
  double stellar_mass_fraction;
  std::vector<galaxy> satellites;

public:
  // default constructor
  galaxy() {
    hubble_type = "Irr";
    redshift = 0.0;
    total_mass = 1e7;
    stellar_mass_fraction = 0.0;
  }
  // parameterized constructor
  galaxy(std::string type, double z, double M_tot, double f)
      : hubble_type(type), redshift(z), total_mass(M_tot),
        stellar_mass_fraction(f) {
    // If any error is found sets the error variable to its default.
    set_redshift(redshift);
    set_hubble_type(hubble_type);
    set_total_mass(total_mass);
    set_stellar_mass_fraction(stellar_mass_fraction);
  };
  // destructor
  ~galaxy(){};

  // Public member functions
  // Change galaxy's Hubble type
  void change_hubble_type(std::string type) {
    // check if hubble type is defined
    if (std::find(allowed_hubble_type.begin(), allowed_hubble_type.end(),
                  type) != allowed_hubble_type.end()) {
      hubble_type = type;
    } else {
      std::cout << "Hubble type not found! Try again." << std::endl;
    }
  }

  double get_stellar_mass() const { return total_mass * stellar_mass_fraction; }

  // Add satellite galaxy
  void add_satellite(galaxy satellite) { satellites.push_back(satellite); }

  // SETTERS
  void set_redshift(double z) {
    if (redshift < 0.0 || redshift > 10.0) {
      std::cerr
          << "Redshift must be between 0 and 10! Falling Back to default (0.0)."
          << std::endl;
      redshift = 0.0;
    } else {
      redshift = z;
    }
  }
  void set_hubble_type(std::string type) {
    if (!(std::find(allowed_hubble_type.begin(), allowed_hubble_type.end(),
                    type) != allowed_hubble_type.end())) {
      std::cerr << "Wrong Hubble Type! Falling Back to default (Irr)."
                << std::endl;
      hubble_type = "Irr";
    } else {
      hubble_type = type;
    }
  }
  void set_total_mass(double total) {
    if (total < 1e7 || total > 1e12) {
      std::cerr << "Total Mass must be between 1e7 and 1e12! Falling Back to "
                   "default (1e7)."
                << std::endl;
      total_mass = 1e7;
    } else {
      total_mass = total;
    }
  }
  void set_stellar_mass_fraction(double stellar_fraction) {
    if (stellar_fraction < 0.0 || stellar_fraction > 0.05) {
      std::cerr << "Stellar mass fraction must be between 0 and 0.05! Falling "
                   "Back to default (0.0)"
                << std::endl;
      stellar_mass_fraction = 0.0;
    } else {
      stellar_mass_fraction = stellar_fraction;
    }
  }

  // GETTERS
  double get_redshift() { return redshift; }

  std::string get_hubble_type() { return hubble_type; }

  double get_total_mass() { return total_mass; }

  double get_stellar_mass_fraction() { return stellar_mass_fraction; }

  // Prototype for function to print out an object's data
  void print();
};
// Print out an object's data
void galaxy::print() {
  std::cout << "Hubble type: " << hubble_type << std::endl;
  std::cout << "Redshift: " << redshift << std::endl;
  std::cout << "Total mass: " << total_mass << " solar masses" << std::endl;
  std::cout << "Stellar mass fraction: " << stellar_mass_fraction << std::endl;
  std::cout << "Number of satellites: " << satellites.size() << std::endl;
  int count{1};
  if (!satellites.empty()) { // if non-zero satellites
    std::cout << "Satellites:" << std::endl;
    for (std::vector<galaxy>::iterator it = satellites.begin();
         it != satellites.end(); ++it) {
      std::cout << std::endl;
      std::cout << count << ":" << std::endl;
      it->print();
      count++;
    }
  }
}
// End of class and associated member functions

// Main program
int main() {
  // In the following example, galaxies are named from 1 to 7 as test galaxies.
  // Example using default constructor
  galaxy galaxy1;

  // Example using parameterised constructor
  galaxy galaxy2("Irr", 1.2, 5e10, 0.03);

  // declaring wrong values (important: galaxy still defined but with default
  // values instead)
  std::cout << "Demonstration of declaring wrong values for galaxy:"
            << std::endl;
  galaxy galaxy3("ab", 1.2, 5e10, 0.03);
  galaxy galaxy4("S0", 11.2, 5e10, 0.03);
  galaxy galaxy5("S0", 1.2, 5e13, 0.03);
  galaxy galaxy6("S0", 1.2, 5e10, 0.07);
  std::cout << std::endl;
  galaxy galaxy7("ab", 11.2, 5e13, 0.13);
  std::cout << std::endl;

  // print out data
  std::cout << "Demonstration of printing a galaxy:" << std::endl;
  galaxy1.print();
  std::cout << std::endl;
  galaxy2.print();
  std::cout << std::endl;

  // Get and print out stellar mass
  std::cout << "Demonstration of printing a galaxy stellar mass:" << std::endl;
  std::cout << galaxy2.get_stellar_mass() << std::endl;
  std::cout << std::endl;

  // Change Hubble type from Irr to S0
  std::cout << "Demonstration of changing Hubble type to a wrong value, then "
               "to a correct value:"
            << std::endl;
  galaxy2.change_hubble_type("S0a");
  galaxy2.change_hubble_type("S0");
  std::cout << std::endl;

  galaxy2.print();
  std::cout << std::endl;

  // Add satellite galaxies
  std::cout << "Demonstration of Adding Satellite Galaxies and printing them:"
            << std::endl;
  galaxy2.add_satellite(galaxy1);
  galaxy2.add_satellite(galaxy3);
  galaxy2.print();
  std::cout << std::endl;

  // vector of two classes of sufficient complexities
  std::cout << "Demonstration of Vector of Galaxies and Iterator:" << std::endl;
  std::vector<galaxy> galaxies = {galaxy1, galaxy2};

  for (std::vector<galaxy>::iterator it = galaxies.begin();
       it != galaxies.end(); ++it) {
    it->print();
    std::cout << std::endl;
  }
  return 0;
}