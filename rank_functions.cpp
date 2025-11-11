#include <iostream>
#include <iomanip>
#include "rank_functions.h"

// load data from standard input into a vector
//   input format := <time> <country> <number> <name>
//   examples:
//     32.7 AUS 81 Piastri
//     36.5 NED 1  Verstappen
//   rank should be initialized to 0 for each driver
// returns a vector of drivers, or an empty vector if any input is invalid

std::vector<driver> load_driver_data() {
    std::vector<driver> drivers;

    while (true) {
        double t;
        std::string country;
        int num;

        if (!(std::cin >> t >> country >> num)) {
            break;
        }

        std::string rest;
        std::getline(std::cin, rest);    
        std::string lname = trim(rest);    


        if (lname.empty()) return {};
        if (!(t > 0.0)) return {};
        if (country.size() != 3) return {};
        for (char c : country) {
            if (!(c >= 'A' && c <= 'Z')) return {};
        }

        if (num < 0 || num > 99) return {};
        int letterCount = 0;
        for (char c : lname) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                ++letterCount;
            } else if (c == ' ') {
                // okay
            } else {
                return {};
            }
        }
        if (letterCount < 2) return {};

        driver d;
        d.time     = t;
        d.country  = country;
        d.number   = num;
        d.lastname = lname;
        d.rank     = 0;
        drivers.push_back(d);
    }

    return drivers;
}
std::vector<driver> set_rankings(std::vector<driver> v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        int rank = 1; 
        for (std::size_t j = 0; j < v.size(); ++j) {
            if (v[j].time < v[i].time) {
                rank++;
            }
        }
        v[i].rank = rank;
    }
    return v;
}

std::string trim(std::string s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}


void print_results(const std::vector<driver>& drivers) {
	
	double best_time;
	for (const driver& driver : drivers) {
		if (driver.rank == 1) {
			best_time = driver.time;
			break;
		}
	}

	std::cout << "Final results!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	for(unsigned rank = 1; rank <= drivers.size(); rank++) {
		for(const driver& driver : drivers) {
			if(driver.rank == rank) {
				std::string rank_str = "["+std::to_string(rank)+"]";
				std::cout << std::setw(4) << std::left << rank_str << " " << driver.time << " " << std::setw(15) << std::left << driver.lastname << " (" << driver.country << ") +" << (driver.time - best_time) << std::endl;
			}
		}
	}
}