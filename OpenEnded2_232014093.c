#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int id;
    char department[10];
    int age;
    char gender;
    float cgpa;
    char mobile[15];
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, Student student) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = student;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Student dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        exit(1);
    }
    Node* temp = q->front;
    Student data = temp->data;
    q->front = q->front->next;
    free(temp);
    return data;
}

void storeStudent(Queue* cseQueue, Queue* eeeQueue) {
    Student newStudent;
    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter student department (CSE/EEE): ");
    scanf("%s", newStudent.department);
    printf("Enter student age: ");
    scanf("%d", &newStudent.age);
    printf("Enter student gender (M/F): ");
    scanf(" %c", &newStudent.gender);
    printf("Enter student CGPA: ");
    scanf("%f", &newStudent.cgpa);
    printf("Enter student mobile number: ");
    scanf("%s", newStudent.mobile);

    if (strcmp(newStudent.department, "CSE") == 0)
        enqueue(cseQueue, newStudent);
    else if (strcmp(newStudent.department, "EEE") == 0)
        enqueue(eeeQueue, newStudent);
    else
        printf("Invalid department!\n");
}

void searchStudent(Queue* cseQueue, Queue* eeeQueue, int searchID, char searchMobile[]) {
    Queue* searchQueue;
    if (!isEmpty(cseQueue) && cseQueue->front->data.id == searchID) {
        searchQueue = cseQueue;
    } else if (!isEmpty(eeeQueue) && eeeQueue->front->data.id == searchID) {
        searchQueue = eeeQueue;
    } else if (!isEmpty(cseQueue) && strstr(cseQueue->front->data.mobile, searchMobile) != NULL) {
        searchQueue = cseQueue;
    } else if (!isEmpty(eeeQueue) && strstr(eeeQueue->front->data.mobile, searchMobile) != NULL) {
        searchQueue = eeeQueue;
    } else {
        printf("Student not found.\n");
        return;
    }

    printf("Student found:\n");
    printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile: %s\n",
           searchQueue->front->data.name, searchQueue->front->data.id, searchQueue->front->data.department,
           searchQueue->front->data.age, searchQueue->front->data.gender, searchQueue->front->data.cgpa,
           searchQueue->front->data.mobile);
}

void updateStudent(Queue* cseQueue, Queue* eeeQueue, int searchID) {
    Queue* updateQueue;
    if (!isEmpty(cseQueue) && cseQueue->front->data.id == searchID) {
        updateQueue = cseQueue;
    } else if (!isEmpty(eeeQueue) && eeeQueue->front->data.id == searchID) {
        updateQueue = eeeQueue;
    } else {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new CGPA: ");
    scanf("%f", &updateQueue->front->data.cgpa);
    printf("Enter new mobile number: ");
    scanf("%s", updateQueue->front->data.mobile);
    printf("Student information updated successfully.\n");
}

void displayStudents(Queue* cseQueue, Queue* eeeQueue) {
    printf("CSE Department Students:\n");
    if (!isEmpty(cseQueue)) {
        Node* temp = cseQueue->front;
        while (temp != NULL) {
            printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile: %s\n\n",
                   temp->data.name, temp->data.id, temp->data.department,
                   temp->data.age, temp->data.gender, temp->data.cgpa, temp->data.mobile);
            temp = temp->next;
        }
    } else {
        printf("No students in CSE Department.\n");
    }

    printf("EEE Department Students:\n");
    if (!isEmpty(eeeQueue)) {
        Node* temp = eeeQueue->front;
        while (temp != NULL) {
            printf("Name: %s\nID: %d\nDepartment: %s\nAge: %d\nGender: %c\nCGPA: %.2f\nMobile: %s\n\n",
                   temp->data.name, temp->data.id, temp->data.department,
                   temp->data.age, temp->data.gender, temp->data.cgpa, temp->data.mobile);
            temp = temp->next;
        }
    } else {
        printf("No students in EEE Department.\n");
    }
}

int main() {
    Queue cseQueue, eeeQueue;
    initQueue(&cseQueue);
    initQueue(&eeeQueue);
    int choice;
    int searchID;
    char searchMobile[15];

    do {
        printf("\nStudent Management System\n");
        printf("1. Store new student information\n");
        printf("2. Search student by ID or mobile number\n");
        printf("3. Update student information\n");
        printf("4. Display all students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                storeStudent(&cseQueue, &eeeQueue);
                break;
            case 2:
                printf("Enter student ID to search: ");
                scanf("%d", &searchID);
                printf("Enter student mobile number to search: ");
                scanf("%s", searchMobile);
                searchStudent(&cseQueue, &eeeQueue, searchID, searchMobile);
                break;
            case 3:
                printf("Enter student ID to update: ");
                scanf("%d", &searchID);
                updateStudent(&cseQueue, &eeeQueue, searchID);
                break;
            case 4:
                displayStudents(&cseQueue, &eeeQueue);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
