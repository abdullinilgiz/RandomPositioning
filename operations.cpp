#include "operations.h"

double DotP(Particle l, Particle r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

Particle operator+ (const Particle& l, const Particle& r) {
	return { l.x + r.x, l.y + r.y, l.z + r.z };
}
Particle operator- (const Particle& l, const Particle& r) {
	return { l.x - r.x, l.y - r.y, l.z - r.z };
}
Particle operator* (const Particle& l, const double& r) {
	return { l.x * r , l.y * r, l.z * r };
}
Particle operator/ (const Particle& l, const double& r) {
	return { l.x / r , l.y / r, l.z / r };
}
ostream& operator<< (ostream& os, const Particle& l) {
	os << l.x << " " << l.y << " " << l.z;
	return os;
}
