#include "NumberWithUnits.hpp"
namespace ariel {
	const double EPS = 0.001;
	static map<string,map<string, double>> unitsConverts;

	NumberWithUnits::NumberWithUnits(double num, string const& unitInput){
        if (unitsConverts.find(unitInput) == unitsConverts.end())
        {
            throw "Invalid unit";
        }
			this->number = num;
           	this->unit = unitInput;    
    }

	 void NumberWithUnits::casting(const string &lhs, const string &rhs)
    {
        for (auto &cas : unitsConverts[lhs])
        {
            double cast = unitsConverts[rhs][lhs] * cas.second;
            unitsConverts[rhs][cas.first] = cast;
            unitsConverts[cas.first][rhs] = 1 / cast;
        }
		for (auto &cas : unitsConverts[rhs])
        {
            double cast = unitsConverts[lhs][rhs] * cas.second;
            unitsConverts[lhs][cas.first] = cast;
            unitsConverts[cas.first][lhs] = 1 / cast;
        }
    }

	void NumberWithUnits::read_units(ifstream& stream)
	{
        double num1=0,num2 = 0;
        string unit1, unit2, equal;
        while (!stream.eof())
        {
            stream >> num1 >> unit1 >> equal>> num2 >> unit2;
            unitsConverts[unit1][unit2] = num2;
            unitsConverts[unit2][unit1] = num1 / num2;
            casting(unit1, unit2);
        }
    }

	double NumberWithUnits::convert(const string& unit1, const string& unit2, double val)
    {
        if (unit1 == unit2)
        {
            return val;
        }

        if (unitsConverts[unit2].find(unit1) == unitsConverts[unit2].end())
        {
            throw "Error the numbers are diffrent type";
        }
        return (val * unitsConverts[unit2][unit1]); //unit2 -> unit1
    }

	 NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
    {
        double add = NumberWithUnits::convert(this->unit, num.unit, num.number);
        double sum = this->number + add;
        return NumberWithUnits(sum, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        *this = *this + num;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
		NumberWithUnits num(+(this->number), this->unit);
        return num;
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->number);
        return *this;
    }
	
    NumberWithUnits NumberWithUnits::operator++(int)
    {
		NumberWithUnits num(this->number, this->unit);
        ++(this->number);
        return num;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
    {
        double sub = NumberWithUnits::convert(this->unit, num.unit, num.number);
        double sum = this->number - sub;
        return NumberWithUnits(sum, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        *this = *this - num;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
		NumberWithUnits num(-(this->number), this->unit);
        return num;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
		NumberWithUnits num(this->number, this->unit);
        --(this->number);
        return num;
    }

    NumberWithUnits operator*(const double& lhs,const NumberWithUnits& rhs)
    {
        return NumberWithUnits(lhs * rhs.number, rhs.unit);
    }

    NumberWithUnits operator*(const NumberWithUnits& rhs,const double& lhs)
    {
        return NumberWithUnits(lhs * rhs.number, rhs.unit);
    }

    NumberWithUnits &NumberWithUnits::operator*=(const double &num)
    {
        this->number *= num;
        return *this;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &num) const
    {
        double result = NumberWithUnits::convert(this->unit, num.unit, num.number);
		return (result - this->number) > EPS;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &rhs) const
    {
        double result = NumberWithUnits::convert(this->unit, rhs.unit, rhs.number);
        if (abs(result - this->number) <= EPS) 
        {
            return true;
        }
			return (result - this->number) > EPS;
    }
	
    bool NumberWithUnits::operator>(const NumberWithUnits &num) const
    {
        double result = NumberWithUnits::convert(this->unit, num.unit, num.number);
		return(this->number- result) > EPS;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        double result = NumberWithUnits::convert(this->unit, num.unit, num.number);
        if (abs(result - this->number) <= EPS)
        {
            return true;
        }
			return (this->number - result) > EPS;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &rhs) const
    {
		double result = NumberWithUnits::convert(this->unit, rhs.unit, rhs.number);
        return abs(result - this->number) <= EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &rhs) const
    {
		double result = NumberWithUnits::convert(this->unit, rhs.unit, rhs.number);
    	return abs(this->number - result) > EPS;
    }

    ostream &operator<<(ostream& os, const NumberWithUnits& number)
    {
        return os << number.number << "[" << number.unit << "]";
    }
	
    istream &operator>>(istream& stream, NumberWithUnits& num)
    {
        double numberInput = 0;
        string  unitInput; 
        char c = '\0';
        stream >> numberInput >> c;
        while(c != ']')
        {
            if(c != '[')
            {
                unitInput.insert( unitInput.end(), c);
            }
            stream >> c;
        }
        if (unitsConverts.count( unitInput) > 0)
        {
            num.number =  numberInput;
            num.unit =  unitInput;
        }
        else
        {
            throw "Invalid unit!!";
        }
        return stream;
    }

	double NumberWithUnits::getNumber() const{
		return this->number;
	}

	string NumberWithUnits::getUnit(){
		return this->unit;
	}
}