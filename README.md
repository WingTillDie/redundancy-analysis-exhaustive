# redundancy-analysis-exhaustive
Redundancy analysis using exhaustive search: exhaustiveSearch.cc  
Memory repair early abort using tensorflow: eeProjectOutput.ipynb  
[Try it](https://mybinder.org/v2/gh/WingTillDie/redundancy-analysis-exhaustive/master?filepath=eeProjectOutput.ipynb) on mybinder
## Description
This repo solve memory redundancy analysis using exhaustive search  
Try to repair using only spare rows first, then try to remove some spare row and find how much spare columns needed to repair the memory. This repo use combinatorics to try every combination of remove rows to find best solutions, called solution list.  
See II. E. Solution Search in [Fault Group Pattern Matching With Efficient Early Termination for High-Speed Redundancy Analysis](https://ieeexplore.ieee.org/abstract/document/8060577/) for related info and more advanced algorithms.  
### Purpose
This repo generate random fault points with solution list and use it as labelled training data for other machine learning algorithms, the sole purpose is use it to generate labelled data, not for fast redundancy analysis, so the algorithm might not be optimized in this repo.  
## Usage
Compile and run [exhaustiveSearch.cc](exhaustiveSearch.cc) to get results
## Detailed description
### Random fault generator
#### point_gen()
Generate random number in 0 to 2^31-1 using random(), if generated random number is larger than (RAND_MAX+1U)%(rdim*cdim), the number is discard then generate a new one, this mechanism ensure that the random number obtained is unnbiased.
Then use modulo operation to get fault index. 
#### points_gen()
Calls point_gen() multiple times to generate fault points, generated data are inserted into Tree, if inserted data have repeat then it will generate again to satisfy required number of fault points.
### Exhaustive search algorithm
Example: fault points at (1, 7), (1, 8), (2, 1), (3,5), (3,7)
  
Tree: (row:column)  
Subtree 0: 1: 7 8  
Subtree 1: 2: 1  
Subtree 2: 3: 5 7  
  
Solution list:  
(rows needed Columns needed: subtree index: column index)  
3 0:  
2 1: 1 : 1  
1 3: 0 1 : 1 7 8  
0 4: 0 1 2 : 1 5 7 8  
### Repairable detection
#### Case 1
If we have 3 spare rows and 3 spare columns  
Solution list:  
(rows needed columns needed: row index: column index)  
3 0: Reparable  
2 1: 1 : 1 Repairable  
1 3: 0 1 : 1 7 8 Repairable  
0 4: 0 1 2 : 1 5 7 8  
So it’s repairable  
#### Case 2
If we have 2 spare rows and 2 spare columns  
Solution list:  
(rows needed columns needed: row index: column index)  
3 0:  
2 1: 1 : 1 Repairable  
1 3: 0 1 : 1 7 8  
0 4: 0 1 2 : 1 5 7 8  
So it’s repairable  
#### Case 3
If we have 1 spare rows and 1 spare columns  
Solution list:  
(rows needed columns needed: row index: column index)  
3 0:  
2 1: 1 : 1  
1 3: 0 1 : 1 7 8  
0 4: 0 1 2 : 1 5 7 8  
So it’s not repairable  
