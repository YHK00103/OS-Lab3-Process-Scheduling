//SRTF
#include <iostream>

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

int main() {

	int number;
	struct process p[25];

	cin >> number;
	for (int i = 1; i <= number; i++) {
		p[i].pid = i;
		cin >> p[i].arrival_time;
	}
	for (int i = 1; i <= number; i++) {
		cin >> p[i].burst_time;
		p[i].burst_remaining_time = p[i].burst_time;
	}

	int timer = 0;
	int complete_task = number;
	int total_waiting_time = 0, total_turnaround_time = 0;

	while (complete_task != 0) {

		int min = 9999999;
		int index = -1;

		for (int i = 1; i <= number; i++) {
			if (p[i].arrival_time <= timer && p[i].is_completed != true) {

				//選擇目前remaining time最少的process
				if (p[i].burst_remaining_time < min) {
					min = p[i].burst_remaining_time;
					index = i;
				}

				//如果remaining time相同，選擇arrival time最早的process
				if (p[i].burst_remaining_time == min) {
					if (p[i].arrival_time < p[index].arrival_time) {
						min = p[i].burst_remaining_time;
						index = i;
					}
				}
			}
		}

		if (index != -1) {
			p[index].burst_remaining_time--;
			for (int i = 1; i <= number; i++) {
				if ((i != index) && (p[i].is_completed == false) && (p[i].arrival_time <= timer)) {
					p[i].waiting_time++;
				}
			}
			//scheduling[timer] == p[index].pid;
		}

		//process執行完成的設定
		if (p[index].burst_remaining_time == 0) {
			p[index].is_completed = true;
			p[index].complete_time = timer;
			p[index].turnaround_time = p[index].waiting_time + p[index].burst_time;

			total_waiting_time += p[index].waiting_time;
			total_turnaround_time += p[index].turnaround_time;
			complete_task--;
		}
		timer++;
	}

	for (int i = 1; i <= number; i++) {
		cout << p[i].waiting_time << " " << p[i].turnaround_time << endl;
	}

	cout << total_waiting_time << endl;

	cout << total_turnaround_time << endl;
}

/*
test1:
3
0 2 4
6 3 1

Ans1:
4 10
0 3
1 2
5
15
*/

/*
test2:
4
0 1 2 3
8 4 9 5

Ans2:
9 17
0 4
15 24
2 7
26
52
*/

/*
test3:
5
0 2 4 6 8
3 6 4 5 2

Ans3:
0 3
7 13
0 4
9 14
0 2
16
36
*/