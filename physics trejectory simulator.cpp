#include <iostream>  //no error checking involved in this program. Too lazy to add it xD
#include <vector>
#include <cmath>

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec)
{
	out << "[ ";
	for (T elements : vec) 
	{
		out << elements << " ";
	}
	out << " ]";
	return out;
}

template <typename T>
void distancetracker(T startv_y, T startv_x, int startheight) //our actual calculation takes place here.  (uh... as mentioned below)
{
	double displacementy = 0; //y-position
	double displacementx = 0; //x-position
	
	double static g = 9.82;   //earth's gravitational constant
	
	double t = 0;             //time 

	while (true)
	{
		t += 0.0001; //counting up
		displacementy = startheight + startv_y * t - ((g * pow(t,2)) / 2); 
		displacementx = startv_x * t;

		if (displacementy <= 0)
		{
			break;   //so we do not go underneath the y-axis. the loop ends.
		}
		std::cout << "height: " << displacementy << "m distance traveled: " << displacementx << "m time: " << t << "s \n"; //display 
	}

}


int main()
{
	double angleStart = 0;                        //The angle
	double startheight = 0;                       //The height you start at.
	double realSpeed = 0;                         //The speed of the object.
	constexpr double pi = 3.14159265358979323846; //the constant pi 
	std::cout << "Input starting speed for throwing/firing your object (in m/s): ";       //ask user for input 
	std::cin >> realSpeed;
	std::cout << "Input the angle for throwing/firing your object (degrees): ";           //ask user for input 
	std::cin >> angleStart;
	std::cout << "Input the start-height for throwing/firing your object (in meters): ";  //ask user for input 
	std::cin >> startheight;
	double radians = ((angleStart*(pi / 180)));         //converting from deg to rad 

	const double start_y = std::sin(radians)*realSpeed; //trig stuff, we get the vertical start speed
	const double start_x = std::cos(radians)*realSpeed; //trig stuff, we get the horizontal start speed
	
	distancetracker(start_y, start_x,startheight);      //our actual calculation takes place here. 

}



