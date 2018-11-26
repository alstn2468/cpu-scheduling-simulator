CPU Scheduling Algorithm Simulator
==================================
Soonchunhyang University<br/>
Department of Computer Software Engineering
------------------------------------------

##  [김민수](https://github.com/alstn2468)
## [ [Facebook](https://www.facebook.com/profile.php?id=100003769223078) ] [ [Github](https://github.com/alstn2468) ] [ [LinkedIn](https://www.linkedin.com/in/minsu-kim-336289160/) ] [ [Webpage](https://kimminsu.ml) ]<br/>

## Test Case 1
Quantum : 2

|PID|Burst Time|Arrive Time|Priority|
|:-:|:-:|:-:|:-:|
|P1|2|0|1|
|P2|9|1|3|
|P3|5|2|2|
|P4|11|3|4|
|P5|2|4|5|

<br/>

## Test Case 2
Quantum : 5

|PID|Burst Time|Arrive Time|Priority|
|:-:|:-:|:-:|:-:|
|P1|10|0|4|
|P2|28|1|2|
|P3|6|2|5|
|P4|4|3|1|
|P5|14|4|3|

<br/>

## FCFS (First Come First Served)
- 선입선처리 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/FCFS.h)

- Test Image
> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/FCFS1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/FCFS2.PNG" width="700" height="auto">

<br/>

## SJF (Shortest Job First)
- 최소작업 우선 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/SJF.h)

- Test Image
> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/SJF1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/SJF2.PNG" width="700" height="auto">

<br/>

## SRT (Shortest Remaining Time)
- 선점 최소작업 우선 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/SRT.h)

- Test Image
> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/SRT1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/SRT2.PNG" width="700" height="auto">

<br/>

## Non-Preemptive Priority Scheduling
- 비선점 우선순위 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/NPPS.h)

- Test Image

> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/NPPS1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/NPPS2.PNG" width="700" height="auto">

<br/>

## Preemptive Priority Scheduling
- 선점 우선순위 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/PPS.h)

- Test Image

> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/PPS1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/PPS2.PNG" width="700" height="auto">

<br/>

## RR (Round Robin)
- 라운드 로빈 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/RR.h)

- Test Image
> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/RR1.PNG" width="700" height="auto">

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/RR2.PNG" width="700" height="auto">

<br/>

## HRN (Highest Response-Ratio Next)
- 최상 응답 비율 우선 스케쥴링<br/>
[[코드]](https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/CpuSchedulingAlgorithmsModule/HRN.h)

- Test Image
> Test Case 1

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/HRN1.PNG" width="700" height="auto">'

> Test Case 2

<img src="https://github.com/alstn2468/CPU_Scheduling_Simulator/blob/master/Test%20Image/HRN2.PNG" width="700" height="auto">

<br/>

## Performance Analysis

### Test Case 1

||Average Waiting Time|Average Turnaround Time|Average Response Time|
|:-:|:-:|:-:|:-:|
|FCFS|9.20|14.60|11.20|
|SJF|5.20|11.00|7.20|
|SRT|5.00|10.80|6.60|
|NPPS|8.40|14.20|10.40|
|PPS|8.40|14.20|10.40|
|RR|9.40|15.20|4.00|
|HRN|6.80|12.60|8.80|

- Average Waiting Time

> SRT > SJF > HRN > NPPS, PPS > FCFS > RR

- Average Response Time

> RR > SRT > SJF > HRN > NPPS, PPS > FCFS

- Average Turnaround Time

> SRT > SJF > HRN > NPPS, PPS > FCFS > RR

- - -

### Test Case 2

||Average Waiting Time|Average Turnaround Time|Average Response Time|
|:-:|:-:|:-:|:-:|
|FCFS|26.00|36.40|28.00|
|SJF|13.60|26.00|15.60|
|SRT|12.60|25.60|11.80|
|NPPS|22.40|34.80|24.40|
|PPS|26.60|39.00|18.60|
|RR|24.40|36.80|10.00|
|HRN|14.00|26.40|16.00|

- Average Waiting Time

> SRT > SJF > HRN > NPPS > RR > FCFS > PPS

- Average Response Time

> RR > SRT > SJF > HRN > PPS > NPPS > FCFS

- Average Turnaround Time

> SRT > SJF > HRN > NPPS > FCFS > RR > PPS

<br/>

## Contributor
- [김혜린](https://www.github.com/merry-Hyelyn)
- [배서형](https://www.github.com/gurumsh)
