//RR
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

int main() {

	int number, q;
	struct process p[25];
	queue<int> qq;

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

	int timer = 0, q_time = 0, index = -1;
	int complete_task = number;
	int total_waiting_time = 0, total_turnaround_time = 0;
	int first_value = 0;
	int next_value = 0;


	for (int i = 1; i <= number; i++) {
		if (p[i].arrival_time == 0 && p[i].is_completed == false) {
			qq.push(i);
			first_value = 1;
		}
	}

	while (complete_task != 0) {

		//下一秒到達的process放到queue中
		for (int i = 1; i <= number; i++) {
			if (p[i].arrival_time == timer + 1 && p[i].is_completed == false) {
				qq.push(i);
				next_value = 1;
			}
		}

		if (first_value == 1) {

			//如果quantum用完或process已經執行完，就選下一個要執行的process 
			if (q_time == 0 || p[index].burst_remaining_time == 0) {
				//把queue中最前面的值pop出來
				index = qq.front();
				qq.pop();
				q_time = q;
			}

			if (index != -1) {
				p[index].burst_remaining_time--;
				for (int i = 1; i <= number; i++) {
					if ((i != index) && (p[i].is_completed == false) && (p[i].arrival_time <= timer)) {
						p[i].waiting_time++;
					}
				}
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
			else if (p[index].burst_remaining_time != 0 && q_time == 1) {
				//還沒執行完的process再放回queue中
				qq.push(index);
			}
			q_time--;
		}
		timer++;

		if (next_value == 1)
			first_value = 1;
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
7 5 3
3

Ans1:
8 15
7 12
5 8
20
35
*/

/*
test2:
4
0 2 4 5
7 4 1 4
4

Ans2:
5 12
2 6
4 5
7 11
18
34
*/

/*
test3:
5
0 2 4 6 8
3 6 4 5 2
4

Ans:
0 3
9 15
3 7
9 14
9 11
30
50
*/

/*
test4:
3
1 3 5
7 5 3
3

Ans:
8 15
7 12
5 8
20
35
*/
