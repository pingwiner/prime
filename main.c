#include <stdio.h>

//Ищем простые числа от 2 до top
void prime(int top) {
    //Создаем массив и заполняем единицами
    char a[top + 1];
    for(int i = 0; i <= top; ++i) {
        a[i] = 1;
    }

    int d = 2;              //Начинаем с 2
    while (d <= top) {      //Пока не дойдем до максимального числа
        int j = d * 2;
        while (j < top + 1) {   //обнуляем все, что делится на d
            a[j] = 0;
            j += d;
        }
        while (!a[++d]);  //ищем следующий ненулевой элемент - это будет новое d
    }

    //Считаем количество оставшихся ненулевых элементов
    int count = 0;
    for (int i = 2; i < top + 1; ++i) {
        if (a[i]) count++;
    }
    printf("%d\n", count);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 0;
    //Открываем файл
    FILE* f = fopen(argv[1], "r");
    int lines;
    //Читаем количество заданий
    fscanf(f, "%d", &lines);

    for (int i = 0; i < lines; ++i) {
        int top;
        //Читаем число - верхнюю границу поиска
        fscanf(f, "%d", &top);
        //Вызываем функцию поиска простых чисел
        prime(top);
    }
    //Закрываем файл
    fclose(f);
    return 0;
}