#include <iostream>
#include "./Runway.h"
#include "./Plan.h"
#include "./RANDOM.H"

using namespace std;

void initialize_p2(int &end_time, int &queue_limit,
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
   cout << "This program simulates an airport with two runways." << endl
   << "One runway is dedicated to landing and one to takeoff." << endl;
   cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
   cin  >> queue_limit;

   cout << "How many units of time will the simulation run?" << flush;
   cin  >> end_time;

   bool acceptable;
   do {
      cout << "Expected number of arrivals per unit time?" << flush;
      cin  >> arrival_rate;
      cout << "Expected number of departures per unit time?" << flush;
      cin  >> departure_rate;
      if (arrival_rate < 0.0 || departure_rate < 0.0)
         cerr << "These rates must be nonnegative." << endl;
      else
         acceptable = true;

      if (acceptable && (arrival_rate > 1.0 || departure_rate > 1.0))
         cerr << "Safety Warning: At least one dedicated runway will become saturated. " << endl;

   } while (!acceptable);
}

void run_idle_p2(int time, const string &runway_name)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
   cout << time << ": " << runway_name << " runway is idle." << endl;
}

int main_2()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle_p2, initialize_p2.
*/

{
   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;
   int served_two_runway = 0;
   double arrival_rate, departure_rate;
   initialize_p2(end_time, queue_limit, arrival_rate, departure_rate);
   Random variable;
   Runway landing_runway(queue_limit);
   Runway takeoff_runway(queue_limit);
   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_runway.can_land(current_plane) != success)
            current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (takeoff_runway.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      Plane moving_plane;
      switch (landing_runway.activity(current_time, moving_plane)) {
      case land:
         served_two_runway++;
         moving_plane.land(current_time);
         break;
      case takeoff:
         break;
      case crash:
         break;
      case idle:
         run_idle_p2(current_time, "Landing");
      }

      switch (takeoff_runway.activity(current_time, moving_plane)) {
      case land:
         break;
      case crash:
         break;
      case takeoff:
         served_two_runway++;
         moving_plane.fly(current_time);
         break;
      case idle:
         run_idle_p2(current_time, "Takeoff");
      }
   }
  // landing_runway.shut_down(end_time);
  // takeoff_runway.shut_down(end_time);

   cout << endl;
   cout << "Two-runway summary:" << endl;
   cout << "Planes served with two dedicated runways: " << served_two_runway << endl;

  return 0;
}
