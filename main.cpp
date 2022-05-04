#include <iostream>
#include <vector>
#include "randomc.h"
#include "operations.h"
#include "mylibr.h"

using namespace std;

int ClosestParticle(vector <Particle>& particle_coords, const vector<bool>& pressed_particles){
    double min_dist = 10000;
    double dist;
    int min_ind = 0;
    for (int i = 1; i < particle_coords.size(); ++i){
        dist = DotP(particle_coords[i], particle_coords[i]);
        if (min_dist > dist && !pressed_particles[i]){
            min_dist = dist;
            min_ind = i;
        }
    }
    return min_ind;
}

void ToCenter(vector<Particle>& particle_coords, int ind){
    Particle norm_dir = particle_coords[ind] / -sqrt(DotP(particle_coords[ind], particle_coords[ind]));
    double koef = 0.05;
    double min_dist = 10000, dist;
    double range_min = 1.95 * Particle_radius;
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

void ParticlesShift(vector <Particle>& particle_coords){
    double max_x = -100, max_y = -100, max_z = -100;
    double min_x = 100, min_y = 100, min_z = 100;
    for(const auto item : particle_coords){
        if (max_x < item.x) max_x = item.x;
        if (max_y < item.y) max_y = item.y;
        if (max_z < item.z) max_z = item.z;
        if (min_x > item.x) min_x = item.x;
        if (min_y > item.y) min_y = item.y;
        if (min_z > item.z) min_z = item.z;
    }
    for(auto& item : particle_coords){
        item.x -= min_x;
        item.y -= min_y;
        item.z -= min_z;
    }
    XSideLength = max_x - min_x - 2 * Particle_radius;
    XHalfSideLength = XSideLength / 2;
    YSideLength = max_y - min_y - 2 * Particle_radius;
    YHalfSideLength = YSideLength / 2;
    ZSideLength = max_z - min_z - 2 * Particle_radius;
    ZHalfSideLength = ZSideLength / 2;
    ShortestHalfSideLength = min(XSideLength, min(YSideLength, ZSideLength)) / 2.0;
    cout << XSideLength << " " << YSideLength << " " << ZSideLength << endl;
}

void FillVectorWithCoords(vector <Particle>& particle_coords){
    double L = Particle_diam * 22;
    double x,y,z;
    bool marker;
    TRandomMersenne* rg = new TRandomMersenne(iSeed);
    particle_coords[0] = Particle{0,0, 0};
    for(int i = 1; i < Nmb_particles; ++i){
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

    ofstream stream;
    stream.open("initial positions.txt");
    for (const auto& item : particle_coords){
        stream << item << endl;
    }
    stream.close();

    ParticlesPressing(particle_coords);
    ParticlesShift(particle_coords);
}



int main() {

    vector <Particle> particle_coords(Nmb_particles);
    vector <bool> particle_markers(Nmb_particles);
    FillVectorWithCoords(particle_coords);

    ofstream streamp;
    streamp.open("pressing positions.txt");
    for (const auto& item : particle_coords){
        streamp << item << endl;
    }
    streamp.close();

    return 0;
}
