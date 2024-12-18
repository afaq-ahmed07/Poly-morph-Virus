# Polymorphic Virus for Linux (Ubuntu)

## Overview
This project is a polymorphic virus designed for educational purposes to demonstrate file manipulation, encryption, and basic antivirus evasion techniques. The virus scans a specified folder, renames and encrypts targeted files, modifies their permissions, and appends junk bytes to its binary to evade detection.

---

## Features
- **File Scanning:** Searches a specified folder for files containing a specific letter in their names.
- **File Renaming:** Renames matching files to a user-specified name.
- **Encryption:** Encrypts files using XOR encryption for obfuscation.
- **Permission Modification:** Changes file permissions to make them inaccessible.
- **Antivirus Evasion:** Adds junk bytes to the virus binary after execution to evade detection by simple antivirus tools.

---

## Requirements
- Linux (Ubuntu or similar distributions)
- GCC (GNU Compiler Collection) for compiling the program

---

## How to Run
1. Clone the repository or download the source code.
2. Open a terminal and navigate to the folder containing the source code.
3. Compile the program using GCC:
   ```bash
   gcc -c main.c -o main.o
  ```bash
   gcc main.o -o main
