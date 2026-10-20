#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// ============================================================================
// SYSTEM FUNCTION PROTOTYPES
// ============================================================================
void displayMainMenu();
void recordTransactions(int &totalTransactions, double &grossRevenue, 
                        double &highestSale, double &lowestSale, bool &isFirstTransaction,
                        int &countGrocery, double &subGrocery,
                        int &countBeverages, double &subBeverages,
                        int &countGeneral, double &subGeneral);
void viewShiftSnapshot(int totalTransactions, double grossRevenue);
void printFinalAudit(int totalTransactions, double grossRevenue, 
                     double highestSale, double lowestSale,
                     int countGrocery, double subGrocery,
                     int countBeverages, double subBeverages,
                     int countGeneral, double subGeneral);

// ============================================================================
// MAIN APPLICATION CONTROLLER
// ============================================================================
int main() {
    // ---- System State Variables ----
    int menuChoice = 0;
    
    // Core Accumulators & Counters
    int totalTransactions = 0;
    double grossRevenue = 0.0;
    
    // Extremes Tracking Variables
    double highestSale = 0.0;
    double lowestSale = 0.0;
    bool isFirstTransaction = true; // Prevents min/max tracker from locking at 0.00

    // Category Counters and Sub-Accumulators
    int countGrocery = 0, countBeverages = 0, countGeneral = 0;
    double subGrocery = 0.0, subBeverages = 0.0, subGeneral = 0.0;

    // Fixed Global Formatting for Double Output
    cout << fixed << setprecision(2);

    // ---- Main Persistent System Loop ----
    do {
        displayMainMenu();
        cout << "Enter choice (1-4): ";
        
        // Input validation loop for main menu selection
        if (!(cin >> menuChoice) || menuChoice < 1 || menuChoice > 4) {
            cout << "\n[ERROR] Invalid menu choice. Please select an option between 1 and 4.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue; 
        }

        // ---- Processing Menu Selections ----
        switch (menuChoice) {
            case 1:
                // Variables passed by reference (&) to directly update state arrays/counters
                recordTransactions(totalTransactions, grossRevenue, highestSale, lowestSale, isFirstTransaction,
                                   countGrocery, subGrocery, countBeverages, subBeverages, countGeneral, subGeneral);
                break;

            case 2:
                // Variables passed by value since snapshot only reads data
                viewShiftSnapshot(totalTransactions, grossRevenue);
                break;

            case 3:
                if (totalTransactions == 0) {
                    cout << "\n[WARNING] No transactions recorded today. Cannot generate audit analytics.\n";
                } else {
                    printFinalAudit(totalTransactions, grossRevenue, highestSale, lowestSale,
                                    countGrocery, subGrocery, countBeverages, subBeverages, countGeneral, subGeneral);
                    menuChoice = 4; // Exit loop automatically after final audit submission
                }
                break;

            case 4:
                cout << "\nExiting Daily Sales Analyzer application. Goodbye!\n";
                break;
        }

    } while (menuChoice != 4);

    return 0;
}

// ============================================================================
// SYSTEM FUNCTION IMPLEMENTATIONS (VOID FUNCTIONS)
// ============================================================================

// Displays the static corporate branding header menu layout
void displayMainMenu() {
    cout << "\n=====================================================\n";
    cout << "      BELIZE TRADING CO. - DAILY SALES ANALYZER\n";
    cout << "=====================================================\n";
    cout << "Shift Location: San Ignacio Branch\n";
    cout << "Currency:       Belize Dollars (BZ$)\n\n";
    cout << "MAIN MENU:\n";
    cout << "1. Record a New Sale Transaction\n";
    cout << "2. View Shift Snapshot (Interim Totals)\n";
    cout << "3. Close Shift & Print Daily Audit\n";
    cout << "4. Exit Without Saving\n\n";
}

// Handles continuous transaction entries, nested validation loops, and metric assignments
void recordTransactions(int &totalTransactions, double &grossRevenue, 
                        double &highestSale, double &lowestSale, bool &isFirstTransaction,
                        int &countGrocery, double &subGrocery,
                        int &countBeverages, double &subBeverages,
                        int &countGeneral, double &subGeneral) {
    char enterMore = 'y';
    
    while (tolower(enterMore) == 'y') {
        totalTransactions++;
        double saleAmount = 0.0;
        int categoryChoice = 0;

        cout << "\n--- Record Sale #" << totalTransactions << " ---
";
        
        // Input Validation Loop: Sale Amount 
        while (true) {
            cout << "Enter sale amount ($BZ): ";
            if (cin >> saleAmount && saleAmount > 0.00) {
                break; 
            } else {
                cout << "[ERROR] Invalid entry! Sale amount must be greater than $BZ 0.00.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        // Input Validation Loop: Category Selection
        while (true) {
            cout << "Select Category:\n";
            cout << "  Grocery & Produce\n";
            cout << "  Beverages & Snacks\n";
            cout << "  General Merchandise\n";
            cout << "Enter category choice (1-3): ";
            
            if (cin >> categoryChoice && categoryChoice >= 1 && categoryChoice <= 3) {
                break; 
            } else {
                cout << "\n[ERROR] Invalid selection! Please choose a category option from 1 to 3.\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        // Sorting Subtotals & Counters
        if (categoryChoice == 1) {
            countGrocery++;
            subGrocery += saleAmount;
            cout << ">>> Sale of $BZ " << saleAmount << " recorded under Grocery & Produce.\n";
        } else if (categoryChoice == 2) {
            countBeverages++;
            subBeverages += saleAmount;
            cout << ">>> Sale of $BZ " << saleAmount << " recorded under Beverages & Snacks.\n";
        } else if (categoryChoice == 3) {
            countGeneral++;
            subGeneral += saleAmount;
            cout << ">>> Sale of $BZ " << saleAmount << " recorded under General Merchandise.\n";
        }

        // Real-Time Min/Max Evaluation Block
        if (isFirstTransaction) {
            highestSale = saleAmount;
            lowestSale = saleAmount;
            isFirstTransaction = false; 
        } else {
            if (saleAmount > highestSale) highestSale = saleAmount;
            if (saleAmount < lowestSale) lowestSale = saleAmount;
        }

        // Accumulate running total revenue
        grossRevenue += saleAmount;

        // Flow continuation check
        cout << "Do you want to enter another transaction? (y/n): ";
        cin >> enterMore;
    }
    cout << "Returning to Main Menu...\n";
}

// Displays quick look analytics on performance tracking without closing the registers
void viewShiftSnapshot(int totalTransactions, double grossRevenue) {
    cout << "\n--- INTERIM SHIFT SNAPSHOT ---\n";
    cout << "Transactions Logged: " << totalTransactions << "\n";
    cout << "Current Gross Sales: $BZ " << grossRevenue << "\n";
    if (totalTransactions > 0) {
        cout << "Current Average Sale: $BZ " << (grossRevenue / totalTransactions) << "\n";
    } else {
        cout << "Current Average Sale: $BZ 0.00\n";
    }
}

// Formats spreadsheet data matrices matching end-of-day compliance requirements
void printFinalAudit(int totalTransactions, double grossRevenue, 
                     double highestSale, double lowestSale,
                     int countGrocery, double subGrocery,
                     int countBeverages, double subBeverages,
                     int countGeneral, double subGeneral) {
                     
    double averageSale = grossRevenue / totalTransactions;
    
    cout << "\n=====================================================\n";
    cout << "            END-OF-DAY SALES AUDIT REPORT\n";
    cout << "=====================================================
";
    cout << left << setw(32) << "Total Transactions Processed:" << totalTransactions << "\n";
    cout << left << setw(32) << "Gross Revenue Collected:" << "$BZ " << grossRevenue << "\n";
    cout << left << setw(32) << "Average Transaction Size:" << "$BZ " << averageSale << "\n";
    cout << "-----------------------------------------------------\n";
    cout << left << setw(32) << "Peak Transaction (Highest):" << "$BZ " << highestSale << "\n";
    cout << left << setw(32) << "Base Transaction (Lowest):" << "$BZ " << lowestSale << "\n";
    
    cout << "=====================================================\n";
    cout << "                  CATEGORY BREAKDOWN\n";
    cout << "=====================================================\n";
    cout << left << setw(23) << "Category" 
         << right << setw(7) << "Count" 
         << right << setw(13) << "Subtotal" 
         << right << setw(10) << "Share" << "\n";
    cout << "-----------------------------------------------------\n";
    
    // Category Breakdown rows with inline mathematical percentage calculations
    cout << left << setw(23) << "Grocery & Produce" 
         << right << setw(7) << countGrocery 
         << "   $BZ " << right << setw(7) << subGrocery 
         << right << setw(9) << (subGrocery / grossRevenue * 100) << "%\n";
         
    cout << left << setw(23) << "Beverages & Snacks" 
         << right << setw(7) << countBeverages 
         << "   $BZ " << right << setw(7) << subBeverages 
         << right << setw(9) << (subBeverages / grossRevenue * 100) << "%\n";
         
    cout << left << setw(23) << "General Merchandise" 
         << right << setw(7) << countGeneral 
         << "   $BZ " << right << setw(7) << subGeneral 
         << right << setw(9) << (subGeneral / grossRevenue * 100) << "%\n";
         
    cout << "=====================================================\n";
    cout << "Shift reconciliation completed successfully. Have a safe evening!\n";
}