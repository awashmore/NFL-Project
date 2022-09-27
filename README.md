# NFL-Project

## 2022-23 Season Accuracy
30/48 - 62.5%

### Week 1 Accuracy
10/16 - 62.5%
### Week 2 Accuracy
12/16 - 75%
### Week 3 Accuracy
8/16 - 50%

## About this project
In this project, I use Python and C++. 
The Python code uses beautiful soup's lxml parser to web scrape data regarding winners of NFL games, and which teams were home and away.
The C++ code then uses the data gathered from the Python code, and runs it through an algorithm to determine who will win every matchup of the current week.

To run the code on Windows:
  ```
  Vegas.py
  g++ VegasAlgorithm.cpp
  ./a.exe
  ```

To run the code on Linux:
```
Vegas.py
g++ VegasAlgorithm.cpp
./a.out
```
    
The future plans for this project:
- Wrap the C++ code in Python so that it can be run in one command
- Add in predicted scores of the games to be used for betting lines
- Modify the algorithm to be more accurate
