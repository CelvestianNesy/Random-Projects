#include <iostream>
#include <vector>
#include <string>
std::ostream& operator<< (std::ostream& out, std::vector<std::string> vector)
{
	
	for (std::string text : vector)
	{
		out << text;
	}
	

	return out;
}

struct battery
{
public:
	double voltage = {};
	std::string location = {};
};

struct resistor
{
public:
	double resistance= {};
	std::string location = {};
};

struct resistorpackage
{
public:
	std::vector<resistor> resistors = {}; 	
	double resistanceCalculate()
	{
		double finalResistorValue = 0;
		double denominatores = 0;
		int tag = 0;
		for (resistor resistor : resistors)  
		{
				if (resistor.location == "series")
				{
					finalResistorValue += resistor.resistance;
				}
				else if (resistor.location == "parallel")
				{
					denominatores += (1 / (resistor.resistance));
					tag = 1;
				}
				else
				{
					std::cout << "Invalid resistor type!\n";
				}
		}
		if (tag == 1)
		{
			finalResistorValue += (1 / (denominatores));
		}
		return finalResistorValue;
	}
};

double batteryVoltageCalculator(std::vector<battery> batteries)
{
	double voltage = 0;
	for (battery battery : batteries)
	{
		if (battery.location == "series")
		{
			voltage += battery.voltage;
		}
	}

	return voltage;
}

void display(double& voltage, double& current, double& resistance)
{
	std::cout << "Circuit information:\n";
	std::cout << "Voltage across the entire circuit: " << voltage << " V \n";
	std::cout << "Current: " << current << " A \n";
	std::cout << "Resistance: " << resistance << " ohms \n";
}

int main()
{

	battery battery1 = { 75,"series" };  //Add or remove batteries. 
	std::vector<battery> batteries = { battery1 };
	double totalVoltage = batteryVoltageCalculator(batteries);   //Calculate total voltage in the circuit.

	//Place our resistors in here.

	resistor resistor1 = { 50,"parallel" };
	resistor resistor2 = { 50,"parallel" };
	resistor resistor3 = { 50,"series" };
	std::vector<resistor> resistors1 = { resistor1,resistor2,resistor3 }; //Package the resistors into a vector.
	resistorpackage resistorPackage1 = { resistors1 }; //Package everything into one single resistor-package. Our struct, resistorpackage contains the "resistors" variable, which can be accessed by our function named resistorCalculator
	//--------------------------------------------------------------------------------------------------------

	resistor resistor4 = { 50,"parallel" };
	resistor resistor5 = { 50,"parallel" };
	resistor resistor6 = { 50,"series" };
	std::vector<resistor> resistors2 = { resistor4 ,resistor5,resistor6 };
	resistorpackage resistorPackage2 = { resistors2 };


	//A resistorcomplex is a package of multiple resistor packages/or one. We treat them as one single resistor. Our resistance is calculated via the Res-calculator function.

	resistor resistorComplex1 = { resistorPackage1.resistanceCalculate(),"parallel"};
	resistor resistorComplex2 = { resistorPackage2.resistanceCalculate(), "parallel"};
	std::vector<resistor> resistorComplex = { resistorComplex1,resistorComplex2 };    //Collect every resistorcomplex in a vector.
	resistorpackage allResistors = { resistorComplex }; //Push the vector inside, so we can use the resistorCalculatorFunction to access our resistorcomplexes.
	double totalResistance = allResistors.resistanceCalculate();


	double current = totalVoltage / totalResistance; //Ohms law. 

	display(totalVoltage,current, totalResistance);


	return 0;
}

