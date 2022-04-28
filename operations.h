#pragma once

#include <fstream>
#include <vector>

using namespace std;

struct Particle{
    double x;
    double y;
    double z;
};

double DotP(Particle l, Particle r);

Particle operator+ (const Particle& l, const Particle& r);

Particle operator- (const Particle& l, const Particle& r);

Particle operator* (const Particle& l, const double& r);

Particle operator/ (const Particle& l, const double& r);

ostream& operator<< (ostream& os, const Particle& l);

Particle ParticleVectorAvr(const vector<Particle>& input_vector);

double ParticleVectorStDiv(const Particle& avr, const vector<Particle>& vector);