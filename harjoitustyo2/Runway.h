#ifndef RUNWAY_H
#define RUNWAY_H

#include "./Plan.h"
#include "./LinkedQueue.h"

#include <iostream>

enum Runway_activity {idle, land, takeoff, crash};

class Runway {
public:
   Runway(int limit);
   Error_code can_land(const Plane &current);
   Error_code can_depart(const Plane &current);
   Error_code can_land_with_fuel(const Plane &current);
   Runway_activity activity(int time, Plane &moving);
   Runway_activity emergency_activity(int time, Plane &moving);
   void shut_down(int time) const;
   void short_detail() const;
   void short_fuel_detail() const;


private:
   Extended_queue landing;
   Extended_queue takeoff_queue;
   Extended_queue landing_emergency_queue;
   int queue_limit;
   int num_land_requests;        //  number of planes asking to land
   int num_takeoff_requests;     //  number of planes asking to take off
   int num_landings;             //  number of planes that have landed
   int num_takeoffs;             //  number of planes that have taken off
   int num_land_accepted;        //  number of planes queued to land
   int num_takeoff_accepted;     //  number of planes queued to take off
   int num_land_refused;         //  number of landing planes refused
   int num_takeoff_refused;      //  number of departing planes refused
   int land_wait;                //  total time of planes waiting to land
   int takeoff_wait;             //  total time of planes waiting to take off
   int idle_time;                //  total time runway is idle
   int num_crashes;              //  number of landing planes crashed
   int num_emergency_landings;   //  number of emergency landing planes 
};

inline Runway::Runway(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
   queue_limit = limit;
   num_land_requests = num_takeoff_requests = 0;
   num_landings = num_takeoffs = 0;
   num_land_refused = num_takeoff_refused = 0;
   num_land_accepted = num_takeoff_accepted = 0;
   land_wait = takeoff_wait = idle_time = 0;
   num_crashes = 0;
   num_emergency_landings = 0;
}

inline Error_code Runway::can_land(const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
   Error_code result;
   if (landing.size() < queue_limit)
      result = landing.append(current);
   else
      result = overflow;
   num_land_requests++;

   if (result != success)
      num_land_refused++;
   else
      num_land_accepted++;

   return result;
}

inline Error_code Runway::can_land_with_fuel(const Plane &current)
/*
Post: If it has low fuel, it is placed into the emergency landing queue.
      If it has normal fuel, it goes into the regular landing queue.
*/
{
   Error_code result;
   if (current.fuel() >= 0 && current.fuel() <= landing_emergency_queue.size() + 1) {
      if (landing_emergency_queue.size() < queue_limit)
         result = landing_emergency_queue.append(current);
      else
         result = overflow;
   }
   else {
      if (landing.size() < queue_limit)
         result = landing.append(current);
      else
         result = overflow;
   }

   num_land_requests++;
   if (result != success)
      num_land_refused++;
   else
      num_land_accepted++;

   return result;
}


inline Error_code Runway::can_depart(const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
   Error_code result;
   if (takeoff_queue.size() < queue_limit)
      result = takeoff_queue.append(current);
   else
      result = overflow;
   num_takeoff_requests++;
   if (result != success)
      num_takeoff_refused++;
   else
      num_takeoff_accepted++;

   return result;
}

inline Runway_activity Runway::activity(int time, Plane &moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
   Runway_activity in_progress;
   if (!landing.empty()) {
      landing.retrieve(moving);
      land_wait += time - moving.started();
      num_landings++;
      in_progress = land;
      landing.serve();
   }

   else if (!takeoff_queue.empty()) {
      takeoff_queue.retrieve(moving);
      takeoff_wait += time - moving.started();
      num_takeoffs++;
      in_progress = takeoff;
      takeoff_queue.serve();
   }

   else {
      idle_time++;
      in_progress = idle;
   }
   return in_progress;
}

inline Runway_activity Runway::emergency_activity(int time, Plane &moving)
/*
Post:  Emergency landings are handled first.
       If the first emergency plane has already run out of fuel, it is counted as a crash and the function returns “crash.”
       If it still has enough fuel to land, the function returns “land.”
       If there are no emergency planes at all, the program follows the normal rules for handling planes.
*/
{
   if (!landing_emergency_queue.empty()) {
      landing_emergency_queue.retrieve(moving);
      landing_emergency_queue.serve();

      if (moving.out_of_fuel(time)) {
         num_crashes++;
         return crash;
      }

      land_wait += time - moving.started();
      num_landings++;
      num_emergency_landings++;
      return land;
   }

   return activity(time, moving);
}

inline void Runway::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
   cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (num_land_requests + num_takeoff_requests) << endl
        << "Total number of planes asking to land "
        << num_land_requests << endl
        << "Total number of planes asking to take off "
        << num_takeoff_requests << endl
        << "Total number of planes accepted for landing "
        << num_land_accepted << endl
        << "Total number of planes accepted for takeoff "
        << num_takeoff_accepted << endl
        << "Total number of planes refused for landing "
        << num_land_refused << endl
        << "Total number of planes refused for takeoff "
        << num_takeoff_refused << endl
        << "Total number of planes that landed "
        << num_landings << endl
        << "Total number of planes that took off "
        << num_takeoffs << endl
        << "Total number of planes left in landing queue "
        << landing.size() << endl
        << "Total number of planes left in takeoff queue "
      << takeoff_queue.size() << endl;
   cout << "Percentage of time runway idle "
        << 100.0 * (( float ) idle_time) / (( float ) time) << "%" << endl;
   if(num_landings > 0) 
    cout << "Average wait in landing queue "
         << (( float ) land_wait) / (( float ) num_landings) << " time units";
   else
      cout << "Average wait in landing queue: No planes landed";
   if (num_takeoffs > 0)
    cout << endl << "Average wait in takeoff queue "
         << (( float ) takeoff_wait) / (( float ) num_takeoffs)
         << " time units" << endl;
   else
    cout << "Average wait in takeoff queue: No planes took off";
   cout << "Average observed rate of planes wanting to land "
        << (( float ) num_land_requests) / (( float ) time)
        << " per time unit" << endl;
   cout << "Average observed rate of planes wanting to take off "
        << (( float ) num_takeoff_requests) / (( float ) time)
        << " per time unit" << endl;
}

inline void Runway::short_detail() const{
  cout << "Summary: " << endl;
  cout << "Total number of planes that landed " << num_landings << endl;
  cout << "Total number of planes that took off " << num_takeoffs << endl;
  cout << "Total number of planes served " << (num_landings + num_takeoffs) << endl;
  cout << "Total number of planes refused for landing " << num_land_refused << endl;
  cout << "Total number of planes refused for takeoff " << num_takeoff_refused << endl;
  cout << "Total number of planes left in landing queue " << landing.size() << endl;
  cout << "Total number of planes left in takeoff queue " << takeoff_queue.size() << endl;
}

inline void Runway::short_fuel_detail() const
{
    short_detail();
    cout << "Total emergency landings served " << num_emergency_landings << endl;
    cout << "Total number of crashes " << num_crashes << endl;
    cout << "Total number of planes left in emergency landing queue "
            << landing_emergency_queue.size() << endl;
}


#endif