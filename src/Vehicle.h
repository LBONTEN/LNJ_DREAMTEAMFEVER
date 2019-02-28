/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <string>
using namespace std;

#ifndef LNJ_PIZZA_PROJECT_VEHICLE_H
#define LNJ_PIZZA_PROJECT_VEHICLE_H

class Vehicle
{
    string license_plate = generate_license_plate();
    string current_road;
    double acceleration;
    double speediness;
    double position;

    string generate_license_plate();

public:
    string get_license_plate() { return license_plate; }
    string get_current_road() { return current_road; }
    double get_acceleration() { return acceleration; }
    double get_speediness() { return speediness; }
    double get_position() { return position; }
};

#endif //LNJ_PIZZA_PROJECT_VEHICLE_H
