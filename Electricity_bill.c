/* =========================================================================
   ELECTRICITY BILL GENERATOR SYSTEM
   ---------------------------------
  
   ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------ CONFIG --------------------------------- */
#define DATA_FILE        "bills.dat"
#define METER_RENT       50.00f      /* fixed monthly meter rent            */
#define TAX_RATE         0.05f       /* 5% tax on (energy + fixed charges)  */
#define SLAB1_LIMIT      100
#define SLAB2_LIMIT      200
#define SLAB3_LIMIT      300
#define SLAB1_RATE       3.50f
#define SLAB2_RATE       4.50f
#define SLAB3_RATE       6.00f
#define SLAB4_RATE       7.50f
#define NAME_LEN         50
#define ADDR_LEN         100
#define PHONE_LEN        15
#define MONTH_LEN        20
/* ------------------------------------------------------------------------ */

typedef struct {
    int   consumerNo;
    char  name[NAME_LEN];
    char  address[ADDR_LEN];
    char  phone[PHONE_LEN];
    char  billMonth[MONTH_LEN];
    float previousReading;
    float currentReading;
    float unitsConsumed;
    float energyCharges;
    float fixedCharges;
    float tax;
    float totalAmount;
} Bill;

/* --------------------------- FUNCTION PROTOTYPES ------------------------ */
float calculateEnergyCharges(float units);
void  generateBill(void);
void  viewAllBills(void);
void  searchBill(void);
void  updateBill(void);
void  deleteBill(void);
void  printReceipt(const Bill *b);
void  saveReceiptToFile(const Bill *b);
int   getValidInt(const char *prompt);
float getValidFloat(const char *prompt, float minValue);
void  clearInputBuffer(void);
void  readLine(char *buffer, int size);
Bill *loadAllBills(int *count);
void  pauseScreen(void);

/* ------------------------------- MAIN ------------------------------------ */
int main(void) {
    int choice;

    do {
        printf("\n===================================================\n");
        printf("       ELECTRICITY BILL GENERATOR SYSTEM\n");
        printf("===================================================\n");
        printf(" 1. Generate New Bill\n");
        printf(" 2. View All Bills\n");
        printf(" 3. Search Bill by Consumer Number\n");
        printf(" 4. Update Bill\n");
        printf(" 5. Delete Bill\n");
        printf(" 6. Exit\n");
        printf("===================================================\n");

        choice = getValidInt("Enter your choice (1-6): ");

        switch (choice) {
            case 1: generateBill();   break;
            case 2: viewAllBills();   break;
            case 3: searchBill();     break;
            case 4: updateBill();     break;
            case 5: deleteBill();     break;
            case 6: printf("\nThank you for using the system. Goodbye!\n"); break;
            default: printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

/* ---------------------------------------------------------------------
   calculateEnergyCharges
   Applies slab-wise tariff calculation on the units consumed.
   --------------------------------------------------------------------- */
float calculateEnergyCharges(float units) {
    float charge = 0.0f;

    if (units <= 0) {
        return 0.0f;
    }

    if (units <= SLAB1_LIMIT) {
        charge = units * SLAB1_RATE;
    } else if (units <= SLAB2_LIMIT) {
        charge = (SLAB1_LIMIT * SLAB1_RATE) +
                 ((units - SLAB1_LIMIT) * SLAB2_RATE);
    } else if (units <= SLAB3_LIMIT) {
        charge = (SLAB1_LIMIT * SLAB1_RATE) +
                 ((SLAB2_LIMIT - SLAB1_LIMIT) * SLAB2_RATE) +
                 ((units - SLAB2_LIMIT) * SLAB3_RATE);
    } else {
        charge = (SLAB1_LIMIT * SLAB1_RATE) +
                 ((SLAB2_LIMIT - SLAB1_LIMIT) * SLAB2_RATE) +
                 ((SLAB3_LIMIT - SLAB2_LIMIT) * SLAB3_RATE) +
                 ((units - SLAB3_LIMIT) * SLAB4_RATE);
    }
    return charge;
}

/* ---------------------------------------------------------------------
   generateBill
   Collects customer + meter reading details, computes the bill, appends
   the record to the binary data file, prints and saves the receipt.
   --------------------------------------------------------------------- */
void generateBill(void) {
    Bill b;
    FILE *fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("\nError: could not open data file for writing.\n");
        return;
    }

    printf("\n--- Enter Customer & Meter Details ---\n");

    b.consumerNo = getValidInt("Consumer Number: ");

    printf("Customer Name      : ");
    readLine(b.name, NAME_LEN);

    printf("Address            : ");
    readLine(b.address, ADDR_LEN);

    printf("Phone Number       : ");
    readLine(b.phone, PHONE_LEN);

    printf("Billing Month (e.g. July 2026): ");
    readLine(b.billMonth, MONTH_LEN);

    b.previousReading = getValidFloat("Previous Meter Reading (units): ", 0.0f);
    b.currentReading  = getValidFloat("Current Meter Reading (units) : ", b.previousReading);

    b.unitsConsumed  = b.currentReading - b.previousReading;
    b.energyCharges  = calculateEnergyCharges(b.unitsConsumed);
    b.fixedCharges   = METER_RENT;
    b.tax            = (b.energyCharges + b.fixedCharges) * TAX_RATE;
    b.totalAmount    = b.energyCharges + b.fixedCharges + b.tax;

    fwrite(&b, sizeof(Bill), 1, fp);
    fclose(fp);

    printf("\nBill generated successfully!\n");
    printReceipt(&b);
    saveReceiptToFile(&b);
}

/* ---------------------------------------------------------------------
   viewAllBills
   Reads every record from the data file and displays it as a table.
   --------------------------------------------------------------------- */
void viewAllBills(void) {
    int count = 0;
    Bill *bills = loadAllBills(&count);

    if (bills == NULL || count == 0) {
        printf("\nNo bills found. Please generate a bill first.\n");
        free(bills);
        return;
    }

    printf("\n%-10s %-20s %-12s %-10s %-12s\n",
           "Consumer#", "Name", "Month", "Units", "Total (Rs)");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-12s %-10.1f %-12.2f\n",
               bills[i].consumerNo, bills[i].name, bills[i].billMonth,
               bills[i].unitsConsumed, bills[i].totalAmount);
    }
    printf("---------------------------------------------------------------\n");
    printf("Total records: %d\n", count);

    free(bills);
}

/* ---------------------------------------------------------------------
   searchBill
   Looks up a bill by consumer number and prints its full receipt.
   --------------------------------------------------------------------- */
void searchBill(void) {
    int target = getValidInt("\nEnter Consumer Number to search: ");
    int count = 0;
    Bill *bills = loadAllBills(&count);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (bills[i].consumerNo == target) {
            printReceipt(&bills[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo bill found for Consumer Number %d.\n", target);
    }

    free(bills);
}

/* ---------------------------------------------------------------------
   updateBill
   Lets the user re-enter meter readings for an existing consumer and
   recalculates the bill, rewriting the entire data file.
   --------------------------------------------------------------------- */
void updateBill(void) {
    int target = getValidInt("\nEnter Consumer Number to update: ");
    int count = 0;
    Bill *bills = loadAllBills(&count);
    int found = -1;

    for (int i = 0; i < count; i++) {
        if (bills[i].consumerNo == target) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nNo bill found for Consumer Number %d.\n", target);
        free(bills);
        return;
    }

    printf("\nExisting record found for %s. Enter new meter readings.\n", bills[found].name);
    bills[found].previousReading = getValidFloat("New Previous Meter Reading (units): ", 0.0f);
    bills[found].currentReading  = getValidFloat("New Current Meter Reading (units) : ",
                                                  bills[found].previousReading);

    bills[found].unitsConsumed = bills[found].currentReading - bills[found].previousReading;
    bills[found].energyCharges = calculateEnergyCharges(bills[found].unitsConsumed);
    bills[found].fixedCharges  = METER_RENT;
    bills[found].tax           = (bills[found].energyCharges + bills[found].fixedCharges) * TAX_RATE;
    bills[found].totalAmount   = bills[found].energyCharges + bills[found].fixedCharges + bills[found].tax;

    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        printf("\nError: could not open data file for writing.\n");
        free(bills);
        return;
    }
    fwrite(bills, sizeof(Bill), count, fp);
    fclose(fp);

    printf("\nBill updated successfully!\n");
    printReceipt(&bills[found]);
    saveReceiptToFile(&bills[found]);

    free(bills);
}

/* ---------------------------------------------------------------------
   deleteBill
   Removes a record matching the given consumer number.
   --------------------------------------------------------------------- */
void deleteBill(void) {
    int target = getValidInt("\nEnter Consumer Number to delete: ");
    int count = 0;
    Bill *bills = loadAllBills(&count);
    int found = -1;

    for (int i = 0; i < count; i++) {
        if (bills[i].consumerNo == target) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nNo bill found for Consumer Number %d.\n", target);
        free(bills);
        return;
    }

    for (int i = found; i < count - 1; i++) {
        bills[i] = bills[i + 1];
    }
    count--;

    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        printf("\nError: could not open data file for writing.\n");
        free(bills);
        return;
    }
    if (count > 0) {
        fwrite(bills, sizeof(Bill), count, fp);
    }
    fclose(fp);

    printf("\nRecord for Consumer Number %d deleted successfully.\n", target);
    free(bills);
}

/* ---------------------------------------------------------------------
   printReceipt
   Displays a nicely formatted receipt on the console.
   --------------------------------------------------------------------- */
void printReceipt(const Bill *b) {
    printf("\n=========================================================\n");
    printf("                  ELECTRICITY BILL RECEIPT\n");
    printf("=========================================================\n");
    printf("Consumer Number   : %d\n", b->consumerNo);
    printf("Customer Name     : %s\n", b->name);
    printf("Address           : %s\n", b->address);
    printf("Phone Number      : %s\n", b->phone);
    printf("Billing Month     : %s\n", b->billMonth);
    printf("---------------------------------------------------------\n");
    printf("Previous Reading  : %.1f units\n", b->previousReading);
    printf("Current Reading   : %.1f units\n", b->currentReading);
    printf("Units Consumed    : %.1f units\n", b->unitsConsumed);
    printf("---------------------------------------------------------\n");
    printf("Energy Charges    : Rs. %.2f\n", b->energyCharges);
    printf("Fixed/Meter Rent  : Rs. %.2f\n", b->fixedCharges);
    printf("Tax (%.0f%%)         : Rs. %.2f\n", TAX_RATE * 100, b->tax);
    printf("---------------------------------------------------------\n");
    printf("TOTAL AMOUNT DUE  : Rs. %.2f\n", b->totalAmount);
    printf("=========================================================\n");
}

/* ---------------------------------------------------------------------
   saveReceiptToFile
   Writes the receipt to a uniquely named text file, e.g. Receipt_101.txt
   --------------------------------------------------------------------- */
void saveReceiptToFile(const Bill *b) {
    char filename[40];
    snprintf(filename, sizeof(filename), "Receipt_%d.txt", b->consumerNo);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("\nWarning: could not save receipt file.\n");
        return;
    }

    fprintf(fp, "=========================================================\n");
    fprintf(fp, "                  ELECTRICITY BILL RECEIPT\n");
    fprintf(fp, "=========================================================\n");
    fprintf(fp, "Consumer Number   : %d\n", b->consumerNo);
    fprintf(fp, "Customer Name     : %s\n", b->name);
    fprintf(fp, "Address           : %s\n", b->address);
    fprintf(fp, "Phone Number      : %s\n", b->phone);
    fprintf(fp, "Billing Month     : %s\n", b->billMonth);
    fprintf(fp, "---------------------------------------------------------\n");
    fprintf(fp, "Previous Reading  : %.1f units\n", b->previousReading);
    fprintf(fp, "Current Reading   : %.1f units\n", b->currentReading);
    fprintf(fp, "Units Consumed    : %.1f units\n", b->unitsConsumed);
    fprintf(fp, "---------------------------------------------------------\n");
    fprintf(fp, "Energy Charges    : Rs. %.2f\n", b->energyCharges);
    fprintf(fp, "Fixed/Meter Rent  : Rs. %.2f\n", b->fixedCharges);
    fprintf(fp, "Tax (%.0f%%)         : Rs. %.2f\n", TAX_RATE * 100, b->tax);
    fprintf(fp, "---------------------------------------------------------\n");
    fprintf(fp, "TOTAL AMOUNT DUE  : Rs. %.2f\n", b->totalAmount);
    fprintf(fp, "=========================================================\n");

    fclose(fp);
    printf("Receipt saved as \"%s\"\n", filename);
}

/* ---------------------------------------------------------------------
   loadAllBills
   Loads every Bill record from the data file into a dynamically
   allocated array. Caller is responsible for calling free() on it.
   Sets *count to the number of records read (0 if file is empty/missing).
   --------------------------------------------------------------------- */
Bill *loadAllBills(int *count) {
    FILE *fp = fopen(DATA_FILE, "rb");
    *count = 0;

    if (fp == NULL) {
        return NULL;   /* file doesn't exist yet -> no bills */
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    int recordCount = (int)(fileSize / sizeof(Bill));
    if (recordCount <= 0) {
        fclose(fp);
        return NULL;
    }

    Bill *bills = (Bill *)malloc(recordCount * sizeof(Bill));
    if (bills == NULL) {
        printf("\nMemory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    size_t readCount = fread(bills, sizeof(Bill), recordCount, fp);
    fclose(fp);

    *count = (int)readCount;
    return bills;
}

/* ------------------------- INPUT HELPER FUNCTIONS ------------------------ */

/* Clears leftover characters (including newline) from stdin */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Safely reads a line of text into buffer, stripping the trailing newline */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

/* Repeatedly prompts until the user enters a valid integer */
int getValidInt(const char *prompt) {
    int value;
    char extra;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d%c", &value, &extra);
        if (result == EOF) {
            printf("\nNo more input received. Exiting.\n");
            exit(0);
        }
        if (result == 2 && extra == '\n') {
            return value;
        }
        printf("Invalid input! Please enter a whole number.\n");
        clearInputBuffer();
    }
}

/* Repeatedly prompts until the user enters a valid float >= minValue */
float getValidFloat(const char *prompt, float minValue) {
    float value;
    char extra;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%f%c", &value, &extra);
        if (result == EOF) {
            printf("\nNo more input received. Exiting.\n");
            exit(0);
        }
        if (result == 2 && extra == '\n' && value >= minValue) {
            return value;
        }
        printf("Invalid input! Please enter a number >= %.1f.\n", minValue);
        clearInputBuffer();
    }
}