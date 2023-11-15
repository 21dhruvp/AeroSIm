#pragma once

#include <glm/vec2.hpp>
/****
* FoilMath is used to encapsulate all calculations relating to the specific
*	airfoil that is used. Currently only the NACA Four-Digit Series can be represented.
* 
* Calculations are based on: https://www.desmos.com/calculator/wtxxhobd6w
****/
class FoilMath {
	int NACAInput;					// The type of airfoil using the NACA four-digit standard
	float m;						// The m value for the foil
	float p;						// The p value for the foil
	float t;						// The t value for the foil
	bool i;							// Checks the validity of the NACA input

public:
	FoilMath();						// Use default foil (NACA 4412)
	FoilMath(unsigned int N);		// Use specified foil

	float MeanLine(float x);		// Calulates the points along the Mean Line	
	float ChordLine(float x);		// Calculates the points along the Chord Line
	float DChordLine(float x);	// Calculates the points along the derivative of the chord line

	glm::vec2 TopFoil(float T);	// Calculates the line representing the top of the foil
	glm::vec2 BotFoil(float B);	// Calculates the line representing the bottom of the foil

private:
	void CalcConsts();				// Handles the calculation of m, p, t, and i
};
