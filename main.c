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
void doctorChannelling(void);

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
void doctorChannelling(void)
{
    int selectedSpecialty;
    int option;

    printf("\n--- Doctor Channeling ---\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n",
               i + 1,
               specialty[i]);
    }

    printf("Specialty ID: ");
    scanf("%d", &selectedSpecialty);

    if (selectedSpecialty < 1 ||
        selectedSpecialty > 4)
    {
        printf("Invalid specialty choice!\n");
        return;
    }


    do
    {
        printf("\n1. Current queue\n");
        printf("2. Consultation time\n");
        printf("3. Estimated waiting time\n");
        printf("4. Daily capacity\n");
        printf("5. Back\n");

        printf("Enter your choice: ");
        scanf("%d", &option);


        switch (option)
        {
            case 1:
            {
                int count = 0;

                printf("\nCurrent queue:\n");

                /*
                   Critical first
                   Urgent second
                   Normal last
                */

                for (int level = 3; level >= 1; level--)
                {
                    for (int i = 0;
                         i < patientCount;
                         i++)
                    {
                        if (specialtyId[i] == selectedSpecialty &&
                            emergencyLevel[i] == level)
                        {
                            count++;

                            printf("%d. %s - %s\n",
                                   count,
                                   patientName[i],
                                   emergencyChoice[level - 1]);
                        }
                    }
                }

                currentQueue[selectedSpecialty - 1] = count;

                printf("Total patients in queue: %d\n",
                       count);

                break;
            }


            case 2:

                printf("Consultation time: %d minutes\n",
                       consultationTime[selectedSpecialty - 1]);

                break;


            case 3:
            {
                int count = 0;

                for (int i = 0;
                     i < patientCount;
                     i++)
                {
                    if (specialtyId[i] == selectedSpecialty)
                    {
                        count++;
                    }
                }

                estimatedWaitingTime =
                    count *
                    consultationTime[selectedSpecialty - 1];

                printf("Estimated waiting time: %d minutes\n",
                       estimatedWaitingTime);

                break;
            }


            case 4:

                printf("Daily patient capacity: %d patients\n",
                       dailyCapacity[selectedSpecialty - 1]);

                break;


            case 5:

                break;


            default:

                printf("Invalid choice! Please try again.\n");
        }

    } while (option != 5);
}
//Hospital Wards & Bed Allocation
//Billing
//Reports & Data Management
