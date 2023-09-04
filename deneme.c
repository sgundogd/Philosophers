#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct s_thread
{
    pthread_t       thread;
    int             index;
} t_thread;;
typedef struct s_data
{
    t_thread        threads[100];
    pthread_mutex_t mutex;
} t_data;
void ft_appoint_index(t_data *data, int i)
{
    data->threads[i].index = i;
    pthread_mutex_lock(&data->mutex);
    if (data->threads[i].index % 2 == 0)
        printf("%i -> Ben Çiftim!\n", data->threads[i].index);
    else
        printf("%i -> Ben Tekim!\n", data->threads[i].index);
    pthread_mutex_unlock(&data->mutex);
}
void ft_flow(t_data *data, int i)
{
    ft_appoint_index(data, i);
}
void *ft_routine(void *arg)
{
    (void)arg;
    static int i = 0;
    int temp = i++;
    ft_flow(arg, temp);
    return 0;
};
int main(void)
{
    t_data data;
    pthread_mutex_init(&data.mutex, NULL);
    int i = 0;
    while(i < 100)
    {
		pthread_create(&(data.threads[i].thread), NULL, &ft_routine, &data);
        i++;
        usleep(400);//thread'lerin sırasıyla gitmesi!
    }
    i = 0;
        while (i < 100)
        {
            int cnt = pthread_join(data.threads[i].thread, NULL);//return 0 yerine geldiği zaman, process, threadlerin görevini bitirmesini bekliyor!
            if (cnt != 0)
            {
                printf("Error!\n");
                return 1;
            }
            i++;
        }
    pthread_mutex_destroy(&data.mutex);
    return 0;
}
