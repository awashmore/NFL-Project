# NFL-Project
In this project, I use Python and C++. 
The Python code uses beautiful soup's lxml parser to web scrape data regarding winners of NFL games, and which teams were home and away.
The C++ code then uses the data gathered from the Python code, and runs it through an algorithm to determine who will win every matchup of the current week.

Currently, you have to run the Python code first and then run the C++ code. I am actively working on wrapping the C++ code in Python so that it can all be done in one command.

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
