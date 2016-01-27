/*********************************************************************************************************
Title: Programming Assignment #1
Author: Daniel Cambitsis
Created on: March 1st, 2015
Description: Data from a .txt document called "data.txt" is inputted and from there, a menu is displayed
to the user. The user can opt to calculate the force between two objects, each with their own masses and 
coordinates, the distance between the two objects, or can either arbitrarily or manually change the 
objects' locations. 
Usage: ./cambitsis_daniel_hwk1
Build with: g++ cambitsis_daniel_hwk1.cpp -o cambtsis_daniel_hwk1
Dependencies: An input file, data.txt, should be in the same directory.
**********************************************************************************************************/

#include <iostream>
#include <fstream> //needed for inputting files from data.txt
#include <time.h> //needed for seed generation for srand() if seed == 0
#include <cstdlib> //needed for srand() and rand()
#include <string> //needed for menu
#include <cmath> //needed for pow () and sqrt ()

using namespace std; 

const double GRAVITATIONAL_CONSTANT = 6.674e-11; //global constant needed for calculating gravitational force

void inputseed (int SEED); /*
sets srand() 
@param: int SEED (inputted from data.txt)
@pre: SEED is a whole number greater than or equal to 0 
@post: if SEED is 0, srand(time(0)) else srand(SEED) 
no return 
*/
double gravitationalforce (double MASS_BODY1, double MASS_BODY2, double DISTANCE_BETWEEN); /*
calculates gravitational force between two bodies 
@param: double MASS_BODY, double MASS_BODY2 (imported from data.txt), double DISTANCE_BETWEEN (imported from the distancebetween function) 
@pre: mass is greater than 0, is in kilograms, and is a floating point value 
@post: none 
return: GRAVITATIONAL_FORCE, or the gravitational force between two bodies 
*/ 
double distancebetween (double XCOORD_BODY1, double XCOORD_BODY2, double YCOORD_BODY1, double YCOORD_BODY2); /*
calculates the distance between two bodies
@param: double XCOORD_BODY1, XCOORD_BODY2, YCOORD_BODY1, YCOORD_BODY2 (imported from data.txt) 
@pre: coordinates are floating point values and can be either negative or positive 
@post: none 
return: DISTANCE_BETWEEN, or the distance between the two bodies 
*/ 
void changeposition (double & XCOORD_BODY, double & YCOORD_BODY, int DIRECTION_RAND_INPUT, double DISTANCE_RAND_INPUT); /*
changes the position arbitrarily of body #1 or manually (user inputs) of body #2 
@param: double & XCOORD_BODY, double & YCOORD_BODY (inputted from data.txt) int DIRECTION_RAND_INPUT, double DISTANCE_RAND_INPUT (either randomly generated or inputted from user)
@pre: coordinates are floating point values and can be either negative or positive, the direction is a whole number between 0 and 359, the distance is a floating point value between 2.0 and 1500.0 
@post: the value of the coordinates depends on the direction and whether distance is added, subtracted, or multiplied
no return
*/ 

int main () { 
	ifstream inputStream; //declares the inputStream variable
	int SEED_VALUE, MENU_INPUT, DIRECTION_INPUT, DIRECTION_RAND;
	double MASS_BODY1, XCOORD_BODY1, YCOORD_BODY1, MASS_BODY2, XCOORD_BODY2, YCOORD_BODY2, GRAVITATIONAL_FORCE, DISTANCE_BETWEEN, DISTANCE_INPUT, DISTANCE_RAND;
	// declaration of variables to be used; DIRECTION_INPUT and RAND are int type for whole number values, while DISTANCE_INPUT and RAND are double to display decimal values
	inputStream.open("data.txt"); //opens the data.txt file
	inputStream >> SEED_VALUE >> MASS_BODY1 >> XCOORD_BODY1 >> YCOORD_BODY1 >> MASS_BODY2 >> XCOORD_BODY2 >> YCOORD_BODY2; //input values from data.txt
	inputseed(SEED_VALUE); //the SEED_VALUE (seed) is generated
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
    	cout.precision(2); //two decimal points of precision

	cout << "~= BODIES WITH MASSES AND COORDINATES =~" << endl;
	cout << "Body #1: " << MASS_BODY1 << " kg @ (" << XCOORD_BODY1 << ", " << YCOORD_BODY1 << ")" << endl;
	cout << "Body #2: " << MASS_BODY2 << " kg @ (" << XCOORD_BODY2 << ", " << YCOORD_BODY2 << ")" << endl;
	cout << endl; //displays the values of mass bodies and coordinates, x-coordinates and y-coordinates are subject to change from options 3 and 4 in menu

	string menu = "~= MENU =~ \n" 
			"Please enter a number corresponding to the event that you wish to perform: \n" 
			"1. \t Calculate the gravitational attractive force between the two bodies. \n" 
			"2. \t Calculate the distance between the two bodies. \n" 
			"3. \t Move body #1 a random distance and direction. \n" 
			"4. \t Move body #2 a user defined distance and direction. \n" 
			"5. \t Exit the program. \n"; //declaration of the string menu, which is used to output menu to user
	cout << menu << endl;
	cout << "Please make your selection: "; cin >> MENU_INPUT; //outputs menu, asks for user's input

	while ((MENU_INPUT >= 1) || (MENU_INPUT <= 5)) { //while loop is utilized to loop the menu while MENU_INPUT values are 1 <= MENU_INPUT <= 5
	switch (MENU_INPUT) { //switch is implemented for menu selection, ranging from case 1 to 5
		case 1:	GRAVITATIONAL_FORCE = gravitationalforce (MASS_BODY1, MASS_BODY2, DISTANCE_BETWEEN); //GRAVITATIONAL_FORCE is the value returned from gravitationalforce function
			cout << endl;
			cout << "Gravitational force between bodies: " << GRAVITATIONAL_FORCE << " Newtons." << endl; //GRAVITATIONAL_FORCE is displayed to user
			cout << endl;
			cout.setf(ios::fixed);
    			cout.setf(ios::showpoint);
   			cout.precision(2); //two decimal points of precision
			cout << "~= BODIES WITH MASSES AND COORDINATES =~" << endl;
			cout << "Body #1: " << MASS_BODY1 << " kg @ (" << XCOORD_BODY1 << ", " << YCOORD_BODY1 << ")" << endl;
			cout << "Body #2: " << MASS_BODY2 << " kg @ (" << XCOORD_BODY2 << ", " << YCOORD_BODY2 << ")" << endl;
			cout << endl;
			cout << menu; //menu is shown
			cout << "Please make your selection: "; cin >> MENU_INPUT; //asks for user's input
			break;
		case 2: DISTANCE_BETWEEN = distancebetween(XCOORD_BODY1, XCOORD_BODY2, YCOORD_BODY1, YCOORD_BODY2); //DISTANCE_BETWEEN is the value returned from distancebetween function
			// NOTE: I'm assuming the user is cognizant to the fact that this must be entered first as the gravitationalforce function depends on the distancebetween function for an accurate result
			cout << endl;
			cout << "Distance between bodies: " << DISTANCE_BETWEEN << " meters." << endl; //DISTANCE_BETWEEN is displayed to user
			cout << endl;
			cout.setf(ios::fixed);
    			cout.setf(ios::showpoint);
    			cout.precision(2); //two decimal points of precision
			cout << "~= BODIES WITH MASSES AND COORDINATES =~" << endl;
			cout << "Body #1: " << MASS_BODY1 << " kg @ (" << XCOORD_BODY1 << ", " << YCOORD_BODY1 << ")" << endl;
			cout << "Body #2: " << MASS_BODY2 << " kg @ (" << XCOORD_BODY2 << ", " << YCOORD_BODY2 << ")" << endl;
			cout << endl;
			cout << menu; //menu is shown
			cout << "Please make your selection: "; cin >> MENU_INPUT; //asks for user's input
			break;
		case 3: DIRECTION_RAND = rand() % 360; //DIRECTION_RAND is the randomly generated number between 0 and 359 (recall, a whole number that is 0 <=  DIRECTION_RAND <= 359)
    			DISTANCE_RAND = (rand() / (static_cast<double>(RAND_MAX) / (1500.0 - 2.0))) + 2.0; /*DISTANCE_RAND is the randomly generated number between 2.0 and 1500.0 
    			RAND_MAX is static cast to a double and is divided by 1500.0 - 2.0, the result divides rand(), + 2.0 is padded to restore the min value back to 2.0 rather than 0.0 */
			changeposition(XCOORD_BODY1, YCOORD_BODY1, DIRECTION_RAND, DISTANCE_RAND); 
			/*change position function to Body #1, with xcoord1, ycoord1, and the random direction and distance as parameters, 
			will affect coordinate values depending on DIRECTION_RAND and DISTANCE_RAND values */
			cout << endl;
			cout << "Moving body #1 " << DISTANCE_RAND << " meters in direction " << DIRECTION_RAND << " degrees." << endl; //both DISTANCE_RAND and DIRECTION_RAND are displayed to user
			cout << endl;
			cout << "~= BODIES WITH MASSES AND COORDINATES =~" << endl;
			cout << "Body #1: " << MASS_BODY1 << " kg @ (" << XCOORD_BODY1 << ", " << YCOORD_BODY1 << ")" << endl;
			cout << "Body #2: " << MASS_BODY2 << " kg @ (" << XCOORD_BODY2 << ", " << YCOORD_BODY2 << ")" << endl; //display information with updated coordinates to Body #1
			cout << endl; 
			cout << menu; //menu is shown
			cout << "Please make your selection: "; cin >> MENU_INPUT; //asks for user's input
			break;
		case 4: cout << "Please input direction (0 <= direction <= 359): "; cin >> DIRECTION_INPUT; //user enters DIRECTION_INPUT, or the direction
			while ((DIRECTION_INPUT < 0) || (DIRECTION_INPUT > 359)) { //while loop is utilized to prevent user from exceeding intended boundaries (0 - 359)
				cout << "This is not a valid direction. Please re-enter a valid direction: "; cin >> DIRECTION_INPUT; //asks user to input correct value
			} 
			cout << "Please input distance (2.0 <= distance <= 1500.0): "; cin >> DISTANCE_INPUT; //user enters DISTANCE_INPUT, or the distance
			while ((DISTANCE_INPUT < 2.0) || (DISTANCE_INPUT > 1500.0)) { //while loop is utilized to prevent user from exceeding intended boundaries (2.0 - 1500.0)
				cout << "This is not a valid distance. Please re-enter a valid distance: "; cin >> DISTANCE_INPUT; //asks user to input correct value
			} 
			changeposition(XCOORD_BODY2, YCOORD_BODY2, DIRECTION_INPUT, DISTANCE_INPUT); 
			/*change position function to Body #2, with xcoord1, ycoord1, and the user entered direction and distance as parameters, 
			will affect coordinate values depending on DIRECTION_INPUT and DISTANCE_INPUT values */
			cout << endl;
			cout << "Moving body #2 " << DISTANCE_INPUT << " meters in direction " << DIRECTION_INPUT << " degrees." << endl; //both DISTANCE_INPUT and DIRECTION_INPUT are displayed to user
			cout << endl;
			cout << "~= BODIES WITH MASSES AND COORDINATES =~" << endl;
			cout << "Body #1: " << MASS_BODY1 << " kg @ (" << XCOORD_BODY1 << ", " << YCOORD_BODY1 << ")" << endl;
			cout << "Body #2: " << MASS_BODY2 << " kg @ (" << XCOORD_BODY2 << ", " << YCOORD_BODY2 << ")" << endl; //display information with updated coordinates to Body #2
			cout << endl; 
			cout << menu; //menu is shown
			cout << "Please make your selection: "; cin >> MENU_INPUT; //asks for user's input
			break;
		case 5: cout << "Goodbye!" << endl; //displays a goodbye message to user
			return 0; //ends program
		default: 
			while ((MENU_INPUT < 1) || (MENU_INPUT > 5)) { //default statement is used with a while loop to only let user enter values 1, 2, 3, 4, or 5
				cout << "Please re-enter a valid number: "; cin >> MENU_INPUT; //asks user to input correct value
			} 
		}	
	}

	return 0; //ends program
}

void inputseed (int SEED) { //void function with no return value, sets srand()
	if (SEED == 0) { //if SEED_VALUE is read as "0" from data.txt ...
		srand(time(0)); // ... srand uses a value read from the time(0) function
	}
	else if (SEED > 0) { //else, SEED_VALUE > 0 ...
		srand(SEED); // ... srand would use the SEED_VALUE read from data.txt
	}
}

double gravitationalforce(double MASS_BODY1, double MASS_BODY2, double DISTANCE_BETWEEN) { //type double function with a GRAVITATIONAL_FORCE return
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(5); //five decimal points of precision
    double GRAVITATIONAL_FORCE = GRAVITATIONAL_CONSTANT * ((MASS_BODY1 * MASS_BODY2) / pow(DISTANCE_BETWEEN, 2));
	/*global constant GRAVITATIONAL_CONSTANT (declared at the beginning of the program) is multiplied with the result of the multiplication between the two
	MASS_BODY inputs divided by the DISTANCE_BETWEEN (read from menu selection 2) squared, this is equal to a double type called GRAVITATIONAL_FORCE */

    return GRAVITATIONAL_FORCE; //GRAVITATIONAL_FORCE is returned, to be displayed to user in int main()
}

double distancebetween (double XCOORD_BODY1, double XCOORD_BODY2, double YCOORD_BODY1, double YCOORD_BODY2) { //type double function with a DISTANCE_BETWEEN return

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(5); //five decimal points of precision

    double DISTANCE_BETWEEN = sqrt(pow((XCOORD_BODY2 - XCOORD_BODY1), 2) + pow((YCOORD_BODY2 - YCOORD_BODY1), 2));
	/* the distance formula between two Cartesian coordinates is used, where the x-coordinates of body 1 is subtracted from the x-coordinates of body 2 (likewise for
	the y-coordinates), each result is squared, summated, and the square root is taken; this is equal to a double type called DISTANCE_BETWEEN */
    return DISTANCE_BETWEEN; //DISTANCE_BETWEEN is returned, to be displayed to user in int main()
}

void changeposition (double & XCOORD_BODY, double & YCOORD_BODY, int DIRECTION_RAND_INPUT, double DISTANCE_RAND_INPUT) { //void function with no return value, determines coordinate positions
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2); //two decimal points of precision
    int DIRECTION_ = DIRECTION_RAND_INPUT; //DIRECTION_ is set equal to DIRECTION_RAND_INPUT
    double DISTANCE_ = DISTANCE_RAND_INPUT; //DISTANCE_ is set equal to DISTANCE_RAND_INPUT
    double PI = 3.1415926535897; //the value of PI needed to convert radians to degrees
    /* based on the randomly generated direction or user input direction, the coordinate values will be affected. For example, if the user inputs or the value
    is randomly 180, only the x-coordinate will be affected and by how much depends on either the randomly generated or user input distance */ 

    if (DIRECTION_ == 0) {
    	XCOORD_BODY = XCOORD_BODY + DISTANCE_;
    }

    if (DIRECTION_ == 45) {
    	XCOORD_BODY = XCOORD_BODY + DISTANCE_;
    	YCOORD_BODY = YCOORD_BODY + DISTANCE_;
    }

    if (DIRECTION_ == 90) {
    	YCOORD_BODY = YCOORD_BODY + DISTANCE_;
    }

    if (DIRECTION_ == 135) {
    	XCOORD_BODY = XCOORD_BODY - DISTANCE_;
    	YCOORD_BODY = YCOORD_BODY + DISTANCE_;
    }

    if (DIRECTION_ == 180) {
    	XCOORD_BODY = XCOORD_BODY - DISTANCE_;
    }

    if (DIRECTION_ == 225) {
    	XCOORD_BODY = XCOORD_BODY - DISTANCE_;
    	YCOORD_BODY = YCOORD_BODY - DISTANCE_;
    }

    if (DIRECTION_ == 270) {
    	YCOORD_BODY = YCOORD_BODY - DISTANCE_;
    }

    if (DIRECTION_ == 315) {
    	XCOORD_BODY = XCOORD_BODY + DISTANCE_;
    	YCOORD_BODY = YCOORD_BODY - DISTANCE_;
    }

    /* in cases where the degrees entered or randomly generated are not bisecting the x,y axes or going perfectly along the axes,
    the updated coordinates must correspond to the entered direction. For example, if 70 is randomly generated, we can assume that 
    it is the hypotenuse of an imaginary triangle in quadrant I of a Cartesian graph. The "y-side" would serve as the opposite side 
    while the "x-side" would serve as the adjacent side. Using trigonometry, the sin of DIRECTION_ (angle) would be multiplied by the DISTANCE_
    (hypotenuse) in order to achieve the new y-coordinate (the value of "y-side") while the cos of DIRECTION_ would achieve the new x-coordinate 
    (the value of "x-side"). DIRECTION_ is multiplied by PI and divided by 180 to convert radians into degrees.
    */

    else if ((DIRECTION_ >= 1 && DIRECTION_ <= 44) || (DIRECTION_ >= 46 && DIRECTION_ <= 89) || (DIRECTION_ >= 91 && DIRECTION_ <= 134) 
    		|| (DIRECTION_ >= 136 && DIRECTION_ <= 179) || (DIRECTION_ >= 181 && DIRECTION_ <= 224) || (DIRECTION_ >= 226 && DIRECTION_ <= 269) 
    		|| (DIRECTION_ >= 271 && DIRECTION_ <= 314) || (DIRECTION_ >= 316 && DIRECTION_ <= 359)) {
    	
    	YCOORD_BODY = sin((DIRECTION_ * PI) / 180) * DISTANCE_; 
    	XCOORD_BODY = cos((DIRECTION_ * PI) / 180) * DISTANCE_; 
    }


}
