# OS-Lab3-Process-Scheduling

## HW3-1 Shortest Remaining Time First Scheduling
Example:  
![image](https://github.com/YHK00103/OS-Lab3-Process-Scheduling/assets/117156581/70c32feb-3b41-4a5d-870d-8ab7e175aa8a)

## HW3-2 Round-Robin
Example: (Time Quantum = 3)  
![image](https://github.com/YHK00103/OS-Lab3-Process-Scheduling/assets/117156581/8b5b1aab-7bb6-4e10-ad40-d964ba08d70a)

## HW3-3 Multilevel Feedbck Queue (RR+FCFS)
1. Processes in lower priority queue is selected if the higher queues are empty.  
2. If a new process comes to higher priority queue, currently executing process in lower priority queue will be preempted by it.  
3. When a new job comes, it first enters queue 𝑄0 which is served as RR. As it gains CPU, job receives “t” time unit.   
4. If it doesn’t finish in “t” time unit, job is moved to the next queue 𝑄1 which is served as FCFS.  
5. The preempted process will be re-inserted to the end of Q1
![image](https://github.com/YHK00103/OS-Lab3-Process-Scheduling/assets/117156581/a7eb0e0a-22ad-4e33-a271-6a995abe857b)

Example: (Time Quantum = 3)  
![image](https://github.com/YHK00103/OS-Lab3-Process-Scheduling/assets/117156581/39434ffc-ea93-4062-8f3a-5a42623537af)
