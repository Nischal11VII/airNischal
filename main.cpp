#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ncurses.h>
#include <string>
#include <vector>

#include "Database.h"
#include "logIn.h"
#include "menu.h"
#include "showBook.h"
#include "signUp.h"

#define ACODE 117

using namespace std;

int main() {
  string loggedUser;
  string loggedAdmin;
  string loggedGmail;
  vector<string> menu_option = {"SIGN UP", "LOG IN", "ADMIN PANEL", "EXIT"};
  //   vector<string> airLine = {"Delta", "British", "American", "Lufthansa",
  //   "LockHeed.PVT"};

  // Initialize ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  // Welcome screen
  clear();
  refresh();
  Menu welcome(
      {"WELCOME TO THE FLIGHT RESERVATION", "Press any key to get started"}, 5,
      50);
  welcome.strictDisplay();
  //   welcome.display();
  clear();
  refresh();

  Database db;
  db.loadAirports();
  //   flights.clear();
  db.loadFlights();

  while (true) {
    // Main menu using Menu class
    Menu mainMenu(menu_option, getmaxy(stdscr), getmaxx(stdscr));
    //     Menu mainMenu(menu_option, 12, 50);
    int choice = mainMenu.display();

    if (choice == -1) { // Escape pressed
      continue;
    }

    switch (choice) {
    case 0: { // SIGN UP
      vector<string> signUpOptions = {
          "Username: ", "Gmail: ", "Password: ", "Submit", "Cancel"};
      SignUp activate;
      if (activate.showSignUp(signUpOptions)) {
        clear();
        refresh();
        Menu status({"Sign Up Successful.", "Press any key to continue"}, 5,
                    30);
        status.strictDisplay();
        //           status.display();
      } else {
        clear();
        refresh();
        Menu status({"Sign Up was Unsuccessful.", "Press any key to continue"},
                    5, 30);
        status.strictDisplay();
        //                 status.display();
      }
      break;
    }

    case 1: { // LOG IN
      logIn activateLog;
      vector<string> status = {"Customer", "Admin", "Cancel"};
      int passChoice = activateLog.customerOrAdmin(status);

      if (passChoice == 0) { // Customer
        const vector<string> logInOptions = {
            "Username/Gmail: ", "Password: ", "Submit", "Cancel"};
        bool hasUserAccess = activateLog.showLogIn(logInOptions);
        loggedUser = activateLog.getUserId();
        //     string gmailForBookingFlight = activateLog.getUserGmail();
        clear();
        refresh();

        if (hasUserAccess) {
          // Book a Flight: Airport selection (placeholder)
          // Assume airports.csv exists with format: AirportID,Name
          loggedGmail = activateLog.getUserGmail();
          //          clear();
          //          refresh();

        backToUserPanel:

          vector<string> userPanel = {"Book a Flight", "See Your Flight",
                                      "Delete bookings", "Exit"};
          Menu userMind(userPanel, 12, 50);
          int getuser = userMind.display();

          if (getuser == -1) {
            break;
          }

          else if (getuser == 0) {

            //***              Database db;
            //***              db.loadAirports();
            Menu originMenu(db.getAirportNames(), 20, 70);
            int originChoice = originMenu.display();
            if (originChoice == -1) {
              break; // Cancel
            }

            // Exclude selected origin from destination list
            vector<string> destinations = db.getAirportNames();
            destinations.erase(destinations.begin() + originChoice);
            Menu destMenu(destinations, 20, 70);
            int destChoice = destMenu.display();
            if (destChoice == -1) {
              break; // Cancel
            }

            // Placeholder for flight selection
            clear();
            refresh();

            string origin = db.getAirportID(originChoice);
            string airportOrigin = db.getAirName(originChoice);
            int destIndex =
                destChoice < originChoice ? destChoice : destChoice + 1;
            string dest = db.getAirportID(destIndex);
            string airportDestination = db.getAirName(destChoice);

            //    db.loadFlights();

            /* // helped debuging

                WINDOW* msg_win = newwin(10 , 50 , (getmaxy(stdscr)-10) /
               2,(getmaxx(stdscr) - 50) / 2 ); wmove(msg_win , 2, 2);
                wprintw(msg_win ,  "%s %s " , origin.c_str() , dest.c_str());
                wrefresh(msg_win);
                getch();
                delwin(msg_win);
            */

            /*

                string shortOrigin;
                string shortDest;

                istringstream ss(origin);
                istringstream nn(dest);

                string discardLine , tempLine;
                while(ss >> discardLine) {
                    shortOrigin+=discardLine[0];
                }

                while(nn >> tempLine)
                {
                    shortDest+=tempLine[0];
                }

               */

            vector<Database::Flight> foundFlight = db.getFlights(origin, dest);

            if (foundFlight.empty()) {
              Menu errorMenu({"No flights available. Press Enter to continue."},
                             12, 50);
              errorMenu.strictDisplay();
              //  errorMenu.display(); // Wait for user acknowledgment
              break; // Restart loop in main.cpp
            }

            vector<string> flightOptions;

            for (size_t i = 0; i < foundFlight.size(); ++i) {

              ostringstream cut;
              cut << std::fixed << std::setprecision(2) << foundFlight[i].price;

              flightOptions.push_back(
                  foundFlight[i].flightId + " - " + foundFlight[i].airline +
                  " - " + foundFlight[i].date + " - " +
                  foundFlight[i].departureTime + " - $" + cut.str());
            }

            Menu flightMenu(flightOptions, 12, 50);
            int flightIndex = flightMenu.display();

            if (flightIndex == -1) {
              break;
            }

            Database::Booking bookNow;
            bookNow.flightId = foundFlight[flightIndex].flightId;
            bookNow.airline = foundFlight[flightIndex].airline; // e.g., "Delta"
            bookNow.flightDate = foundFlight[flightIndex].date;
            bookNow.duration = foundFlight[flightIndex].duration;
            bookNow.origin = airportOrigin;    // e.g., "JFK"
            bookNow.dest = airportDestination; // e.g., "LAX"
            bookNow.departureTime = foundFlight[flightIndex].departureTime;

            if (db.userBook(&bookNow)) {
              bookNow.bookingId = db.generateBookingID();

              int totalBaggageCost = 0;
              if (bookNow.baggage > 1) {
                totalBaggageCost = bookNow.baggage * 25;
              }

              bookNow.gmail = loggedGmail;
              bookNow.cost =
                  (foundFlight[flightIndex].price) + totalBaggageCost;

              db.saveBooking(bookNow);

              //    showFlight tempObj(loggedGmail);
              showFlight::ticket(bookNow.bookingId);

              Menu successMenu({"Booking successful! Press Enter to continue."},
                               12, 50);
              successMenu.strictDisplay();
              //  successMenu.display();
              goto backToUserPanel;
            } else {
              Menu cancelMenu({"Booking cancelled. Press Enter to continue."},
                              12, 50);

              cancelMenu.strictDisplay();
              // cancelMenu.display();
              goto backToUserPanel;
              // continue;
            }

          }

          else if (getuser == 1) {

            string ticketId;
            ticketId.clear();

            ticketId = showFlight::displayUserFlight(loggedGmail);
            showFlight::ticket(ticketId);

            goto backToUserPanel;

          }

          else if (getuser == 2) {
            string deleteId;

            deleteId = showFlight::displayUserFlight(loggedGmail);
            showFlight::removeFlight(deleteId);
            goto backToUserPanel;

          } else if (getuser == 3) {
            continue;
          }

          //      break;
        }

      }

      else if (passChoice == 1) { // Admin
        goto adminLogIn;
      } else if (passChoice == 2) { // Cancel
        continue;
      }
      break;
    }

    case 2: { // ADMIN PANEL
    adminLogIn:
      vector<string> logInOptions = {"Admin ID: ", "CODE: ", "Submit",
                                     "Cancel"};
      logIn adminActivate;
      bool hasAdminAccess = adminActivate.adminLogIn(logInOptions);
      loggedAdmin = adminActivate.getAdmin();
      clear();
      refresh();

      if (hasAdminAccess) {
        Menu status({"Admin Log In Successful.", "Press any key to continue"},
                    5, 50);
        status.strictDisplay();

        //         status.display();
      } else {
        Menu status({"Admin Log In Unsuccessful.", "Press any key to continue"},
                    5, 50);
        status.strictDisplay();
        //         status.display();
      }
      break;
    }

    case 3: // EXIT
      endwin();
      //          cout << loggedUser << endl;
      return 0;
    }
  }

  endwin();
  //   cout << loggedUser << endl;
  return 0;
}
