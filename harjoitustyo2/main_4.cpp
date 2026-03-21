#include <iostream>
#include "./Runway.h"
#include "./Plan.h"
#include "./RANDOM.H"

using namespace std;

void initialize_p4(int &end_time, int &queue_limit,
                   double &arrival_rate, double &departure_rate)
/*
Pre:  The user specifies the number of time units in the simulation,
      the maximal queue sizes permitted,
      and the expected arrival and departure rates for the airport.
Post: The program prints instructions and initializes the parameters
      end_time, queue_limit, arrival_rate, and departure_rate to
      the specified values.
Uses: utility function user_says_yes
*/

{
   cout << "This program simulates one airport with three runways." << endl
        << "Normally one runway is for landings and one for takeoffs." << endl
        << "The third runway is mostly for landings." << endl
        << "If landing queue is idle, this third runway can be used for takeoffs-queue." << endl;

   cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
   cin >> queue_limit;

   cout << "How many units of time will the simulation run?" << flush;
   cin >> end_time;

   bool acceptable = false;
   do {
      cout << "Expected number of arrivals per unit time?" << flush;
      cin >> arrival_rate;
      cout << "Expected number of departures per unit time?" << flush;
      cin >> departure_rate;

      if (arrival_rate < 0.0 || departure_rate < 0.0) {
         cerr << "These rates must be nonnegative." << endl;
      } else {
         acceptable = true;
      }

      if (acceptable && arrival_rate + departure_rate > 3.0) {
         cerr << "Safety Warning: This airport may become saturated." << endl;
      }
   } while (!acceptable);
}

void run_idle_p4(int time, int runway_slot)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
   cout << time << ": Runway " << runway_slot << " is idle." << endl;
}

int main_4()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle_p4, initialize_p4.
*/

{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   int served_three_runway = 0;
   double arrival_rate, departure_rate;
   initialize_p4(end_time, queue_limit, arrival_rate, departure_rate);
   Random variable;
   Runway landing_runway(queue_limit);
   Runway takeoff_runway(queue_limit);
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_runway.can_land(current_plane) != success) {
            current_plane.refuse();
         }
      }

      int number_departures = variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (takeoff_runway.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      Plane moving_plane;
      Runway_activity landing_slot = landing_runway.activity(current_time, moving_plane);
      if (landing_slot == land) {
         served_three_runway++;
         moving_plane.land(current_time);
      } else {
         run_idle_p4(current_time, 1);
      }

      Runway_activity takeoff_slot = takeoff_runway.activity(current_time, moving_plane);
      if (takeoff_slot == takeoff) {
         served_three_runway++;
         moving_plane.fly(current_time);
      } else {
         run_idle_p4(current_time, 2);
      }

      Runway_activity flexing_slot = landing_runway.activity(current_time, moving_plane);
      if (flexing_slot == land) {
         served_three_runway++;
         moving_plane.land(current_time);
      } else {
         Runway_activity borrowed = takeoff_runway.activity(current_time, moving_plane);
         if (borrowed == takeoff) {
            served_three_runway++;
            moving_plane.fly(current_time);
         } else {
            run_idle_p4(current_time, 3);
         }
      }
    }
   

   landing_runway.short_detail();
   takeoff_runway.short_detail();
   cout << endl;
   cout << "Three-runway summary:" << endl;
   cout << "Planes served with three-runway policy: " << served_three_runway << endl;
   
  return 0;
}
