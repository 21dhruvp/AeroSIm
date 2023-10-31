#pragma once
class glm {
	int vec2;
};
/****
* FoilMath is used to encapsulate all calculations relating to the specific
*	airfoil that is used. Currently only the NACA Four-Digit Series can be represented.
* 
* Calculations are based on: https://www.desmos.com/calculator/wtxxhobd6w
****/
class FoilMath {
	int NACAInput;					// The type of airfoil using the NACA four-digit standard
	double m;						// The m value for the foil
	double p;						// The p value for the foil
	double t;						// The t value for the foil
	bool i;							// Checks the validity of the NACA input

public:
	FoilMath();						// Use default foil (NACA 4412)
	FoilMath(unsigned int N);		// Use specified foil

	double MeanLine(double x);		// Calulates the points along the Mean Line	
	double ChordLine(double x);		// Calculates the points along the Chord Line
	double DChordLine(double x);	// Calculates the points along the derivative of the chord line

	glm::vec2 TopFoil(double T);	// Calculates the line representing the top of the foil
	glm::vec2 BotFoil(double B);	// Calculates the line representing the bottom of the foil

private:
	void CalcConsts();				// Handles the calculation of m, p, t, and i
};
