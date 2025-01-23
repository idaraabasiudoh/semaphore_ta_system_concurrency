
# Semaphore Project

This repository contains a project for managing student and teaching assistant (TA) data using semaphores in C. The project demonstrates how to synchronize processes and manage shared resources efficiently using semaphore mechanisms.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Folder Structure](#folder-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

The Semaphore Project is designed to simulate a system for tracking and managing marks assigned to students by multiple teaching assistants (TAs). It showcases synchronization of multiple processes using semaphores to ensure data integrity in concurrent environments.

The project processes input data such as student IDs and their corresponding marks assigned by TAs, ensuring thread-safe operations when updating shared data.

---

## Features

- Implements semaphore-based synchronization in C.
- Handles concurrent access to shared student data by multiple TAs.
- Ensures consistency of student records and marks.
- Supports input from multiple files for student data and TA mark assignments.

---

## Folder Structure

```
Semaphore-Project/
├── student-generator.c      # Source code for generating student data
├── students.txt             # File containing a list of student IDs
├── TA1.txt - TA5.txt        # Files containing marks assigned by different TAs
├── tasystem.c               # Core implementation of the semaphore system
├── tasystem.h               # Header file for semaphore system definitions
└── README.md                # Project documentation (you are here)
```

---

## Getting Started

### Prerequisites

- GCC Compiler (for compiling C programs)
- A Unix-based environment (Linux/MacOS or WSL on Windows)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/semaphore-project.git
   cd semaphore-project
   ```

2. Compile the project:

   ```bash
   gcc -o tasystem tasystem.c student-generator.c -pthread
   ```

3. Prepare the data files (`students.txt`, `TA1.txt` to `TA5.txt`) in the same directory.

---

## Usage

Run the compiled program to process the student and TA data:

```bash
./tasystem
```

The program will:

- Read `students.txt` to load the list of students.
- Process each TA's input file (`TA1.txt` to `TA5.txt`) to retrieve marks.
- Use semaphores to ensure synchronized updates to shared student data.

### Example Input Files

**students.txt**  
A file containing student IDs:
```
7907
0244
0272
7614
0533
...
```

**TA1.txt**  
Marks assigned by TA1 to each student:
```
Student: 7907, Mark: 8
Student: 244, Mark: 7
Student: 272, Mark: 5
...
```

### Output

The program ensures that all TA inputs are processed without conflicts, and the final state of the shared student data is consistent.

---

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request to enhance this project.

### Steps to Contribute:

1. Fork the repository.
2. Create a new feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature description"
   ```
4. Push to your branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---
