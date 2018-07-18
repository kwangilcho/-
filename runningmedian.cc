#include <vector>
#include <queue>
#include <cstdio>

#define START_SEQ_NUM 1983
using namespace std;

struct RunningMedian {
    int sequence_length;
    int a;
    int b;
};

void UpdateSequenceNumber(RunningMedian &running_median, long long &last_seq_num)
{
    last_seq_num = (last_seq_num * running_median.a + running_median.b) % 20090711;
}

void BalanceHeaps(priority_queue<int, vector<int>, greater<int> > &min_heap,
                  priority_queue<int, vector<int>, less<int> > &max_heap) 
{
    if (min_heap.size() > max_heap.size()) {
        max_heap.push(min_heap.top());
        min_heap.pop();
    }
    if (min_heap.size() && min_heap.top() < max_heap.top()) {
        int min_top = min_heap.top();
        int max_top = max_heap.top();
        min_heap.pop();
        max_heap.pop();
        min_heap.push(max_top);
        max_heap.push(min_top);
    }
}

void RunMedian(RunningMedian &running_median)
{
    priority_queue<int, vector<int>, greater<int> > min_heap;
    priority_queue<int, vector<int>, less<int> > max_heap;
    long long curr_seq_num = START_SEQ_NUM;
    long long sum_meidans = 0;
    for (int i = 0; i < running_median.sequence_length; i++) {
        min_heap.push(curr_seq_num);
        BalanceHeaps(min_heap, max_heap);
        sum_meidans += max_heap.top();
        UpdateSequenceNumber(running_median, curr_seq_num);
    }
    printf("%lld\n", sum_meidans % 20090711);
}

void GetTestCase(RunningMedian &running_median) {
    scanf("%d %d %d", 
            &running_median.sequence_length, 
            &running_median.a, &running_median.b);
}

void GetNumTestCases(int &num_testcases)
{
    scanf("%d", &num_testcases);
}

int main(int argc, const char *argv[])
{
    int num_testcases;
    GetNumTestCases(num_testcases);
    for (int i = 0; i < num_testcases; i++) {
        RunningMedian running_median;
        GetTestCase(running_median);
        RunMedian(running_median);
    }
}
