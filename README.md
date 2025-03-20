# Introduction

This framework implements the mathematical framework presented in "A Compositional Framework for End-to-End Path Delay Calculation of Automotive Systems under Different Path Semantics" by Feiertag et al.

# Structure

The code is split into the include folder containing all the headers and the source folder containing the code that implements the functions defined in the headers. There are several components in there

### executable/
The source/executable/ subfolder contains the code that is used to build the 2 main executables: 1 executable for analyzing individual task instance sequences (individualPathAnalyzer) and 1 executable for a more high-level analysis using tasks with certain parameters (taskAnalyzer). In the case of taskAnalyzer, it will try to generate individual task instances based on the task parameters and will perform the same kind of E2E analysis that the individualPathAnalyzer would apply to a pre-defined task instance sequence. With the se Right now, two ways for reading and writing are supported: console-based and text-based. 

#### individualPathAnalyzer

Text based option supports a file that is formated as follows:
```
START <timed_path_name>
<t1_period>,<t1_wcet>,<t1_priority>,<t1_activation_time>
...
<tn_period>,<tn_wcet>,<tn_priority>,<tn_activation_time>
END <timed_path_name>
```
See example files as well

For example, input contained in example2.txt will produce the following results: <be>

```
Results

Number of analyzed paths: 5
Number of unreachable paths: 1

Unreachable paths:
E

Number of reachable paths: 4
Reachable paths:
A
B
C
D

Last-to-Last semantics:
  Path with maximum latency over all reachable paths: A
  Maximum latency over all reachable paths: 40

Last-to-First semantics:
  Path with maximum latency over all reachable paths: B
  Maximum latency over all reachable paths: 10

First-to-Last semantics:
  Maximum path delay: 80

First-to-First semantics:
  Maximum path delay: 50
```

### Analysis.h and Analysis.cpp

Contains definitions and functions that can be used to perform an end-to-end analysis on a set of timed paths. They allow performing the analysis according to different semantics and they essentially implement equations 10-17 in the paper

### MathFrameowk.h and MathFrameowk.cpp

Contains boolean predicates that determine reachability between task instances. They are essentially definitions of equations 3-8 in the paper

### TimedPath.h and TimedPath.cpp

Represent a task chain and allows simple manipulations and calculations on it, for example end-to-end calculation for a specific path, first task instance activation time etc.

### Task.h and Task.cpp

Contain data structures used to represnt tasks and task instances

## main_IndividualPath.cpp

Entry point of the program. Reads user input, performs the analysis, and logs the results. The analysis itself starts on line 57:

![image](https://github.com/user-attachments/assets/a6c05188-35ce-47c2-aa04-a5926c65f381)


## tests/

Contains test for the implementation

# Executable usage

Default build process produced an executable called ```individualPathAnalyzer``` and an executable ```taskAnalyzer``` <br>
```Usage: ./individualPathAnalyzer <reader_type> <logger_type>``` <br>
```Usage: ./taskAnalyzer <reader_type> <logger_type>``` <br>

```taskAnalyzer``` uses the taskExample1.txt and taskExample2.txt as examples
```individualPathAnalyzer``` uses the example1.txt and example2.txt as examples

Currently supported logger types:
- ```console```
- ```text```

Currently supported reader types:
- ```console```
- ```text```

If no arguments are provided, the program will default to ```console```
