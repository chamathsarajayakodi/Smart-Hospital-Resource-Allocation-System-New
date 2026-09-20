# Smart-Hospital-Resource-Allocation-System-New
The individual assignment submission for CSC 1012: Introduction to Computer Programming (University of Sri Jayewardenepura).

## 1. Project Overview

The Smart Hospital Resource Allocation System is a menu-driven C application developed to manage essential hospital operations.

The system provides functionality for:

- New Patient Registration
- Doctor Channelling
- Hospital Ward and Bed Allocation
- Patient Billing
- Reports and Data Management
- File Handling for persistent data storage

The system is designed to organize patient information, manage hospital resources, calculate billing amounts, and generate useful reports.

---

## 2. Objectives

The main objectives of this project are:

- To manage patient registration efficiently.
- To provide doctor channelling and queue information.
- To manage hospital wards and bed allocation.
- To calculate patient billing accurately.
- To generate reports from stored patient and hospital data.
- To demonstrate modular programming using C.
- To use file handling for persistent data storage.

---

## 3. Main Features

### 3.1 New Patient Registration

The system records:

- Patient name
- Age
- Emergency level
- Medical specialty
- Ward admission requirement
- Ward selection
- Planned admission days

Each registered patient receives a unique patient ID.

### 3.2 Doctor Channelling

The system provides:

- Current queue information
- Emergency priority information
- Consultation time
- Estimated waiting time
- Daily consultation capacity

Supported specialties include:

- General Practice (OPD)
- Paediatrics
- Cardiology
- Neurology

### 3.3 Hospital Wards & Bed Allocation

The system manages:

- Ward selection
- Bed availability
- Bed allocation
- Already allocated beds
- Bed cancellation
- Allocation dates
- Cancellation dates

The bed matrix uses:

- `0` = Available
- `1` = Occupied
- `X` = Not available

### 3.4 Billing

The billing system calculates:

- Base consultation fee
- Emergency surcharge
- Ward stay cost
- Age-based subsidy
- Final payable amount

### 3.5 Reports & Data Management

The system provides reports for:

- Patient summary by emergency level
- Revenue and discount information
- Ward bed occupancy
- Highest-paying patient

### 3.6 File Handling

The system uses text files to maintain data between program runs.

#### `beds_status.txt`

Stores the current bed occupancy status so that occupied and available beds can be restored when the program starts again.

#### `patient_records.txt`

Stores permanent patient billing records by appending new billing information to the existing file.

---

## 4. Data Structures

The system mainly uses fixed-size arrays.

```c
#define MAX_PATIENTS 100
#define MAX_WARDS 4
#define MAX_BEDS 20
