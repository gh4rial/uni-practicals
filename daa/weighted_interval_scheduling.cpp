#include <cstdlib>
#include <iostream>

struct Job {
    int start_time, finish_time;
    int weight;
};

// sort can be improved -> insertion, count?
void sort_jobs(Job *jobs, int job_count)
{
    for (int i = 0; i < job_count - 1; i++) {
        int min_ft_idx = i;

        for (int j = i + 1; j < job_count; j++) {
            if (jobs[j].finish_time < jobs[min_ft_idx].finish_time) {
                min_ft_idx = j;
            }
        }

        std::swap(jobs[i], jobs[min_ft_idx]);
    }
}

Job *read_weighted_jobs(int *out_job_count)
{
    int job_count;

    std::cout << "Enter number of jobs: ";
    std::cin >> job_count;

    if (job_count < 1) {
        std::cout << "Error: Number of jobs must be positive\n";
        std::exit(1);
    }

    Job *jobs = new Job[job_count];

    std::cout << "Enter jobs:\n";
    for (int i = 0; i < job_count; i++) {
        int start_time, finish_time, weight;

        std::cout << "Job " << i+1 << ":\n";

        std::cout << "  Enter start time: ";
        std::cin >> start_time;

        if (start_time < 0) {
            std::cout << "Error: invalid start time\n";
            std::exit(1);
        }

        std::cout << "  Enter finish time: ";
        std::cin >> finish_time;

        if (finish_time < 0 || finish_time <= start_time) {
            std::cout << "Error: invalid finish time\n";
            std::exit(1);
        }

        std::cout << "  Enter weight: ";
        std::cin >> weight;

        if (weight < 0) {
            std::cout << "Error: Invalid weight\n";
            std::exit(1);
        }

        jobs[i].start_time = start_time;
        jobs[i].finish_time = finish_time;
        jobs[i].weight = weight;
    }

    *out_job_count = job_count;

    return jobs;
}

// change to binary search
int job_prev(int job_idx, Job *jobs)
{
    for (int i = job_idx - 1; i >= 0; i--) {
        if (jobs[i].finish_time <= jobs[job_idx].start_time) {
            return i;
        }
    }

    return -1;
}

int compute_OPT_iter(Job *jobs, int job_count, int *memo_arr)
{
    memo_arr[0] = jobs[0].weight;

    for (int i = 1; i < job_count; i++) {
        int prev_job = job_prev(i, jobs);
        memo_arr[i] = (memo_arr[i-1] > (jobs[i].weight + memo_arr[prev_job]))
            ? memo_arr[i-1] : (jobs[i].weight + memo_arr[prev_job]);
    }

    return memo_arr[job_count-1];
}

int compute_OPT(int job_idx, Job *jobs, int job_count, int *memo_arr)
{
    if (job_idx == -1) {
        return 0;
    }

    if (memo_arr[job_idx] != -1) {
        return memo_arr[job_idx];
    }

    int prev_job = job_prev(job_idx, jobs);

    int included = jobs[job_idx].weight + compute_OPT(prev_job, jobs, job_count, memo_arr);
    int excluded = compute_OPT(job_idx - 1, jobs, job_count, memo_arr);

    memo_arr[job_idx] = (included > excluded) ? included : excluded;
    return memo_arr[job_idx];
}

int main()
{
    int job_count; 

    Job *jobs = read_weighted_jobs(&job_count);

    sort_jobs(jobs, job_count);

    int *memo_arr = new int[job_count];

    for (int i = 0; i < job_count; i++) {
        memo_arr[i] = -1;
    }

    //int result = compute_OPT(job_count - 1, jobs, job_count, memo_arr);
    int result = compute_OPT_iter(jobs, job_count, memo_arr);

    std::cout << "Result: " << result << '\n';

    return 0;
}
