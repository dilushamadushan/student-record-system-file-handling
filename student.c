#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct student {
    char f_name[20];
    char l_name[20];
    int roll_no;
    char vill[20];
    float per;
} stu;

void addStudent(); // Add student
void displayRecord(); // Display student records
void searchRecord(); // Search student record
void deleteRecord(); // Delete student record
void clearScreen(); // Clear the screen
void updateRecord();// Update student record

int main() {
    int ch;

    do {
        clearScreen();
        printf("============================================\n");
        printf("=    STUDENT DATABASE MANAGEMENT SYSTEM    =\n");
        printf("=               Main Menu                  =\n");
        printf("============================================\n\n");
        printf("\t1. Add Student\n");
        printf("\t2. Display Student Records\n");
        printf("\t3. Search Student\n");
        printf("\t4. Delete Student Record\n");
        printf("\t5. Update Student Record\n");
        printf("\t0. Exit\n\n");

        printf("[-] Enter Your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                addStudent();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                updateRecord();
                break;
            case 0:
                printf("[+] Exiting Program.\n");
                break;
            default:
                printf("[!] Invalid Choice. Please try again.\n");
                break;
        }
    } while (ch != 0);

    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

void addStudent() {
    char another;
    stu info;
    FILE *fp;

    do {
        clearScreen();
        printf("\t\t\t===           ADD NEW STUDENT RECORD            ===\n\n\n");
        fp = fopen("student.dat", "ab");
        
        if (fp == NULL) {
            printf("[!] Can't Open File.\n");
            return;
        }

        printf("[-] Enter Your First Name: ");
        scanf("%s", info.f_name);
        printf("[-] Enter Your Last Name: ");
        scanf("%s", info.l_name);
        printf("[-] Enter Enroll ID No: ");
        scanf("%d", &info.roll_no);
        printf("[-] Enter Your Address: ");
        scanf("%s", info.vill);
        printf("[-] Enter Percentage: ");
        scanf("%f", &info.per);  

        fwrite(&info, sizeof(stu), 1, fp);
        fclose(fp);

        printf("[+] Record Stored Successfully.\n");
        printf("[+] Do You Want to Add Another Record (Y / N)? ");
        scanf(" %c", &another);
    } while (another == 'Y' || another == 'y');
}

void displayRecord() {
    FILE *fp;
    stu info;
    int recordCount = 0;

    fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("[!] Can't Open File.\n");
        return;
    }

    clearScreen();
    printf("\n\n\t\t\t===              STUDENT RECORD                 ===\n\n\n");
    printf("\t\t   Records >>\n\n");
    printf("\t\t\t\t_______________________________________\n\n");

    while (fread(&info, sizeof(stu), 1, fp)) {
        printf("\t\t\t\tStudent Name: %s %s\n", info.f_name, info.l_name);
        printf("\t\t\t\tRoll No: %d\n", info.roll_no);
        printf("\t\t\t\tAddress: %s\n", info.vill);
        printf("\t\t\t\tPercentage: %.2f\n", info.per);
        printf("\t\t\t\t_______________________________________\n\n");
        recordCount++;
    }

    fclose(fp);

    if (recordCount == 0) {
        printf("\n\n[!] No Records Found.\n\n");
    }

    printf("\n\n[-] Press Any Key to Return to Menu.\n\n");
    getch();
}

void searchRecord() {
    FILE *fp;
    stu info;
    int roll_no, found = 0;

    clearScreen();
    printf("\t\t\t===           SEARCH STUDENT RECORD            ===\n\n\n");
    fp = fopen("student.dat", "rb");

    if (fp == NULL) {
        printf("[!] Can't Open File.\n");
        return;
    }

    printf("[-] Enter Roll Number: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(stu), 1, fp)) {
        if (info.roll_no == roll_no) {
            printf("\n\t\t\t\tStudent Name: %s %s\n", info.f_name, info.l_name);
            printf("\t\t\t\tRoll No: %d\n", info.roll_no);
            printf("\t\t\t\tAddress: %s\n", info.vill);
            printf("\t\t\t\tPercentage: %.2f\n", info.per);
            printf("\t\t\t\t_______________________________________\n\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("[!] Record Not Found.\n");
    }

    printf("\n\n[-] Press Any Key to Return to Menu.\n\n");
    getch();
}

void deleteRecord() {
    FILE *fp, *fp1;
    stu info;
    int roll_no, found = 0;

    clearScreen();
    printf("\t\t\t===           DELETE STUDENT RECORD            ===\n\n\n");
    fp = fopen("student.dat", "rb");
    fp1 = fopen("temp.dat", "wb");

    if (fp == NULL || fp1 == NULL) {
        printf("[!] Can't Open File.\n");
        if (fp) fclose(fp);
        if (fp1) fclose(fp1);
        return;
    }

    printf("[-] Enter Roll Number: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(stu), 1, fp)) {
        if (info.roll_no == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(stu), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        printf("[+] Record Deleted Successfully.\n");
    } else {
        printf("[!] Record Not Found.\n");
        remove("temp.dat");
    }

    printf("\n\n[-] Press Any Key to Return to Menu.\n\n");
    getch();
}

void updateRecord() {
    FILE *fp, *fp1;
    stu info;
    int roll_no, found = 0;

    clearScreen();
    printf("\t\t\t===           UPDATE STUDENT RECORD            ===\n\n\n");
    fp = fopen("student.dat", "rb");
    fp1 = fopen("temp.dat", "wb");

    if (fp == NULL || fp1 == NULL) {
        printf("[!] Can't Open File.\n");
        if (fp) fclose(fp);
        if (fp1) fclose(fp1);
        return;
    }

    printf("[-] Enter Roll Number: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(stu), 1, fp)) {
        if (info.roll_no == roll_no) {
            found = 1;
            printf("[-] Enter New First Name: ");
            scanf("%s", info.f_name);
            printf("[-] Enter New Last Name: ");
            scanf("%s", info.l_name);
            printf("[-] Enter New Address: ");
            scanf("%s", info.vill);
            printf("[-] Enter New Percentage: ");
            scanf("%f", &info.per);
        }
        fwrite(&info, sizeof(stu), 1, fp1);
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        printf("[+] Record Updated Successfully.\n");
    } else {
        printf("[!] Record Not Found.\n");
        remove("temp.dat");
    }

    printf("\n\n[-] Press Any Key to Return to Menu.\n\n");
    getch();
}
