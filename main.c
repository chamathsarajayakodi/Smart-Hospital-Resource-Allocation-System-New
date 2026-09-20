#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

//Shared patient data
int emergencyLevel[MAX_PATIENTS];
int specialtyId[MAX_PATIENTS];
int wardId[MAX_PATIENTS];

char patientName[MAX_PATIENTS][100];

int age[MAX_PATIENTS];
int admissionChoice[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];

int currentQueue[4] = {0, 0, 0, 0};
int estimatedWaitingTime = 0;

int patientCount = 0;


//Hospital data

const char emergencyChoice[3][10] =
{
    "Normal",
    "Urgent",
    "Critical"
};

const char specialty[4][30] =
{
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const float consultationFee[4] =
{
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[4] =
{
    15,
    20,
    30,
    30
};

const int dailyCapacity[4] =
{
    30,
    20,
    12,
    10
};

const char ward[4][30] =
{
    "General Ward",
    "Pediatric Ward",
    "Surgical Ward",
    "ICU (Intensive Care Unit)"
};

const float dailyBedRate[4] =
{
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int totalBedCapacity[4] =
{
    20,
    10,
    10,
    5
};

//Function declarations
void registerPatient(void);
void billing(void);

void generateBill(int i);

float calculateEmergencySurcharge(float baseFee, int level);
float calculateWardCost(int days, float dailyRate);
float calculateGrossTotal(float baseFee, float surcharge, float wardCost);
float calculateAgeSubsidy(float grossTotal, int patientAge);
float calculateFinalPayable(float grossTotal, float discount);

float patientFinalPayable(int i);

//Main program
int main(void)
{
    int id;
    int choice;
    int loginAgain;

    char userName[50];
    char date[20];
    char time[20];


    do
    {
        printf("\n");
        printf("========================================\n");
        printf("       SMART HOSPITAL SYSTEM\n");
        printf("========================================\n");


        /* ================= LOGIN ================= */

        printf("User login\n");

        printf("User name: ");
        scanf(" %49[^\n]", userName);

        printf("Employee ID: ");
        scanf("%d", &id);

        printf("Date (DD/MM/YYYY): ");
        scanf("%19s", date);

        printf("Time (HH:MM): ");
        scanf("%19s", time);


        /* ================= MAIN MENU ================= */

        do
        {
            printf("\n");
            printf("=============== MAIN MENU ===============\n");

            printf("1. New Patient Registration\n");
            printf("2. Doctor Channeling\n");
            printf("3. Hospital Wards & Bed Allocation\n");
            printf("4. Billing\n");
            printf("5. Reports & Data Management\n");
            printf("6. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);


            switch (choice)
            {
                case 1:

                    registerPatient();

                    break;


                case 2:

                    doctorChannelling();

                    break;


                case 3:

                    wardAndBedAllocation();

                    break;


                case 4:

                    billing();

                    break;


                case 5:

                    reports();

                    break;


                case 6:

                    printf("\nExiting main menu...\n");

                    break;


                default:

                    printf("\nInvalid choice! "
                           "Please try again.\n");
            }

        } while (choice != 6);


        /* ================= LOGIN AGAIN ================= */

        do
        {
            printf("\nDo you want to login again?\n");

            printf("1. Yes\n");
            printf("2. No\n");

            printf("Enter your choice: ");
            scanf("%d", &loginAgain);


            if (loginAgain != 1 &&
                loginAgain != 2)
            {
                printf("Invalid choice! "
                       "Please enter 1 or 2.\n");
            }

        } while (loginAgain != 1 &&
                 loginAgain != 2);


    } while (loginAgain == 1);


    printf("\nThank you for using the "
           "Smart Hospital System!\n");


    return 0;
}

//New Patient Registration
//Doctor Channeling
//Hospital Wards & Bed Allocation
//Billing
/* =========================================================
   CASE 4
   BILLING FUNCTIONS
   ========================================================= */

float calculateEmergencySurcharge(float baseFee,
                                  int level)
{
    if (level == 2)
    {
        return baseFee * 0.20f;
    }

    if (level == 3)
    {
        return baseFee * 0.50f;
    }

    return 0.0f;
}


float calculateWardCost(int days,
                        float dailyRate)
{
    return days * dailyRate;
}


float calculateGrossTotal(float baseFee,
                          float surcharge,
                          float wardCost)
{
    return baseFee +
           surcharge +
           wardCost;
}


float calculateAgeSubsidy(float grossTotal,
                          int patientAge)
{
    if (patientAge < 5 ||
        patientAge > 65)
    {
        return grossTotal * 0.15f;
    }

    return 0.0f;
}


float calculateFinalPayable(float grossTotal,
                            float discount)
{
    return grossTotal - discount;
}


/* =========================================================
   CALCULATE ONE PATIENT'S FINAL BILL
   ========================================================= */

float patientFinalPayable(int i)
{
    float baseFee =
        consultationFee[specialtyId[i] - 1];


    float surcharge =
        calculateEmergencySurcharge(
            baseFee,
            emergencyLevel[i]
        );


    float wardCost = 0.0f;


    if (admissionChoice[i] == 1)
    {
        wardCost =
            calculateWardCost(
                daysAdmitted[i],
                dailyBedRate[wardId[i] - 1]
            );
    }


    float gross =
        calculateGrossTotal(
            baseFee,
            surcharge,
            wardCost
        );


    float discount =
        calculateAgeSubsidy(
            gross,
            age[i]
        );


    return calculateFinalPayable(
        gross,
        discount
    );
}


/* =========================================================
   GENERATE BILL
   ========================================================= */

void generateBill(int i)
{
    float baseFee =
        consultationFee[specialtyId[i] - 1];


    float surcharge =
        calculateEmergencySurcharge(
            baseFee,
            emergencyLevel[i]
        );


    float wardCost = 0.0f;


    if (admissionChoice[i] == 1)
    {
        wardCost =
            calculateWardCost(
                daysAdmitted[i],
                dailyBedRate[wardId[i] - 1]
            );
    }


    float gross =
        calculateGrossTotal(
            baseFee,
            surcharge,
            wardCost
        );


    float discount =
        calculateAgeSubsidy(
            gross,
            age[i]
        );


    float finalPayable =
        calculateFinalPayable(
            gross,
            discount
        );


    printf("\n");
    printf("========================================\n");
    printf("       SMART HOSPITAL ADMISSION & BILL\n");
    printf("========================================\n");


    printf("Patient ID            : PAT-%04d\n",
           1001 + i);

    printf("Patient Name          : %s\n",
           patientName[i]);

    printf("Age                   : %d Years\n",
           age[i]);

    printf("Specialty             : %s\n",
           specialty[specialtyId[i] - 1]);


    if (admissionChoice[i] == 1)
    {
        printf("Assigned Ward         : %s",
               ward[wardId[i] - 1]);

        if (bedNumber[i] > 0)
        {
            printf(" (Bed #%02d)",
                   bedNumber[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Assigned Ward         : Outpatient (OPD)\n");
    }


    printf("Urgency Level         : Level %d (%s)\n",
           emergencyLevel[i],
           emergencyChoice[
               emergencyLevel[i] - 1
           ]);


    printf("\n");

    printf("Base Consultation Fee : LKR %10.2f\n",
           baseFee);

    printf("Emergency Surcharge   : LKR %10.2f\n",
           surcharge);

    printf("Ward Stay Cost        : LKR %10.2f\n",
           wardCost);

    printf("Gross Total Bill      : LKR %10.2f\n",
           gross);

    printf("Age Subsidy Discount  : LKR -%9.2f\n",
           discount);

    printf("\n");

    printf("Final Payable Amount  : LKR %10.2f\n",
           finalPayable);

    printf("Estimated Waiting Time: %d mins\n",
           estimatedWaitingTime);

    printf("========================================\n");
}


/* =========================================================
   CASE 4 MAIN
   ========================================================= */

void billing(void)
{
    if (patientCount == 0)
    {
        printf("\nNo registered patients available.\n");
        return;
    }


    int option;


    do
    {
        printf("\n--- Billing ---\n");


        for (int i = 0;
             i < patientCount;
             i++)
        {
            printf("%d. %s\n",
                   i + 1,
                   patientName[i]);
        }


        printf("0. Back\n");


        printf("Select patient: ");
        scanf("%d", &option);


        if (option >= 1 &&
            option <= patientCount)
        {
            generateBill(option - 1);


            printf("\nEnter 0 to return to Billing "
                   "menu or select another patient: ");

            scanf("%d", &option);


            if (option == 0)
            {
                break;
            }


            if (option < 1 ||
                option > patientCount)
            {
                printf("Invalid patient selection.\n");
                option = -1;
            }
        }

        else if (option != 0)
        {
            printf("Invalid patient selection!\n");
        }

    } while (option != 0);
}
//Reports & Data Management
