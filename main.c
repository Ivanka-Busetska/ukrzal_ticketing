#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char from[50];
    char to[50];
    char departure[20];
    char arrival[20];
} Train;

typedef struct {
    char name[50];
    Train train;
} Ticket;

void showMenu() {
    printf("\n--- Укрзалізниця: Сервіс купівлі квитків ---\n"); //додано функцію пошуку
    printf("1. Переглянути всі поїзди\n");
    printf("2. Знайти поїзд за містом призначення\n");
    printf("3. Придбати квиток\n");
    printf("4. Переглянути куплені квитки\n");
    printf("0. Вийти\n");
    printf("Ваш вибір: ");
}

void viewTrains() {
    FILE *file = fopen("trains.txt", "r");
    if (!file) {
        printf("Помилка відкриття файлу trains.txt\n");
        return;
    }
    Train train;
    printf("\nСписок поїздів:\n");
    while (fscanf(file, "%d %s %s %s %s",
                  &train.id, train.from, train.to, train.departure, train.arrival) == 5) {
        printf("ID: %d | %s -> %s | Відправлення: %s | Прибуття: %s\n",
               train.id, train.from, train.to, train.departure, train.arrival);
    }
    fclose(file);
}

void searchTrain() {
    char city[50];
    printf("Введіть місто призначення: ");
    scanf("%s", city);
    FILE *file = fopen("trains.txt", "r");
    if (!file) {
        printf("Не вдалося відкрити файл trains.txt\n");
        return;
    }
    Train train;
    int found = 0;
    printf("Результати пошуку:\n");
    while (fscanf(file, "%d %s %s %s %s",
                  &train.id, train.from, train.to, train.departure, train.arrival) == 5) {
        if (strcmp(train.to, city) == 0) {
            printf("ID: %d | %s -> %s | Відправлення: %s | Прибуття: %s\n",
                   train.id, train.from, train.to, train.departure, train.arrival);
            found = 1;
        }
    }
    if (!found) printf("Поїздів у місто %s не знайдено.\n", city);
    fclose(file);
}

void buyTicket() {
    int trainId;
    char name[50];
    Train train;
    int found = 0;
    printf("Введіть ваше ім’я: ");
    scanf("%s", name);
    printf("Введіть ID поїзда: ");
    scanf("%d", &trainId);

    FILE *file = fopen("trains.txt", "r");
    if (!file) {
        printf("Не вдалося відкрити файл trains.txt\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %s",
                  &train.id, train.from, train.to, train.departure, train.arrival) == 5) {
        if (train.id == trainId) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Поїзд з ID %d не знайдено.\n", trainId);
        return;
    }

    FILE *out = fopen("tickets.txt", "a");
    if (!out) {
        printf("Не вдалося відкрити файл tickets.txt\n");
        return;
    }

    fprintf(out, "%s %d %s %s %s %s\n",
            name, train.id, train.from, train.to, train.departure, train.arrival);
    fclose(out);

    printf("Квиток успішно придбано!\n");
}

void viewTickets() {
    FILE *file = fopen("tickets.txt", "r");
    if (!file) {
        printf("Немає куплених квитків або файл не існує.\n");
        return;
    }
    char name[50];
    Train train;
    printf("\nВаші квитки:\n");
    while (fscanf(file, "%s %d %s %s %s %s",
                  name, &train.id, train.from, train.to, train.departure, train.arrival) == 6) {
        printf("Пасажир: %s | %s -> %s | Відправлення: %s | Прибуття: %s\n",
               name, train.from, train.to, train.departure, train.arrival);
    }
    fclose(file);
}

int main() {
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: viewTrains(); break;
            case 2: searchTrain(); break;
            case 3: buyTicket(); break;
            case 4: viewTickets(); break;
            case 0: printf("Вихід з програми.\n"); break;
            default: printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    } while (choice != 0);
    return 0;
}
