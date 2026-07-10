

ELECTRICITY BILL GENERATOR SYSTEM



---

# 1. Project Information

| Field                    | Details                                 |
| ------------------------ | --------------------------------------- |
| **Project Name**         | Electricity Bill Generator System       |
| **Programming Language** | C                                       |
| **Intern Name**          | **Abantika Sen**                    |
| **Intern ID**            | **CITS4804**                    |
| **No. of Weeks**         |  4 Weeks  |
| **Organization**         | CODTECH IT SOLUTIONS PRIVATE LIMITED              |
| **Submission Date**      |10 /07/26            |

---

# 2. Project Scope

The **Electricity Bill Generator System** is a console-based application developed using the C programming language to automate the process of electricity bill management. The system calculates electricity charges based on slab-wise tariff rates, stores customer billing information permanently using binary file handling, generates detailed receipts, and provides options to view, search, update, and delete customer records. The project demonstrates the practical implementation of file handling, structures, functions, modular programming, and input validation in C.

---

# 3. Project Overview

The Electricity Bill Generator System is a menu-driven application that helps electricity providers or users generate accurate electricity bills quickly and efficiently. It automatically calculates the bill amount using slab-wise tariff rates, adds fixed meter charges and taxes, stores customer details in a binary file, and generates printable receipts.

The project is designed to demonstrate the practical application of C programming concepts including structures, functions, modular programming, binary file handling, dynamic memory allocation, and input validation. 

---

# 4. Objectives

4.1. Automate electricity bill generation.

4.2. Calculate electricity charges using slab-wise rates.

4.3. Store customer billing information permanently.

4.4. Search customer records using Consumer Number.

4.5. Update existing customer records.

4.6. Delete customer billing records.

4.7. Generate printable receipts.

4.8. Demonstrate file handling and modular programming concepts in C.

---

# 5. Features

i) Generate New Bill

ii) View All Bills

iii) Search Bill by Consumer Number

iv) Update Existing Bill

v) Delete Bill

vi) Slab-wise Electricity Charge Calculation

vii) Automatic Tax Calculation

viii) Fixed Meter Rent Calculation

ix) Binary File Storage

x) Receipt Generation

xi) Input Validation

xii) User-friendly Menu Interface

---

 # 6. Technologies Used

* i) Programming Language: **C**
*ii) Compiler: **GCC / MinGW GCC**
  * iii)IDE:

   * Visual Studio Code
   * CodeBlocks
   * Dev-C++
iv) File Handling: Binary Files

v) Operating System: Windows

---

# 7. Project Structure

``
Electricity_Bill_Generator/
│
├── main.c
├── bills.dat
├── Receipt_101.txt
├── Receipt_102.txt
├── README.md
├── screenshots/
│   ├── menu.png
│   ├── generate_bill.png
│   ├── view_bill.png
│   ├── search_bill.png
│   ├── update_bill.png
│   ├── delete_bill.png
│   └── receipt.png
├── output_images/
│   ├── output1.png
│   ├── output2.png
│   └── output3.png
└── Documentation.pdf
`

---

# 8. File Description

 8.1 main.c

Contains the complete source code of the application.

8.2 bills.dat

Stores all customer billing records permanently using binary file handling.

 8.3 Receipt_XXX.txt

Automatically generated receipt for each customer.

8.4 screenshots/

Contains screenshots of different program operations.

 8.5 output_images/

Contains screenshots of the final outputs.

 8.6 Documentation.pdf

Contains the detailed project documentation.

 8.7 README.md

Contains project description and usage instructions.

---

# 9. Code Structure

The project is divided into several modules for better readability and maintenance.

 9.1 Header Files

The following header files are used:

``
stdio.h
stdlib.h
string.h
`

Purpose:

1. Input and Output Operations
2. Memory Management
3. String Manipulation

---

 9.2 Constant Definitions

The program defines constants using `#define` for:

1. Data file name
2. Meter rent
3. Tax percentage
4. Slab limits
5. Slab rates
6. Maximum sizes of strings

This makes the code reusable and easier to modify.

---

 9.3 Structure (Bill)

A structure named **Bill** stores all customer details.

It contains:

1. Consumer Number
2. Customer Name
3. Address
4. Phone Number
5. Billing Month
6. Previous Meter Reading
7. Current Meter Reading
8. Units Consumed
9. Energy Charges
10. Fixed Charges
11. Tax
12. Total Amount

---

 9.4 Function Prototypes

The program is modularized into separate functions.

Functions include:

1. calculateEnergyCharges()
2. generateBill()
3. viewAllBills()
4. searchBill()
5. updateBill()
6. deleteBill()
7. printReceipt()
8. saveReceiptToFile()
9. loadAllBills()
10. getValidInt()
11. getValidFloat()
12. readLine()
13. clearInputBuffer()

---

 9.5 Main Function

The application begins execution from the `main()` function.

The main function continuously displays the menu until the user chooses Exit.

Menu Options:

1. Generate New Bill
2. View All Bills
3. Search Bill
4. Update Bill
5. Delete Bill
6. Exit

---

 # 10. Working of the Code

 Step 1

The program starts and displays the main menu.

 Step 2

The user selects one of the available operations.

 Step 3

If **Generate Bill** is selected:

1. Customer details are entered.
2. Previous meter reading is entered.
3. Current meter reading is entered.

 Step 4

Units consumed are calculated.

``
Units Consumed =
Current Reading − Previous Reading
`

 Step 5

Energy charges are calculated using slab-wise tariff rates.

### Step 6

Fixed meter rent is added.
 Step 7

Tax is calculated.

 Step 8

The final bill amount is calculated.

 Step 9

Customer information is saved in **bills.dat**.

 Step 10

The receipt is displayed.

 Step 11

The receipt is automatically saved as:

```
Receipt_<ConsumerNumber>.txt
```

---

# 11. Electricity Bill Calculation

Slab Rates

| Units     | Rate           |
| --------- | -------------- |
| 0–100     | ₹3.50 per unit |
| 101–200   | ₹4.50 per unit |
| 201–300   | ₹6.00 per unit |
| Above 300 | ₹7.50 per unit |
  Additional Charges

1. Fixed Meter Rent = ₹50
2. Tax = 5%

 Formula

``
Total Amount =
Energy Charges
+ Meter Rent
+ Tax
``

---

# 12. File Handling

The application uses binary file handling.

### Saving Records

Uses:

```
fwrite()
```

 Reading Records

Uses:

```
fread()
```

 Updating Records

1. Load all records.
2. Modify selected record.
3. Rewrite the binary file.

### Deleting Records

1. Load all records.
2. Remove selected record.
3. Rewrite updated records.

---

# 13. Receipt Generation

After bill generation:

1. Receipt is displayed on the console.
2. Receipt is saved automatically.

Example:

```
Receipt_101.txt
```

---

# 14. Input Validation

The application validates:

1. Integer inputs
2. Floating-point inputs
3. Negative values
4. Invalid meter readings
5. Incorrect user input

---

# 15. Function Description

| Function                 | Description                         |
| ------------------------ | ----------------------------------- |
| calculateEnergyCharges() | Calculates slab-wise energy charges |
| generateBill()           | Generates a new electricity bill    |
| viewAllBills()           | Displays all stored records         |
| searchBill()             | Searches a customer bill            |
| updateBill()             | Updates customer details            |
| deleteBill()             | Deletes a customer record           |
| printReceipt()           | Prints formatted receipt            |
| saveReceiptToFile()      | Saves receipt as a text file        |
| loadAllBills()           | Loads records from the binary file  |
| getValidInt()            | Validates integer input             |
| getValidFloat()          | Validates decimal input             |
| readLine()               | Reads string input safely           |
| clearInputBuffer()       | Clears invalid input                |

---

#16. How to Compile

Open the terminal and compile using GCC:

```bash
gcc main.c -o bill_generator
```

---

# 17. How to Run

### Windows

```bash
bill_generator.exe
```

### Linux/macOS

```bash
./bill_generator
```

---

 * Running in Visual Studio Code

* Install GCC (MinGW or MSYS2).
* Open the project folder in Visual Studio Code.
* Open **main.c**.
* Open the integrated terminal.
* Compile the project:

``bash
gcc main.c -o bill_generator
* Run:

```bash
bill_generator.exe
```

---

You can add the following section to your **README.md** under **"Program Output"** or **"Sample Execution"**.

---

# 18. Sample Program Output

## 18.1 Main Menu

``
=========================================================
          ELECTRICITY BILL GENERATOR SYSTEM
=========================================================

1. Generate New Bill
2. View All Bills
3. Search Bill by Consumer Number
4. Update Bill
5. Delete Bill
6. Exit

Enter your choice (1-6):
`

---

## 18.2 Generate New Bill (Consumer 101)

``
Enter your choice (1-6): 1

--- Enter Customer & Meter Details ---

Consumer Number            : 101
Customer Name              : Avni Sen
Address                    : Kolkata
Phone Number               : 987644
Billing Month              : June
Previous Meter Reading     : 1250
Current Meter Reading      : 1500

Bill generated successfully!
`

### Generated Receipt

``
=========================================================
               ELECTRICITY BILL RECEIPT
=========================================================

Consumer Number   : 101
Customer Name     : Avni Sen
Address           : Kolkata
Phone Number      : 987644
Billing Month     : June

---------------------------------------------------------

Previous Reading  : 1250.0 units
Current Reading   : 1500.0 units
Units Consumed    : 250.0 units

---------------------------------------------------------

Energy Charges    : Rs. 1100.00
Fixed/Meter Rent  : Rs. 50.00
Tax (5%)          : Rs. 57.50

---------------------------------------------------------

TOTAL AMOUNT DUE  : Rs. 1207.50

=========================================================

Receipt saved as "Receipt_101.txt"
``

---

## 18.3 Generate Another Bill (Consumer 102)

``
Enter your choice (1-6): 1

Consumer Number            : 102
Customer Name              : Bumba Roy
Address                    : Mumbai
Phone Number               : 896754
Billing Month              : July
Previous Meter Reading     : 1200
Current Meter Reading      : 1450

Bill generated successfully!
``

 Generated Receipt

``
=========================================================
               ELECTRICITY BILL RECEIPT
=========================================================

Consumer Number   : 102
Customer Name     : Bumba Roy
Address           : Mumbai
Phone Number      : 896754
Billing Month     : July

Previous Reading  : 1200.0 units
Current Reading   : 1450.0 units
Units Consumed    : 250.0 units

Energy Charges    : Rs. 1100.00
Fixed/Meter Rent  : Rs. 50.00
Tax (5%)          : Rs. 57.50

TOTAL AMOUNT DUE  : Rs. 1207.50

Receipt saved as "Receipt_102.txt"
``

---

## 18.4 View All Bills

``
Enter your choice (1-6): 2

Consumer#   Name           Month    Units    Total (Rs)
--------------------------------------------------------
101         Avni Sen       June     250.0    1207.50
102         Bumba Roy      July     250.0    1207.50
--------------------------------------------------------

Total Records: 2
``

---

## 18.5 Search Bill

``
Enter your choice (1-6): 3

Enter Consumer Number to search: 101

=========================================================
               ELECTRICITY BILL RECEIPT
=========================================================

Consumer Number   : 101
Customer Name     : Avni Sen
Address           : Kolkata
Phone Number      : 987644
Billing Month     : June

Previous Reading  : 1250.0 units
Current Reading   : 1500.0 units
Units Consumed    : 250.0 units

Energy Charges    : Rs. 1100.00
Fixed/Meter Rent  : Rs. 50.00
Tax (5%)          : Rs. 57.50

TOTAL AMOUNT DUE  : Rs. 1207.50
``

---

## 18.6 Update Bill
 

``
Enter your choice (1-6): 4

Enter Consumer Number to update: 102

Existing record found for Bumba Roy.

New Previous Meter Reading : 1568
New Current Meter Reading  : 1700

Bill updated successfully!
``
 Updated Receipt

``
=========================================================
               ELECTRICITY BILL RECEIPT
=========================================================

Consumer Number   : 102
Customer Name     : Bumba Roy
Address           : Mumbai
Phone Number      : 896754
Billing Month     : July

Previous Reading  : 1568.0 units
Current Reading   : 1700.0 units
Units Consumed    : 132.0 units

Energy Charges    : Rs. 494.00
Fixed/Meter Rent  : Rs. 50.00
Tax (5%)          : Rs. 27.20

TOTAL AMOUNT DUE  : Rs. 571.20

Receipt saved as "Receipt_102.txt"
``

---

##18.7 Delete Bill


`
Enter your choice (1-6): 5

Enter Consumer Number to delete: 101

Record for Consumer Number 101 deleted successfully.
``

---

## 18.8 Exit Program
 

``
Enter your choice (1-6): 6

Thank you for using the system.
Goodbye!
``

---

This section can be placed after **"How to Run the Program"** and before **"Future Enhancements"** in your README. It documents the complete execution flow of your application in a professional format.

---

# 19. Future Enhancements

1. User Login Authentication
2. 
3. MySQL Database Integration
4. 
5. Graphical User Interface (GUI)
6. 
7. PDF Bill Generation
8. 
9. Online Payment Integration
10. 
11. SMS/Email Notifications
12. 
13. Monthly Billing Reports
14. 
15. Customer Payment Tracking

---

# 20. Learning Outcomes

After completing this project, the following concepts are demonstrated:

20.1. C Programming

20.2. Modular Programming

20.3. Structures

20.4. Functions

20.5. Binary File Handling

20.6. Dynamic Memory Allocation

20.7. Input Validation

20.8. Menu-Driven Programming

20.9. File Management

20.10. Real-world Billing System Development

---



---

# 21. Conclusion

The Electricity Bill Generator System is a simple, reliable, and efficient console-based application that automates electricity bill generation using slab-wise tariff calculations. It supports complete CRUD (Create, Read, Update, Delete) operations, securely stores customer records using binary file handling, and generates printable receipts. This project demonstrates practical implementation of fundamental C programming concepts and serves as an excellent academic and internship project.

---

