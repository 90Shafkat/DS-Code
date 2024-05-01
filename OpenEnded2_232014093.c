#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo {
    char studentName[50];
    int studentID;
    char studentDept[50];
    int studentAge;
    char studentGender;
    float studentCGPA;
    char studentMobile[15];
};

void addNewStudent(struct StudentInfo *info, int *numStudents);
void findStudent(struct StudentInfo *info, int numStudents);
void updateStudentInfo(struct StudentInfo *info, int numStudents);
void displayAll(struct StudentInfo *info, int numStudents);

int main() {
    struct StudentInfo students[100]; 
    int numStudents = 0;
    int choice;

    do {
        printf("\nStudent Management System\n");
        printf("1. Add new student information\n");
        printf("2. Find student by ID or mobile number\n");
        printf("3. Update student information\n");
        printf("4. Display all students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addNewStudent(students, &numStudents);
                break;
            case 2:
                findStudent(students, numStudents);
                break;
            case 3:
                updateStudentInfo(students, numStudents);
                break;
            case 4:
                displayAll(students, numStudents);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);

    return 0;
}

void addNewStudent(struct StudentInfo *info, int *numStudents) {
    if (*numStudents >= 100) {
        printf("Maximum number of students reached. Cannot add more.\n");
        return;
    }

    struct StudentInfo newInfo;
    printf("Enter student name: ");
    scanf("%s", newInfo.studentName);
    printf("Enter student ID: ");
    scanf("%d", &newInfo.studentID);
    printf("Enter student department: ");
    scanf("%s", newInfo.studentDept);
    printf("Enter student age: ");
    scanf("%d", &newInfo.studentAge);
    printf("Enter student gender (M/F): ");
    scanf(" %c", &newInfo.studentGender);
    printf("Enter student CGPA: ");
    scanf("%f", &newInfo.studentCGPA);
    printf("Enter student mobile number: ");
    scanf("%s", newInfo.studentMobile);

    info[*numStudents] = newInfo;
    (*numStudents)++;
    printf("Student information added successfully.\n");
}

void findStudent(struct StudentInfo *info, int numStudents) {
    int choice;
    printf("Find student by:\n");
    printf("1. ID\n");
    printf("2. Mobile Number\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int searchID;
        printf("Enter student ID to find: ");
        scanf("%d", &searchID);
        for (int i = 0; i < numStudents; i++) {
            if (info[i].studentID == searchID) {
                printf("Student found:\n");
                printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile Number: %s\n", 
                       info[i].studentName, info[i].studentID, info[i].studentDept, info[i].studentAge, info[i].studentGender,
                       info[i].studentCGPA, info[i].studentMobile);
                return;
            }
        }
        printf("Student with ID %d not found.\n", searchID);
    } else if (choice == 2) {
        char searchMobile[15];
        printf("Enter student mobile number to find: ");
        scanf("%s", searchMobile);
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(info[i].studentMobile, searchMobile) == 0) {
                printf("Student found:\n");
                printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile Number: %s\n", 
                       info[i].studentName, info[i].studentID, info[i].studentDept, info[i].studentAge, info[i].studentGender,
                       info[i].studentCGPA, info[i].studentMobile);
                return;
            }
        }
        printf("Student with mobile number %s not found.\n", searchMobile);
    } else {
        printf("Invalid choice.\n");
    }
}

void updateStudentInfo(struct StudentInfo *info, int numStudents) {
    int searchID;
    printf("Enter student ID to update: ");
    scanf("%d", &searchID);
    for (int i = 0; i < numStudents; i++) {
        if (info[i].studentID == searchID) {
            printf("Student found. Enter new CGPA: ");
            scanf("%f", &info[i].studentCGPA);
            printf("Enter new mobile number: ");
            scanf("%s", info[i].studentMobile);
            printf("Student information updated successfully.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", searchID);
}

void displayAll(struct StudentInfo *info, int numStudents) {
    printf("List of all students:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student %d:\n", i+1);
        printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile Number: %s\n\n", 
               info[i].studentName, info[i].studentID, info[i].studentDept, info[i].studentAge, info[i].studentGender,
               info[i].studentCGPA, info[i].studentMobile);
    }
}
