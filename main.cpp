#include <iostream>
#include <vector>
#include <fstream>
#include "randomc.h"
#include "operations.h"

using namespace std;

const int Nmb_particles = 1000;
const double Particle_radius = 1;
const double iSeed = 13;

void FillVectorWithCoords(vector <Particle>& particle_coords){
    double L = 40;
    double x,y,z;
    bool marker;
    TRandomMersenne* rg = new TRandomMersenne(iSeed);
    particle_coords[0] = Particle{0,0, 0};
    for(int i = 1; i < 1000; ++i){
        cout << i << endl;
        x = (1 - 2 * rg->Random()) * L / 2;
        y = (1 - 2 * rg->Random()) * L / 2;
        z = (1 - 2 * rg->Random()) * L / 2;
        marker = true;
        for (int j = 0; j <= i; ++j){
            if (sqrt(pow(particle_coords[j].x - x, 2) + pow(particle_coords[j].y - y, 2) +
            pow(particle_coords[j].z - z, 2)) < 2 * Particle_radius){
                marker = false;
                --i;
                cout << "FAIL" << endl;
                break;
            }
        }
        if (marker){
            particle_coords[i] = Particle{x,y,z};
        }
    }
}

int ClosestParticle(vector <Particle>& particle_coords, const vector<bool>& pressed_particles){
    double min_dist = 10000;
    double dist;
    int min_ind = 0;
    for (int i = 1; i < particle_coords.size(); ++i){
        dist = DotP(particle_coords[i], particle_coords[i]);
        if (min_dist > dist && pressed_particles[i] == false){
            min_dist = dist;
            min_ind = i;
        }
    }
    return min_ind;
}

void ToCenter(vector<Particle>& particle_coords, int ind){
    Particle norm_dir = particle_coords[ind] / -sqrt(DotP(particle_coords[ind], particle_coords[ind]));
    cout << norm_dir << endl;
    double koef = 0.05;
    double min_dist, dist;
    bool marker = true;
    double range_min = 1.95 * Particle_radius;
    double range_max = 2.05 * Particle_radius;
    Particle new_coords = particle_coords[ind];
    while (min_dist > range_min * range_min){
        particle_coords[ind] = new_coords;
        new_coords = particle_coords[ind] + norm_dir * Particle_radius * koef;
        min_dist = 10000;
        for (int i = 0; i < particle_coords.size(); ++i){
            dist = DotP(particle_coords[i] - new_coords, particle_coords[i] - new_coords);
            if (dist < min_dist && i != ind){
                min_dist = dist;
            }
        }
    }
}

void ParticlesPressing(vector <Particle>& particle_coords){
    vector<bool> pressed_particles(Nmb_particles, false);
    pressed_particles[0] = true;
    for (int i = 1; i < pressed_particles.size(); ++i) {
        int ind = ClosestParticle(particle_coords, pressed_particles);
        ToCenter(particle_coords, ind);
        pressed_particles[ind] = true;
    }

}

int main() {

    vector <Particle> particle_coords(Nmb_particles);
    vector <bool> particle_markers(Nmb_particles);
    FillVectorWithCoords(particle_coords);
    ofstream stream;
    stream.open("initial positions");
    for (const auto& item : particle_coords){
        stream << item << endl;
    }
    stream.close();

    ParticlesPressing(particle_coords);

    ofstream streamp;
    streamp.open("pressing positions");
    for (const auto& item : particle_coords){
        streamp << item << endl;
    }
    streamp.close();

    return 0;
}
