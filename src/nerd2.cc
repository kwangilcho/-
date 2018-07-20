#include <cstdio>
#include <vector>
#include <map>

using namespace std;

bool Verify(map<int, int> &candidates, pair<int, int> &applicant)
{
    map<int, int>::iterator iter = candidates.upper_bound(applicant.first);
    if (iter == candidates.end()) {
        return true;
    }
    return applicant.second > iter->second;
}

void RemoveUncertified(map<int, int> &candidates, pair<int, int> &applicant)
{
    map<int, int>::iterator iter = candidates.lower_bound(applicant.first);
    map<int, int>::iterator target;

    if (iter == candidates.begin()) {
        return;
    }

    iter--;
    while (true) {
        if (iter == candidates.begin()) {
            if (iter->second < applicant.second) {
                candidates.erase(iter);
            }
            break;
        }
        if (iter->second > applicant.second) {
            break;
        }
        target = iter;
        iter--;
        candidates.erase(target);
    }
}


void NextApplicant(pair<int, int> &applicant)
{
    scanf("%d %d", &applicant.first, &applicant.second);
}

void GetNumApplicants(int &num_applicants)
{
    scanf("%d", &num_applicants);
}

void FilterNerds()
{
    map<int, int> candidates;
    pair<int, int> applicant;

    int num_applicants;
    GetNumApplicants(num_applicants);
    int sum_each_step_candidates = 0;
    for (int i = 0; i < num_applicants; i++) {
        NextApplicant(applicant);
        if (Verify(candidates, applicant)) {
            candidates.insert(applicant);
            RemoveUncertified(candidates, applicant);
        }
        sum_each_step_candidates += candidates.size();
    }
    printf("%d\n", sum_each_step_candidates);
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
        FilterNerds();
    }
}
