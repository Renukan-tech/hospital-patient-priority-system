#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for patient details
struct Patient {
    int id;
    char name[50];
    int age;
    int priority;
};

// Swap function
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function
void heapify(struct Patient arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare left child
    if (left < n && arr[left].priority > arr[largest].priority)
        largest = left;

    // Compare right child
    if (right < n && arr[right].priority > arr[largest].priority)
        largest = right;

    // Swap and continue heapifying
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(struct Patient arr[], int n) {

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Display patients
void displayPatients(struct Patient arr[], int n) {

    printf("\n=========================================================\n");
    printf("          HOSPITAL PATIENT PRIORITY REPORT\n");
    printf("=========================================================\n");

    printf("%-10s %-20s %-10s %-10s\n",
           "ID", "NAME", "AGE", "PRIORITY");

    printf("---------------------------------------------------------\n");

    // Print from highest priority to lowest
    for (int i = n - 1; i >= 0; i--) {
        printf("%-10d %-20s %-10d %-10d\n",
               arr[i].id,
               arr[i].name,
               arr[i].age,
               arr[i].priority);
    }

    printf("=========================================================\n");
}

int main() {

    struct Patient patients[MAX];
    int n;

    printf("=============================================\n");
    printf(" HOSPITAL PATIENT PRIORITY MANAGEMENT SYSTEM\n");
    printf("=============================================\n");

    printf("\nEnter number of patients: ");
    scanf("%d", &n);

    // Input patient details
    for (int i = 0; i < n; i++) {

        printf("\nEnter details for Patient %d\n", i + 1);

        printf("Patient ID: ");
        scanf("%d", &patients[i].id);

        getchar();

        printf("Patient Name: ");
        fgets(patients[i].name, sizeof(patients[i].name), stdin);

        // Remove newline
        patients[i].name[strcspn(patients[i].name, "\n")] = 0;

        printf("Age: ");
        scanf("%d", &patients[i].age);

        printf("Priority Level (1-10): ");
        scanf("%d", &patients[i].priority);
    }

    // Sort using Heap Sort
    heapSort(patients, n);

    // Display final sorted report
    displayPatients(patients, n);

    // Highest priority patient
    printf("\nPatient to be treated first:\n");
    printf("----------------------------------\n");
    printf("Name     : %s\n", patients[n - 1].name);
    printf("Priority : %d\n", patients[n - 1].priority);

    return 0;
}