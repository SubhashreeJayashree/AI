Optimal Dependency Scheduling
You are the lead architect for "Project Phoenix," the mission to rebuild a galaxy-wide software system from scratch after a critical failure. The project is composed of N distinct modules, indexed 1 to N. These modules have a complex web of dependencies, which can be represented as a rooted tree, with module 1 being the ultimate root. A module can only be built if its direct parent module in the dependency tree has already been completed.

Your team has a single, highly-specialized build server, meaning you can only work on one module at a time. For each module i, you have estimated the time it will take to build, t_i, and a "value-decay" weight, w_i. The value of completing a module diminishes the longer it takes. Specifically, if a module i is completed at a total elapsed time T_i (the sum of the build times of all modules completed up to and including i), it incurs a weighted completion cost of T_i * w_i.

Your goal is to determine an order for building the modules that respects the dependencies and minimizes the total weighted completion cost, which is the sum of T_i * w_i over all N modules.

Input Format

The first line contains a single integer N, the number of modules.

The next N lines describe the modules. The i-th of these lines (for i from 1 to N) contains two space-separated integers: t_i and w_i.

The next N-1 lines describe the dependencies. Each line contains two space-separated integers u and v, indicating that module u is the parent of module v.

Output Format

Print a single integer: the minimum possible total weighted completion cost.


Constraints:
1 <= N <= 200,000

1 <= t_i, w_i <= 1000

The given dependencies form a valid tree rooted at module 1.

The total weighted completion cost may exceed a 32-bit integer, so use a 64-bit integer type (long long in C) for the result.


Example:
Sample Input:

5
10 20
8 16
5 15
4 4
12 6
1 2
1 3
2 4
2 5

Sample Output:

1135


Explanation:
NA


Public Test Cases:
#	Input	Expected Output
1	
4
10 5
5 10
2 20
8 4
1 2
2 3
3 4
640
2	
5
10 1
2 10
3 9
4 8
5 7
1 2
1 3
1 4
1 5
585
3	
6
1 10
1 50
1 20
1 40
1 30
1 60
1 2
1 3
2 4
3 5
5 6
820
