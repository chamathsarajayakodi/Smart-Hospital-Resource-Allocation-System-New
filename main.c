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

int bedNumber[MAX_PATIENTS] = {0};

char allocationDate[MAX_PATIENTS][20] = {0};
char cancellationDate[MAX_PATIENTS][20] = {0};

int bedOccupancy[MAX_WARDS][MAX_BEDS] = {0};


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

void reports(void);

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
//Reports & Data Management
/* =========================================================
   CASE 5
   REPORTS
   ========================================================= */

void reports(void)
{
    int option;


    do
    {
        printf("\n--- Reports and Data Management ---\n");

        printf("1. Patient Summary by Emergency Level\n");
        printf("2. Revenue & Discount Report\n");
        printf("3. Ward Bed Occupancy Report\n");
        printf("4. Highest-Paying Patient\n");
        printf("5. Back\n");


        printf("Enter your choice: ");
        scanf("%d", &option);


        switch (option)
        {
            /* ================= REPORT 1 ================= */

            case 1:
            {
                int normal = 0;
                int urgent = 0;
                int critical = 0;


                for (int i = 0;
                     i < patientCount;
                     i++)
                {
                    if (emergencyLevel[i] == 1)
                    {
                        normal++;
                    }

                    else if (emergencyLevel[i] == 2)
                    {
                        urgent++;
                    }

                    else if (emergencyLevel[i] == 3)
                    {
                        critical++;
                    }
                }


                printf("\nPatient Summary by Emergency Level\n");

                printf("Normal   : %d patients\n",
                       normal);

                printf("Urgent   : %d patients\n",
                       urgent);

                printf("Critical : %d patients\n",
                       critical);

                break;
            }


            /* ================= REPORT 2 ================= */

            case 2:
            {
                float revenue = 0.0f;
                float discountTotal = 0.0f;


                for (int i = 0;
                     i < patientCount;
                     i++)
                {
                    float base =
                        consultationFee[
                            specialtyId[i] - 1
                        ];


                    float surcharge =
                        calculateEmergencySurcharge(
                            base,
                            emergencyLevel[i]
                        );


                    float wardCost = 0.0f;


                    if (admissionChoice[i] == 1)
                    {
                        wardCost =
                            calculateWardCost(
                                daysAdmitted[i],
                                dailyBedRate[
                                    wardId[i] - 1
                                ]
                            );
                    }


                    float gross =
                        calculateGrossTotal(
                            base,
                            surcharge,
                            wardCost
                        );


                    float discount =
                        calculateAgeSubsidy(
                            gross,
                            age[i]
                        );


                    revenue +=
                        calculateFinalPayable(
                            gross,
                            discount
                        );


                    discountTotal += discount;
                }


                printf("\nRevenue & Discount Report\n");

                printf("Total Revenue   : LKR %.2f\n",
                       revenue);

                printf("Total Discounts : LKR %.2f\n",
                       discountTotal);

                break;
            }


            /* ================= REPORT 3 ================= */

            case 3:
            {
                printf("\nWard Bed Occupancy Report\n\n");


                for (int i = 0;
                     i < 4;
                     i++)
                {
                    int occupied = 0;


                    for (int j = 0;
                         j < totalBedCapacity[i];
                         j++)
                    {
                        if (bedOccupancy[i][j] == 1)
                        {
                            occupied++;
                        }
                    }


                    printf("%s\n",
                           ward[i]);

                    printf("Total Beds     : %d\n",
                           totalBedCapacity[i]);

                    printf("Occupied Beds  : %d\n",
                           occupied);

                    printf("Available Beds : %d\n\n",
                           totalBedCapacity[i] -
                           occupied);
                }

                break;
            }


            /* ================= REPORT 4 ================= */

            case 4:
            {
                if (patientCount == 0)
                {
                    printf("No patients available.\n");
                    break;
                }


                int highest = 0;


                float highestPayable =
                    patientFinalPayable(0);


                for (int i = 1;
                     i < patientCount;
                     i++)
                {
                    float payable =
                        patientFinalPayable(i);


                    if (payable > highestPayable)
                    {
                        highestPayable =
                            payable;

                        highest = i;
                    }
                }


                printf("\nHighest-Paying Patient\n");

                printf("Patient Name  : %s\n",
                       patientName[highest]);

                printf("Patient ID    : PAT-%04d\n",
                       1001 + highest);

                printf("Final Payable : LKR %.2f\n",
                       highestPayable);

                break;
            }


            case 5:

                break;


            default:

                printf("Invalid choice!\n");
        }

    } while (option != 5);
}
