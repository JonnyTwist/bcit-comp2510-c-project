# Hospital Management System

This project simulates a hospital management system, designed to 
manage patients, doctors, and doctor schedules. It includes features 
such as patient and doctor management, report generation, and doctor 
schedule handling.

## Description

Developed as part of COMP 2510 at BCIT, the system demonstrates 
structured programming in C, file handling, and modular program design. 
The program utilizes a combination of file manipulation, linked lists, 
and reporting mechanisms to simulate real-world hospital management scenarios.

### Features
* Patient Management: Manage patient records and report generation for admitted and discharged patients.
* Doctor Management: Manage doctor information, including doctor utilization and schedules.
* Schedule Management: Maintain and manipulate doctor schedules for the week.
* Reports: Generate reports related to room utilization, doctor schedules, and patient status.
* Session persistence:  All data is saved across sessions to ensure that patient, doctor, and schedule information is retained even after the program is closed.

## Contributors
* Nikooff25
* Jonny Twist

## Installation Instructions

### Prerequisites

- GCC compiler (or any C compiler)
- Make

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/Nikooff25/bcit-comp2510-c-project.git
   ```
You can open the project folder in any C-compatible IDE such as VS Code, CLion, or 
Code::Blocks to follow the same build and run steps below in a graphical environment.
Alternatively, continue using the terminal directly.

2. Compile the program using make
   ```bash
      make
   ```
3. Run the executable
   ```bash
      ./manage_hosp
   ```
4. Follow Terminal Instructions for using the program

5. Once finished clean up compiled files
   ```bash
   make clean
   ```

## Known Bugs and Limitations
A few spots could use better input sanitization and a few others could use
buffer clearing after invalid input is received.

## Contents of Folder
Please note that not all txt or bin files will be available immediately off GitHub
but will be generated with use of the program

```
├── .gitattributes            # Git attributes configuration
├── .gitignore                # Git ignore rules
├── admittedReport.txt        # Report of currently admitted patients over specified time spans
├── CMakeLists.txt            # CMake build script (if applicable)
├── dischargedReport.txt      # Report of discharged patients on a specified day
├── doctorsData.bin           # Binary data file storing doctor records
├── doctorsDataBackup.bin     # Backup of doctorsData.bin
├── doctorUtilReport.txt      # Doctor utilization report
├── dsm.c                     # The doctor schedule management system to manage doctors and the schedule
├── dsm.h                     # Header for dsm.c
├── file_m.c                  # File manipulation functions
├── file_m.h                  # Header for file_m.c
├── list.c                    # Implementation of linked list functions
├── list.h                    # Header for list.c
├── main.c                    # Main entry point for the application
├── Makefile                  # Build instructions for GCC/Make
├── patient.c                 # Patient-related logic
├── patient.h                 # Header for patient.c
├── patientData.bin           # Binary file containing patient records
├── patientDataBackup.bin     # Backup of patient data
├── README.md                 # Project readme file
├── report.c                  # Report generation logic
├── report.h                  # Header for report.c
├── roomUtilReport.txt        # Room utilization report
├── test                      # Test output file (not used in main route)
├── test.bin                  # Test binary data file (not used in main route)
├── test.c                    # Contains test code and tests to test other code at a larger scale (not used in main route)
├── test.h                    # Header for test.c (not used in main route)
├── testroomreport.txt        # Room utilization test output (not used in main route)
```

## Acknowledgements
This project was completed as part of the British Columbia Institute of Technology's
Computer Systems Technology (CST) program. The specific course was COMP 2510 Procedural
Programming taught by Ayesha Anzer.