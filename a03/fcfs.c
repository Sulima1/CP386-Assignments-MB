#include <stdio.h>
#include <stdlib.h>

struct threadInfo{
    int p_id;
    int arr_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int time_to_complete;
};

//function to handle use of threads
void handle_threads(FILE *input_file, int thread_count){
    struct threadInfo *thread_list = malloc(thread_count * sizeof(struct threadInfo));

    int j = 0;
    double total_turn_around_time = 0;
    double total_wait_time = 0;

    printf("%-14s %-18s %-14s %-18s %-18s %s\n", "Thread ID", "Arrival Time", "Burst Time", "Completion Time", "Turn Around Time", "Waiting Time");
    
    while (fscanf(input_file, "%d, %d, %d ", &thread_list[j].p_id, &thread_list[j].arr_time, &thread_list[j].burst_time) == 3){
        if (thread_list[j].arr_time == 0){
            thread_list[j].time_to_complete = thread_list[j].burst_time;
        }
        else{
            thread_list[j].time_to_complete = thread_list[j - 1].time_to_complete + thread_list[j].burst_time; 
        }

        //calculate turnaround time per thread and total turn around time
        thread_list[j].turn_around_time = thread_list[j].time_to_complete - thread_list[j].arr_time;
        total_turn_around_time += thread_list[j].turn_around_time;

        //calculate waiting time per thread and total turn waiting time
        thread_list[j].waiting_time = thread_list[j].turn_around_time - thread_list[j].burst_time;
        total_wait_time += thread_list[j].waiting_time;

        printf("%-18d %-18d %-18d %-18d %-18d %-18d\n", thread_list[j].p_id, thread_list[j].arr_time, thread_list[j].burst_time, thread_list[j].time_to_complete, thread_list[j].turn_around_time, thread_list[j].waiting_time);
        j++;
    }
    if (j != thread_count) {
        printf("File reading error, please check the contents");
        exit(1);
    }

    printf("The average waiting time: %.2lf\nThe average turn-around time: %.2lf\n", total_wait_time / thread_count, total_turn_around_time / thread_count);

    free(thread_list);
}

int main(int argc, char const *argv[]){

    FILE *input_file = fopen(argv[1], "r");

    if (input_file == NULL){
        printf("Unable to open file please check your input ");
        exit(1);
    }

    int thread_count = 0;
    int filler;

    //count the number of threads to be created
    while (fscanf(input_file, "%d, %d, %d ", &filler, &filler, &filler) == 3){
        thread_count++;
    }

    fclose(input_file);
    fopen(argv[1], "r");

    handle_threads(input_file, thread_count);
    fclose(input_file);
    
    return 0;
}