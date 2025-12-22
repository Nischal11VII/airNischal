# Flight System

This is a college project for booking airplane flights. The project provides an interactive terminal-based application where users can sign up, log in, and book flights. The system ensures that only authenticated users can access the booking functionality, making it a secure and user-friendly solution for flight management.

## Main Features

- **Terminal-based UI with ncurses:**  
  The project utilizes the [ncurses](https://www.gnu.org/software/ncurses/) library to create an interactive and visually appealing text-based user interface. This makes navigation through the system smooth and intuitive.

- **User Authentication:**  
  Users must sign up and log in to access the booking features. This ensures that only registered users can book flights, adding a layer of security and personalization.

- **Flight Booking:**  
  Authenticated users can book flights by providing necessary information through guided input forms. The system collects all required details to complete the booking process.

- **CSV File Integration:**  
  The project stores and retrieves data using `.csv` files. User information, flight details, and bookings are managed through these files, allowing for easy data management and portability. The system links with multiple CSV files to ensure consistency and seamless data sharing between different modules (for example, user accounts and flight records).

- **Input Validation:**  
  The system performs input validation to ensure that all provided information is correct and complete before confirming bookings.

- **Separation of Concerns:**  
  Different functionalities such as authentication, booking, and data handling are organized into separate modules/files, making the codebase maintainable and easy to extend.

## Project Characteristics

- **Interactive:**  
  Engaging terminal-based interface using ncurses for a better user experience.

- **Secure:**  
  Only registered and logged-in users can make bookings.

- **Modular:**  
  The codebase is structured for clarity and maintainability, with separate modules for core features.

- **Data-driven:**  
  Utilizes CSV files for persistent storage, making it easy to view and manage data externally if needed.

- **User-centric:**  
  Focused on ease of use with guided input and clear prompts for every action.

## Getting Started

1. **Install Dependencies:**  
   Make sure to install `ncurses` and any other required libraries.

   ```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```

2. **Clone the Repository:**  
   ```bash
   git clone https://github.com/Nischal117/flightSystem.git
   cd flightSystem
   ```

3. **Build and Run:**  
   Follow the build instructions provided in the code or `Makefile` (if available).

## Usage

- Launch the application.
- Sign up for a new account or log in with existing credentials.
- Browse available flights and book a flight by filling in the required details.
- All user and booking information is securely stored in CSV files.

## Notes

- Ensure that the CSV files are accessible and writable by the application.
- For any issues or feature requests, feel free to open an issue in this repository.

---

> **This project was created as a part of a college assignment and demonstrates practical usage of Cpp programming, ncurses library, file handling, and user authentication in a real-world scenario.**
