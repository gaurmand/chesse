## Perft Results

Iteration 0:
+ Standard mailbox board representation and algorithms

| Depth  | T1 (ms)   | T2 (ms)   | T3 (ms)   | Avg (ms)   |
|--------|-----------|-----------|-----------|------------|
| 1      | 0         | 0         | 0         | 0          |
| 2      | 0         | 0         | 0         | 0          |
| 3      | 10        | 10        | 10        | 10         |
| 4      | 152       | 152       | 153       | 152.33     |
| 5      | 3484      | 3476      | 3479      | 3479.67    |
| 6      | 86421     | 86257     | 86089     | 86255.67   |      
| 7      | ~24000000 | -         | -         | ~24000000  |

Main bottleneck is `isInCheck()`:
![Profile](i0.png)