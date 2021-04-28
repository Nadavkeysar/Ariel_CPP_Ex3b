#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace ariel {
	class NumberWithUnits {	

		private:
			double number;
			string unit;	
			static double convert(const string& unit1, const string& unit2, double value);
       		static void casting(const string &lhs, const string &rhs);

		public:	
			static void read_units(ifstream& stream);
			NumberWithUnits(double, string const&);
			
			friend ostream& operator<<(ostream& os, const NumberWithUnits& number);
			friend istream& operator>>(istream& stream, NumberWithUnits& num);
			
			NumberWithUnits operator-();
			NumberWithUnits operator--(int); //a-- -prefix
			NumberWithUnits& operator--();    //--a -postfix
			NumberWithUnits& operator -=(NumberWithUnits const& num);
			NumberWithUnits operator-(const NumberWithUnits& num);
			
			NumberWithUnits operator+(const NumberWithUnits& num);
			NumberWithUnits operator+();
			NumberWithUnits& operator +=(const NumberWithUnits& num);
			NumberWithUnits& operator++();    //++a -prefix
			NumberWithUnits operator++(int); //a++ -postfix
			
			friend NumberWithUnits operator*(const double& lhs,const NumberWithUnits& rhs);
			friend NumberWithUnits operator*(const NumberWithUnits& rhs,const double& lhs);
			NumberWithUnits& operator*=(const double& num);

			bool operator <=(NumberWithUnits const& rhs) const;
			bool operator >=(NumberWithUnits const& num) const;
			bool operator>(const NumberWithUnits& num) const;
			bool operator <(NumberWithUnits const& num) const;
			bool operator ==(NumberWithUnits const& rhs) const;
			bool operator !=(NumberWithUnits const& rhs) const;

			double getNumber() const;
			string getUnit();

	
	};
}

