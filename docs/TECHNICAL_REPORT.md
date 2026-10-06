# PAP521S – PROGRAMMING IN PRACTICE  
## PROJECT A: MUNICIPAL FINANCIAL MANAGEMENT SYSTEM  
### SHORT TECHNICAL REPORT

**Group Number:** Not assigned  

**Group Members:**  
- Joyce Kambonde – 224068520  
- Japhet Nekwiyu – 225001187  
- Condolleeza Da Cruz – 224072773  
- Michael George – 225076462  
- Maharero Joy – 223113964  

---

## 1. Introduction

The Municipal Financial Management System (MFMS) is a console-based application developed in the C programming language. The purpose of the system is to demonstrate the use of fundamental programming concepts while solving a practical municipal financial management problem.

The system allows users to manage employees, departmental budgets, suppliers and municipal assets. It also provides reporting functions that summarise information entered into the system.

The project was developed using ANSI C (C99) and organised into separate source and header files to make the program easier to understand, maintain and test.

---

## 2. Problem Description

Municipal organisations handle information relating to employees, departmental budgets, suppliers and assets. If this information is not properly organised, it becomes difficult to locate records, perform calculations and monitor financial activity.

Manual processes can also result in incorrect calculations, missing information and inconsistent record keeping.

The MFMS was developed as a simple computerised solution that allows municipal information to be entered, stored temporarily, searched and processed through a menu-driven interface.

The system also validates user input to reduce common errors such as negative financial values, invalid menu selections and empty required fields.

---

## 3. System Objectives

The main objectives of the MFMS are to:

- Provide a clear menu-driven interface.
- Allow employee information to be added, displayed and searched.
- Calculate employee salary information.
- Allow departmental budgets and expenditure to be recorded.
- Calculate remaining departmental budgets.
- Identify departments that have exceeded their allocated budgets.
- Manage supplier information.
- Manage municipal asset information.
- Generate reports using the information stored in the system.
- Validate user input and prevent obviously invalid values.
- Demonstrate the practical use of arrays, strings, loops, conditions and functions in C.
- Organise the program into separate modules for easier maintenance and development.

---

## 4. System Features

### Employee Management

The Employee Management module allows users to:

- Add new employees.
- Display employee records.
- Search for employees by name.
- Store employee details such as name, department, basic salary and allowances.
- Calculate the total salary of an employee.

Employee information is stored in an array during program execution.

### Budget Management

The Budget Management module allows users to:

- Add departmental budgets.
- Record expenditure.
- Calculate the remaining budget.
- Determine whether a department is within its budget.
- Identify departments that have exceeded their allocated budget.
- Display departmental budget information.

Duplicate department names are rejected to prevent multiple budget records for the same department.

### Supplier Management

The Supplier Management module allows users to:

- Add suppliers.
- Display supplier information.
- Search for suppliers.
- Store supplier contact and location information.

### Asset Management

The Asset Management module allows users to:

- Add municipal assets.
- Display asset records.
- Search for assets.
- Store information such as asset name, type, value, department and condition.

### Reports

The Reports module provides summaries of information already entered into the system.

Available reports include:

- Employee salary statistics.
- Departmental budget summaries.
- Identification of overspent departments.
- Supplier listings.
- Asset listings.

### Input Validation

Shared validation functions are used throughout the system.

The system checks for:

- Invalid menu options.
- Non-numeric values where numbers are required.
- Negative financial values.
- Empty required text.
- Excessively long text input.
- Numerical overflow.
- Invalid characters following numerical input.

This prevents incorrect data from being stored and improves the reliability of the program.

---

## 5. Program Design

The system uses a modular design in which different functions are divided into separate source and header files.

The main files used in the system are:

- `main.c` – controls the main menu and connects the different modules.
- `employees.c` and `employees.h` – contain employee management functions.
- `budget.c` and `budget.h` – contain departmental budget functions.
- `suppliers.c` and `suppliers.h` – contain supplier management functions.
- `assets.c` and `assets.h` – contain asset management functions.
- `reports.c` and `reports.h` – contain report-generation functions.
- `validation.c` and `validation.h` – contain shared input validation functions.

Arrays are used to store records while the program is running. Loops are used to move through records, while conditions are used to make decisions based on user input and stored values.

C string functions such as `strcmp()` are used when searching and comparing text values.

Functions are used to divide the program into smaller logical operations. This improves readability and allows each module to perform a specific responsibility.

The system currently supports a maximum of:

- 100 employees.
- 20 departmental budgets.
- 100 suppliers.
- 100 assets.

The information is stored in memory while the system is running and is removed when the program closes.

---

## 6. Challenges Encountered

One of the main challenges during development was maintaining consistent input handling across the different modules.

Different methods of reading input could result in problems such as leftover characters affecting the next input field or invalid numerical values being accepted.

Another challenge was ensuring that the different modules could work together correctly after integration.

Additional challenges included:

- Preventing negative financial values.
- Detecting invalid menu input.
- Preventing incomplete records from being stored.
- Managing input that exceeds the maximum allowed field length.
- Handling duplicate departmental budgets.
- Ensuring searches and reports work correctly when no records exist.
- Testing the complete system after all modules were integrated.

---

## 7. Solutions Implemented

Shared validation functions were introduced through `validation.c` and `validation.h`.

These functions provide consistent handling of text, numerical input and menu selections across the system.

The validation functions ensure that:

- Required text fields are not empty.
- Financial values are non-negative and valid.
- Menu selections remain within the available range.
- Excessively long input is rejected.
- Invalid characters after numerical values are detected.
- Incomplete records are not saved when input is interrupted.

The system was also tested using an automated test program located in `tests/test_system.py`.

The test suite compiles the complete application and checks important functionality such as:

- Employee creation and searching.
- Employee salary calculations.
- Departmental budget calculations.
- Overspending detection.
- Supplier and asset management.
- Report generation.
- Invalid menu input.
- Invalid financial input.
- Empty and excessively long text.
- Capacity limits.
- End-of-input handling.

A total of **12 automated integration tests were executed successfully**, confirming that the main functions of the integrated system behave as expected.

The program was also documented through the repository README and supporting documentation to make compilation, testing and system operation easier to understand.

---

## 8. Conclusion

The Municipal Financial Management System successfully demonstrates the use of the C programming concepts covered during the first part of PAP521S.

The system provides functional modules for employee management, departmental budgets, suppliers, assets and reports. It also includes input validation to reduce incorrect data and improve system reliability.

The project demonstrates the practical use of arrays, strings, functions, parameters, loops, conditions, calculations and modular programming.

Although the current version stores information only while the program is running, it provides a strong foundation for future development. Project B can extend the system by introducing features such as permanent data storage, improved searching, editing and deleting records, stronger financial controls and additional reporting functionality.
