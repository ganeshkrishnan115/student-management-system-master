Student Management System (C Language)

A simple file-based Student Management System written in C.
This project demonstrates the use of structures, file handling, and basic CRUD operations in C programming.

📌 Project Overview

This program allows users to:

Add new student records

Modify existing student details

View all students

Search and view individual student records

Delete student records

Automatically calculate CGPA

All data is stored permanently using a binary file (db.txt).

🧱 Student Data Structure

Each student record contains:

Full Name

Department

Roll Number

SGPA for 12 semesters

CGPA (calculated automatically)

CGPA Formula:

CGPA = (Sum of 12 SGPA values) / 12

🛠 Technologies Used

C Programming Language

Structures

File Handling (Binary Mode)

GCC / Turbo C++ Compiler

📂 Project Files

student.c → Main program source code
db.txt → Database file (created automatically after running)
README.md → Project documentation

▶ How to Compile (GCC – Recommended)

Open terminal in the project folder and run:

gcc student.c -o student

Then execute:

./student

▶ How to Compile (Turbo C++)

Open Turbo C++

Open student.c

Press Alt + F9 to compile

Press Ctrl + F9 to run

📋 Menu Options

Add Student

Modify Student

Show All Students

Individual View

Delete Student

Exit

💾 How It Works

Data is stored in db.txt using binary file handling

Each record is saved using fwrite()

Records are read using fread()

Modify and delete operations update the file properly

CGPA is automatically calculated when entering SGPA

🚀 Learning Outcomes

This project helps in understanding:

Structures in C

File handling operations

Binary file storage

Record searching

Data modification techniques

Basic menu-driven programming

🔮 Possible Improvements

Password protection system

Search by name feature

Sorting records

Better UI formatting

MySQL database integration

GUI version

📜 License

This project is for educational and academic purposes.