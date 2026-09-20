#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_WARDS 4
#define MAX_BEDS 20

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
void doctorChannelling(void);
void wardAndBedAllocation(void);

void showBedMatrix(void);
void bedAllocation(void);

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
/* =========================================================
   CASE 3
   BED MATRIX
   ========================================================= */

void showBedMatrix(void)
{
    printf("\nBed Occupancy Matrix\n");
    printf("0 = Available   1 = Occupied   X = Not Available\n\n");

    printf("%-30s", "Ward");

    for (int j = 0; j < MAX_BEDS; j++)
    {
        printf("%-4d", j + 1);
    }

    printf("\n");

    for (int i = 0; i < MAX_WARDS; i++)
    {
        printf("%-30s", ward[i]);

        for (int j = 0; j < MAX_BEDS; j++)
        {
            if (j < totalBedCapacity[i])
            {
                printf("%-4d", bedOccupancy[i][j]);
            }
            else
            {
                printf("%-4s", "X");
            }
        }

        printf("\n");
    }
}


/* =========================================================
   CASE 3
   BED ALLOCATION
   ========================================================= */

void bedAllocation(void)
{
    int selectedWard;
    int option;


    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n",
               i + 1,
               ward[i]);
    }

    printf("Ward ID: ");
    scanf("%d", &selectedWard);


    if (selectedWard < 1 ||
        selectedWard > 4)
    {
        printf("Invalid choice!\n");
        return;
    }


    do
    {
        printf("\nSelected Ward: %s\n",
               ward[selectedWard - 1]);

        printf("1. To be allocated\n");
        printf("2. Already allocated\n");
        printf("3. Cancel bed allocation\n");
        printf("4. Back\n");

        printf("Enter your choice: ");
        scanf("%d", &option);


        /* ================= TO BE ALLOCATED ================= */

        if (option == 1)
        {
            int count = 0;
            int selectedPatient;


            for (int i = 0;
                 i < patientCount;
                 i++)
            {
                if (admissionChoice[i] == 1 &&
                    wardId[i] == selectedWard &&
                    bedNumber[i] == 0)
                {
                    count++;

                    printf("%d. %s\n",
                           count,
                           patientName[i]);
                }
            }


            if (count == 0)
            {
                printf("No patients to be allocated.\n");
                continue;
            }


            printf("Select patient: ");
            scanf("%d", &selectedPatient);


            if (selectedPatient < 1 ||
                selectedPatient > count)
            {
                printf("Invalid patient choice!\n");
                continue;
            }


            int patientIndex = -1;
            int position = 0;


            for (int i = 0;
                 i < patientCount;
                 i++)
            {
                if (admissionChoice[i] == 1 &&
                    wardId[i] == selectedWard &&
                    bedNumber[i] == 0)
                {
                    position++;

                    if (position == selectedPatient)
                    {
                        patientIndex = i;
                        break;
                    }
                }
            }


            printf("\nSelected Patient: %s\n",
                   patientName[patientIndex]);


            printf("\nAvailable Beds: ");

            int available = 0;


            for (int i = 0;
                 i < totalBedCapacity[selectedWard - 1];
                 i++)
            {
                if (bedOccupancy[selectedWard - 1][i] == 0)
                {
                    printf("%d ", i + 1);
                    available++;
                }
            }

            printf("\n");


            if (available == 0)
            {
                printf("No beds available in this ward.\n");
                continue;
            }


            int selectedBed;

            printf("Enter bed number: ");
            scanf("%d", &selectedBed);


            if (selectedBed < 1 ||
                selectedBed >
                totalBedCapacity[selectedWard - 1])
            {
                printf("Invalid bed number!\n");
                continue;
            }


            if (bedOccupancy[selectedWard - 1]
                             [selectedBed - 1] == 1)
            {
                printf("This bed is already occupied!\n");
                continue;
            }


            bedOccupancy[selectedWard - 1]
                         [selectedBed - 1] = 1;

            bedNumber[patientIndex] = selectedBed;


            printf("Allocation date (DD/MM/YYYY): ");
            scanf("%19s",
                  allocationDate[patientIndex]);


            printf("Bed allocated successfully!\n");
        }


        /* ================= ALREADY ALLOCATED ================= */

        else if (option == 2)
        {
            int count = 0;


            for (int i = 0;
                 i < patientCount;
                 i++)
            {
                if (admissionChoice[i] == 1 &&
                    wardId[i] == selectedWard &&
                    bedNumber[i] != 0)
                {
                    count++;

                    printf("%d. %s - Bed %d - Allocated: %s\n",
                           count,
                           patientName[i],
                           bedNumber[i],
                           allocationDate[i]);
                }
            }


            if (count == 0)
            {
                printf("No patients are currently "
                       "allocated to a bed.\n");
            }
        }


        /* ================= CANCEL BED ================= */

        else if (option == 3)
        {
            int count = 0;
            int selectedPatient;


            for (int i = 0;
                 i < patientCount;
                 i++)
            {
                if (admissionChoice[i] == 1 &&
                    wardId[i] == selectedWard &&
                    bedNumber[i] != 0)
                {
                    count++;

                    printf("%d. %s - Bed %d\n",
                           count,
                           patientName[i],
                           bedNumber[i]);
                }
            }


            if (count == 0)
            {
                printf("No patients are currently allocated.\n");
                continue;
            }


            printf("Select patient: ");
            scanf("%d", &selectedPatient);


            if (selectedPatient < 1 ||
                selectedPatient > count)
            {
                printf("Invalid patient choice!\n");
                continue;
            }


            int patientIndex = -1;
            int position = 0;


            for (int i = 0;
                 i < patientCount;
                 i++)
            {
                if (admissionChoice[i] == 1 &&
                    wardId[i] == selectedWard &&
                    bedNumber[i] != 0)
                {
                    position++;

                    if (position == selectedPatient)
                    {
                        patientIndex = i;
                        break;
                    }
                }
            }


            printf("Patient: %s\n",
                   patientName[patientIndex]);

            printf("Bed Number: %d\n",
                   bedNumber[patientIndex]);

            printf("Allocation Date: %s\n",
                   allocationDate[patientIndex]);


            printf("Cancellation date (DD/MM/YYYY): ");

            scanf("%19s",
                  cancellationDate[patientIndex]);


            bedOccupancy[selectedWard - 1]
                         [bedNumber[patientIndex] - 1] = 0;

            bedNumber[patientIndex] = 0;


            printf("Bed allocation cancelled successfully!\n");
        }


        else if (option != 4)
        {
            printf("Invalid choice! Please try again.\n");
        }

    } while (option != 4);
}


/* =========================================================
   CASE 3 MAIN
   ========================================================= */

void wardAndBedAllocation(void)
{
    int option;

    do
    {
        printf("\n--- Hospital Wards and Bed Allocation ---\n");

        printf("1. Bed matrix\n");
        printf("2. Bed allocation\n");
        printf("3. Back\n");

        printf("Enter your choice: ");
        scanf("%d", &option);


        if (option == 1)
        {
            showBedMatrix();
        }

        else if (option == 2)
        {
            bedAllocation();
        }

        else if (option != 3)
        {
            printf("Invalid choice!\n");
        }

    } while (option != 3);
}

//Billing
//Reports & Data Management
