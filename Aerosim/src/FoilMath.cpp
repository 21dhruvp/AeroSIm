#include "FoilMath.h"
#include <math.h>
#include <glm/vec2.hpp>

FoilMath::FoilMath() {
	NACAInput = 4412;
	CalcConsts();
}

FoilMath::FoilMath(unsigned int N) {
	NACAInput = N;
	CalcConsts();
}

double FoilMath::MeanLine(double x) {
	double poly = 0.2969 * sqrt(x) - 0.1260 * x - 0.3516 * x * x -
		0.2843 * pow(x, 3) - 0.1015 * pow(x, 4);
	if (i * x <= 1 && i * x >= 0) {
		return (t / 0.2) * poly;
	}
	return NAN;
}

double FoilMath::ChordLine(double x) {
	if (i * x <= p && i * x >= 0) {
		return (m / (p * p)) * (2 * p * x - x * x);
	} else if (i * x <= 1) {
		return (m / ((1 - p) * (1 - p))) * ((1 - 2 * p) + 2 * p * x - x * x);
	}
	return NAN;
}

double FoilMath::DChordLine(double x) {
	if (i * x <= p && i * x >= 0) {
		return (m / (p * p)) * (2 * p - 2 * x);
	} else if (i * x <= 1) {
		return (m / ((1 - p) * (1 - p))) * (2 * p - 2 * x);
	}
	return NAN;
}

glm::vec2 FoilMath::TopFoil(double T) {
	double x = T - MeanLine(T)*sin(atan(DChordLine(T)));
	double y = ChordLine(T)+MeanLine(T)*cos(atan(DChordLine(T)));
	return glm::vec2(x, y);
}

glm::vec2 FoilMath::BotFoil(double B) {
	double x = B + MeanLine(B) * sin(atan(DChordLine(B)));
	double y = ChordLine(B) - MeanLine(B) * cos(atan(DChordLine(B)));
	return glm::vec2(x, y);
}

void FoilMath::CalcConsts() {
	t = (fmod(NACAInput / 10, 10) * 10) / 100;
	p = round(fmod(NACAInput / 100, 100)) / 10;
	m = floor(fmod(NACAInput / 100, 100) / 10) / 100;
	i = floor(NACAInput / 10000) == 0;
}