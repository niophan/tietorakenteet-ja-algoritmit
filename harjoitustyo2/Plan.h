#ifndef PLAN_H
#define PLAN_H

#include <iostream>
using namespace std;

enum Plane_status {null, arriving, departing};

class Plane {
public:
   Plane();
   Plane(int flt, int time, Plane_status status);
   Plane(int flt, int time, Plane_status status, int fuel_level);
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   void crash(int time) const;
   int started() const;
   int fuel() const;
   bool out_of_fuel(int time) const;

private:
   int flt_num;
   int clock_start;
   Plane_status state;
   int fuel_value;
};


inline Plane::Plane(int flt, int time, Plane_status status, int fuel_level)
/*
Post:  The Plane data members flt_num, clock_start, state, and fuel_value
       are set to the values of the parameters.
*/
{
   flt_num = flt;
   clock_start = time;
   state = status;
   fuel_value = fuel_level;
   cout << "Plane number " << flt << " ready to ";
   if (status == arriving)
      cout << "land with this amount of fuel level " << fuel_level << endl;
   else
      cout << "take off." << endl;
}


inline Plane::Plane(int flt, int time, Plane_status status)
/*
Post:  The Plane data members flt_num, clock_start,
       and state are set to the values of the parameters flt,
       time and status, respectively.
*/
{
   flt_num = flt;
   clock_start = time;
   state = status;
   cout << "Plane number " << flt << " ready to ";
   if (status == arriving)
      cout << "land." << endl;
   else
      cout << "take off." << endl;
}

inline Plane::Plane()
/*
Post:  The Plane data members flt_num, clock_start,
       state are set to illegal default values.
*/
{
   flt_num = -1;
   clock_start = -1;
   state = null;
   fuel_value = -1;
}


inline void Plane::refuse() const
/*
Post: Processes a Plane wanting to use Runway, when
      the Queue is full.
*/

{
   cout << "Plane number " << flt_num;
   if (state == arriving)
      cout << " directed to another airport" << endl;
   else
      cout << " told to try to takeoff again later" << endl;
}


inline void Plane::land(int time) const
/*
Post: Processes a Plane that is landing at the specified time.
*/

{
   int wait = time - clock_start;
   cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the landing queue." << endl;
}


inline void Plane::fly(int time) const
/*
Post: Process a Plane that is taking off at the specified time.
*/

{
   int wait = time - clock_start;
   cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}


inline int Plane::started() const
/*
Post: Return the time that the Plane entered the airport system.
*/
{
   return clock_start;
}


inline int Plane::fuel() const
/*
Post: Return the plane fuel level in time units.
*/
{
   return fuel_value;
}


inline bool Plane::out_of_fuel(int time) const
/*
Post: Return true if this arriving plane has waited longer than its fuel.
*/
{
   int wait = time - clock_start;
   if (state != arriving || fuel_value < 0)
      return false;
   return wait > fuel_value;
}

inline void Plane::crash(int time) const
/*
Post: Inform the system that a Plane is crashed at the specified time.
*/
{
   cout << time << ": Plane number " << flt_num 
        << " crashed due to fuel exhaustion." << endl;
}

#endif