#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int index;
    int sleep_time;
} Data;

void* routine(void*);

int main(int argc, char* argv[]) {
    char choice;
    do {
        pthread_t thread[5];
        int arr[5];
        
        for (int j = 0; j < 5; j++) {
            printf("Введите время сна для потока %d: ", j+1);
            scanf("%d", arr+j);
        }
        
        for (int i = 0; i < 5; i++) {
            Data* data = malloc(sizeof(Data));
            data->index = i;
            data->sleep_time = arr[i];
            pthread_create(&thread[i], NULL, &routine, data);
            printf("Поток %d начал работу\n", data->index+1);
        }
        
        for (int j = 0; j < 50; j++) printf("=");
        printf("\n");
        
        for (int i = 0; i < 5; i++) {
            pthread_join(thread[i], NULL);
        }
        
        printf("Успешно!\n\n");
        printf("Нажмите 'x' для выхода или 'r' для повтора: ");
        scanf(" %c", &choice);
    } while (choice != 'x');
    
    return 0;
}

void* routine(void* arg) {
    Data* data = (Data*)arg;
    sleep(data->sleep_time);
    printf("Поток %d завершил работу через %d секунд\n", data->index+1, data->sleep_time);
    free(arg);
    return NULL;
}
