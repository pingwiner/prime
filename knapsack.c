#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int value;
    int weight;
    int stolen;
} Item;

Item items[100];
Item best;

void steal(Item knapsack, Item* items, int index, int n, int max_weight) {
    //Кладем вещь в рюкзак - прибавляем вес и ценность
    knapsack.value += items[index].value;
    knapsack.weight += items[index].weight;
    //Если вес больше максимального - отказываемся
    if (knapsack.weight > max_weight) return;

    items[index].stolen = TRUE;
    //Если ценность рюкзака больше, чем последний лучший вариант - обновляем лучший вариант
    if (best.value < knapsack.value) {
        best.value = knapsack.value;
        best.weight = knapsack.weight;
    }

    //Крадем следующую вещь
    for (int i = 0; i < n; i++) {
        if (items[i].stolen) continue;
        steal(knapsack, items, i, n, max_weight);
    }

    items[index].stolen = FALSE;
}

void do_task(FILE* f) {
    int n, w;

    //Читаем количество вещей и максимальный вес
    fscanf(f, "%d %d", &n, &w);

    //Заполняем массив вещей
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %d", &items[i].value, &items[i].weight);
        items[i].stolen = FALSE;
    }

    //Лучший вариант - пока нулевой
    best.weight = 0;
    best.value = 0;

    //Рюкзак - пока пуст
    Item knapsack;
    knapsack.weight = 0;
    knapsack.value = 0;

    //По очереди крадем каждую вещь
    for (int i = 0; i < n; i++) {
        steal(knapsack, items, i, n, w);
    }

    //Выводим лучший вариант
    printf("%d %d\n", best.value, best.weight);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 0;
    //Открываем файл
    FILE* f = fopen(argv[1], "r");
    int tasks;
    //Читаем количество заданий
    fscanf(f, "%d", &tasks);

    for (int i = 0; i < tasks; ++i) {
        //для каждого задания вызываем функцию
        do_task(f);
    }
    //Закрываем файл
    fclose(f);
    return 0;
}