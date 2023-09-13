//Multilevel Feedback Queue (RR+FCFS)
#include <iostream>
#include <queue>

using namespace std;

/*
1 <= Process數 <= 20
0 <= Arrival Time <= 100
1 <= Burst Time <= 30
1 <= Time Quantum <= 10
*/

struct process {

	int pid;
	int arrival_time;
	int burst_time;
	int burst_remaining_time;
	int complete_time;
	int waiting_time = 0;
	int turnaround_time;
	bool is_completed = false;
};

int number, q;
int timer = 0, q_time = 0, index1 = -1;
int complete_task;
int total_waiting_time = 0, total_turnaround_time = 0;
struct process p[25];
int fcfs_last_index = -1;
int rr_num, finish = 0;
int alg = 0; //alg=0 -> RR, alg=1 -> FCFS
queue<int> rr, fcfs;

void RR(), FCFS();

int main() {

	cin >> number;
	for (int i = 1; i <= number; i++) {
		p[i].pid = i;
		cin >> p[i].arrival_time;
	}
	for (int i = 1; i <= number; i++) {
		cin >> p[i].burst_time;
		p[i].burst_remaining_time = p[i].burst_time;
	}
	cin >> q;

	complete_task = number;
	rr_num = number;
	int first_value = 0;
	while (complete_task != 0) {

		//新進的process放到RR queue 
		for (int i = 1; i <= number; i++) {
			if (p[i].arrival_time == timer && p[i].is_completed == false) {
				rr.push(i);
				first_value = 1;
			}
		}

		if (first_value == 1) {
			if (rr.empty() == false || (rr_num != 0 && q_time != 0 && p[index1].burst_remaining_time != 0)) {
				if (alg == 1 && finish == 0)
					fcfs.push(index1);
				RR();
			}
			else if (rr.empty() == true) {
				if (alg == 1 && finish == 0)
					fcfs_last_index = index1;
				FCFS();
			}
		}

		timer++;
	}

	for (int i = 1; i <= number; i++) {
		cout << p[i].waiting_time << " " << p[i].turnaround_time << endl;
	}
	cout << total_waiting_time << endl;
	cout << total_turnaround_time << endl;
}

void RR() {

	//如果quantum用完或process已經執行完，就選下一個要執行的process 
	if (q_time == 0 || p[index1].burst_remaining_time == 0) {
		//把queue中最前面的值pop出來
		index1 = rr.front();
		rr.pop();
		q_time = q;
	}

	if (index1 != -1) {
		p[index1].burst_remaining_time--;
		for (int i = 1; i <= number; i++) {
			if ((i != index1) && (p[i].is_completed == false) && (p[i].arrival_time <= timer)) {
				p[i].waiting_time++;
			}
		}
	}

	//process執行完成的設定
	if (p[index1].burst_remaining_time == 0) {
		p[index1].is_completed = true;
		p[index1].complete_time = timer;
		p[index1].turnaround_time = p[index1].waiting_time + p[index1].burst_time;

		total_waiting_time += p[index1].waiting_time;
		total_turnaround_time += p[index1].turnaround_time;
		complete_task--;
		rr_num--;
	}
	else if (p[index1].burst_remaining_time != 0 && q_time == 1) {
		//還沒執行完的process放到FCFS的queue中
		fcfs.push(index1);
		rr_num--;
	}

	q_time--;
	alg = 0;

	return;
}

void FCFS() {

	index1 = fcfs.front();
	if (alg == 0 || finish == 1) {
		fcfs.pop();
	}
	else if (alg == 1)
		index1 = fcfs_last_index;

	if (index1 != -1) {
		p[index1].burst_remaining_time--;
		for (int i = 1; i <= number; i++) {
			if ((i != index1) && (p[i].is_completed == false) && (p[i].arrival_time <= timer)) {
				p[i].waiting_time++;
			}
		}
	}

	//process執行完成的設定
	if (p[index1].burst_remaining_time == 0) {
		p[index1].is_completed = true;
		p[index1].complete_time = timer;
		p[index1].turnaround_time = p[index1].waiting_time + p[index1].burst_time;

		total_waiting_time += p[index1].waiting_time;
		total_turnaround_time += p[index1].turnaround_time;
		complete_task--;
		finish = 1;
	}
	else {
		finish = 0;
	}

	alg = 1;

	return;
}

/*
test1:
3
0 2 8
7 4 1
3

Ans1:
5 12
4 8
0 1
9
21
*/


/*
test3:
3
1 3 9
7 4 1
3

Ans3:
5 12
4 8
0 1
9
21
*/

/*
test4:
4
0 2 4 10
7 4 5 1
3

Ans4:
10 17
6 10
5 10
0 1
21
38
*/