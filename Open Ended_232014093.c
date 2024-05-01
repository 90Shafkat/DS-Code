#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Appointment {
    char title[100];
    char purpose[200];
    char date_time[50];
    int duration;
    char participants[100];
    struct Appointment* next;
};


struct Appointment* createAppointment(char title[], char purpose[], char date_time[], int duration, char participants[]) {
    struct Appointment* newAppointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    if (newAppointment == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newAppointment->title, title);
    strcpy(newAppointment->purpose, purpose);
    strcpy(newAppointment->date_time, date_time);
    newAppointment->duration = duration;
    strcpy(newAppointment->participants, participants);
    newAppointment->next = NULL;
    return newAppointment;
}


void addAppointment(struct Appointment** head, struct Appointment* newAppointment) {
    if (*head == NULL) {
        *head = newAppointment;
    } else {
        struct Appointment* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAppointment;
    }
}


struct Appointment* searchAppointment(struct Appointment* head, char title[]) {
    struct Appointment* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}


void removeAppointment(struct Appointment** head, char title[]) {
    struct Appointment* temp = *head;
    struct Appointment* prev = NULL;

    
    if (temp != NULL && strcmp(temp->title, title) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    
    if (temp == NULL) {
        printf("Appointment with title '%s' not found.\n", title);
        return;
    }

    
    prev->next = temp->next;
    free(temp);
}


void updateAppointment(struct Appointment* appointment, char new_date_time[]) {
    strcpy(appointment->date_time, new_date_time);
}


void displayAppointments(struct Appointment* head) {
    printf("----- List of Appointments -----\n");
    struct Appointment* temp = head;
    while (temp != NULL) {
        printf("Title: %s\nPurpose: %s\nDate & Time: %s\nDuration: %d minutes\nParticipants: %s\n\n",
               temp->title, temp->purpose, temp->date_time, temp->duration, temp->participants);
        temp = temp->next;
    }
}

int main() {
    struct Appointment* appointments = NULL;

    
    addAppointment(&appointments, createAppointment("Meeting 1", "Discuss project updates", "2024-03-17 10:00", 60, "John, Alice"));
    addAppointment(&appointments, createAppointment("Meeting 2", "Review budget proposals", "2024-03-18 14:30", 90, "David, Emma"));
    addAppointment(&appointments, createAppointment("Training Session", "New software training", "2024-03-20 09:00", 120, "All employees"));

    
    displayAppointments(appointments);

    
    char searchTitle[100] = "Meeting 2";
    struct Appointment* foundAppointment = searchAppointment(appointments, searchTitle);
    if (foundAppointment != NULL) {
        printf("Appointment found:\n");
        printf("Title: %s\nPurpose: %s\nDate & Time: %s\nDuration: %d minutes\nParticipants: %s\n\n",
               foundAppointment->title, foundAppointment->purpose, foundAppointment->date_time,
               foundAppointment->duration, foundAppointment->participants);
    } else {
        printf("Appointment with title '%s' not found.\n", searchTitle);
    }

    
    char removeTitle[100] = "Meeting 1";
    removeAppointment(&appointments, removeTitle);
    printf("After removing '%s':\n", removeTitle);
    displayAppointments(appointments);

    
    char updateTitle[100] = "Training Session";
    char newDateTime[50] = "2024-03-22 09:00";
    struct Appointment* appointmentToUpdate = searchAppointment(appointments, updateTitle);
    if (appointmentToUpdate != NULL) {
        updateAppointment(appointmentToUpdate, newDateTime);
        printf("Appointment '%s' updated.\n", updateTitle);
    } else {
        printf("Appointment with title '%s' not found.\n", updateTitle);
    }
    printf("After updating '%s':\n", updateTitle);
    displayAppointments(appointments);

    
    struct Appointment* current = appointments;
    while (current != NULL) {
        struct Appointment* next = current->next;
        free(current);
        current = next;
    }
    appointments = NULL;

    return 0;
}
