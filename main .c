#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- STRUCTURES ---------- */

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int room;
};

struct Doctor {
    int id;
    char name[50];
    char dept[50];
};

struct Assign {
    int patient_id;
    int doctor_id;
};

/* ---------- UTILITY ---------- */

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ---------- FUNCTION DECLARATIONS ---------- */

/* Views */
void mainMenu();
void patientMenu();
void doctorMenu();
void workerMenu();
void adminMenu();

/* Admin */
void addPatient();
void addDoctor();
void assignDoctor();
void generateBill();

/* Patient */
void patientViewDetails();
void patientViewDoctor();
void patientViewBill();

/* Doctor */
void doctorViewDetails();
void doctorViewPatients();

/* Worker */
void workerViewPatients();
void workerViewRooms();

/* ---------- MAIN ---------- */

int main() {
    int choice;

    while (1) {
        mainMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: patientMenu(); break;
        case 2: doctorMenu(); break;
        case 3: workerMenu(); break;
        case 4: adminMenu(); break;
        case 5:
            printf("Exiting system...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
}

/* ---------- MENUS ---------- */

void mainMenu() {
    printf("\n==============================");
    printf("\n HOSPITAL MANAGEMENT SYSTEM");
    printf("\n==============================");
    printf("\n1. Patient View");
    printf("\n2. Doctor View");
    printf("\n3. Worker View");
    printf("\n4. Admin View");
    printf("\n5. Exit");
    printf("\n==============================\n");
}

void patientMenu() {
    int ch;
    printf("\n--- PATIENT VIEW ---");
    printf("\n1. View My Details");
    printf("\n2. View Assigned Doctor");
    printf("\n3. View Bill");
    printf("\nEnter choice: ");
    scanf("%d", &ch);
    clearInput();

    if (ch == 1) patientViewDetails();
    else if (ch == 2) patientViewDoctor();
    else if (ch == 3) patientViewBill();
}

void doctorMenu() {
    int ch;
    printf("\n--- DOCTOR VIEW ---");
    printf("\n1. View My Details");
    printf("\n2. View My Patients");
    printf("\nEnter choice: ");
    scanf("%d", &ch);
    clearInput();

    if (ch == 1) doctorViewDetails();
    else if (ch == 2) doctorViewPatients();
}

void workerMenu() {
    int ch;
    printf("\n--- WORKER VIEW ---");
    printf("\n1. View All Patients");
    printf("\n2. View Room Allotment");
    printf("\nEnter choice: ");
    scanf("%d", &ch);
    clearInput();

    if (ch == 1) workerViewPatients();
    else if (ch == 2) workerViewRooms();
}

void adminMenu() {
    int ch;
    printf("\n--- ADMIN VIEW ---");
    printf("\n1. Add Patient");
    printf("\n2. Add Doctor");
    printf("\n3. Assign Doctor");
    printf("\n4. Generate Bill");
    printf("\nEnter choice: ");
    scanf("%d", &ch);
    clearInput();

    if (ch == 1) addPatient();
    else if (ch == 2) addDoctor();
    else if (ch == 3) assignDoctor();
    else if (ch == 4) generateBill();
}

/* ---------- ADMIN FUNCTIONS ---------- */

void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    struct Patient p;

    printf("Patient ID: ");
    scanf("%d", &p.id);
    clearInput();
    printf("Name: ");
    scanf(" %[^\n]", p.name);
    printf("Age: ");
    scanf("%d", &p.age);
    clearInput();
    printf("Disease: ");
    scanf(" %[^\n]", p.disease);
    printf("Room: ");
    scanf("%d", &p.room);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("Patient added successfully!\n");
}

void addDoctor() {
    FILE *fp = fopen("doctors.dat", "ab");
    struct Doctor d;

    printf("Doctor ID: ");
    scanf("%d", &d.id);
    clearInput();
    printf("Name: ");
    scanf(" %[^\n]", d.name);
    printf("Department: ");
    scanf(" %[^\n]", d.dept);

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
    printf("Doctor added!\n");
}

void assignDoctor() {
    FILE *fp = fopen("assign.dat", "ab");
    struct Assign a;

    printf("Patient ID: ");
    scanf("%d", &a.patient_id);
    printf("Doctor ID: ");
    scanf("%d", &a.doctor_id);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Doctor assigned!\n");
}

void generateBill() {
    int days;
    printf("Enter number of days admitted: ");
    scanf("%d", &days);
    printf("Total Bill: Rs.%d\n", days * 2000);
}

/* ---------- PATIENT VIEW ---------- */

void patientViewDetails() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    int id;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Name: %s | Disease: %s | Room: %d\n",
                   p.name, p.disease, p.room);
            break;
        }
    }
    fclose(fp);
}

void patientViewDoctor() {
    FILE *fp = fopen("assign.dat", "rb");
    struct Assign a;
    int id;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.patient_id == id) {
            printf("Assigned Doctor ID: %d\n", a.doctor_id);
            break;
        }
    }
    fclose(fp);
}

void patientViewBill() {
    int days;
    printf("Enter number of days admitted: ");
    scanf("%d", &days);
    printf("Total Bill = Rs.%d\n", days * 2000);
}

/* ---------- DOCTOR VIEW ---------- */

void doctorViewDetails() {
    FILE *fp = fopen("doctors.dat", "rb");
    struct Doctor d;
    int id;

    printf("Enter Doctor ID: ");
    scanf("%d", &id);

    while (fread(&d, sizeof(d), 1, fp)) {
        if (d.id == id) {
            printf("Name: %s | Dept: %s\n", d.name, d.dept);
            break;
        }
    }
    fclose(fp);
}

void doctorViewPatients() {
    FILE *fp = fopen("assign.dat", "rb");
    struct Assign a;
    int id;

    printf("Enter Doctor ID: ");
    scanf("%d", &id);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.doctor_id == id)
            printf("Patient ID: %d\n", a.patient_id);
    }
    fclose(fp);
}

/* ---------- WORKER VIEW ---------- */

void workerViewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("ID:%d | Name:%s | Room:%d\n",
               p.id, p.name, p.room);
    }
    fclose(fp);
}

void workerViewRooms() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("Room %d -> %s\n", p.room, p.name);
    }
    fclose(fp);
}
