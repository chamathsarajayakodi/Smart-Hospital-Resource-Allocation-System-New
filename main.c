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

void registerPatient(void)
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("Patient registration is full!\n");
        return;
    }

    printf("\n--- New Patient Registration ---\n");

    printf("Patient Name: ");
    scanf(" %99[^\n]", patientName[patientCount]);

    printf("Patient Age: ");
    scanf("%d", &age[patientCount]);

    if (age[patientCount] <= 0 || age[patientCount] > 120)
    {
        printf("Invalid age! Registration cancelled.\n");
        return;
    }

    // Emergency level

    printf("\nEmergency Choice\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s\n", i + 1, emergencyChoice[i]);
    }

    printf("Emergency level: ");
    scanf("%d", &emergencyLevel[patientCount]);

    if (emergencyLevel[patientCount] < 1 ||
        emergencyLevel[patientCount] > 3)
    {
        printf("Invalid choice! Registration cancelled.\n");
        return;
    }


    // Specialty

    printf("\nSpecialty Selection\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, specialty[i]);
    }

    printf("Specialty ID: ");
    scanf("%d", &specialtyId[patientCount]);

    if (specialtyId[patientCount] < 1 ||
        specialtyId[patientCount] > 4)
    {
        printf("Invalid choice! Registration cancelled.\n");
        return;
    }


    // Ward admission

    printf("\nIs Admitted to Ward?\n");
    printf("1 = Yes\n");
    printf("0 = No\n");

    printf("Ward admission choice: ");
    scanf("%d", &admissionChoice[patientCount]);


    if (admissionChoice[patientCount] == 1)
    {
        printf("\nWard Selection\n");

        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s\n", i + 1, ward[i]);
        }

        printf("Ward ID: ");
        scanf("%d", &wardId[patientCount]);

        if (wardId[patientCount] < 1 ||
            wardId[patientCount] > 4)
        {
            printf("Invalid choice! Registration cancelled.\n");
            return;
        }

        printf("Days Admitted: ");
        scanf("%d", &daysAdmitted[patientCount]);

        if (daysAdmitted[patientCount] <= 0)
        {
            printf("Invalid number of days! Registration cancelled.\n");
            return;
        }
    }

    else if (admissionChoice[patientCount] == 0)
    {
        wardId[patientCount] = 0;
        daysAdmitted[patientCount] = 0;
    }

    else
    {
        printf("Invalid choice! Registration cancelled.\n");
        return;
    }


    // Initial bed information

    bedNumber[patientCount] = 0;

    allocationDate[patientCount][0] = '\0';
    cancellationDate[patientCount][0] = '\0';


    printf("\nPatient registered successfully!\n");

    printf("Patient ID: PAT-%04d\n",
           1001 + patientCount);

    patientCount++;
}

//Doctor Channeling
//Hospital Wards & Bed Allocation
//Billing
//Reports & Data Management
