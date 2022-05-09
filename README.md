# NFL-Project
In this project, I use Python and C++. 
The Python code uses beatiful soup's lxml parser to web scrape data regarding winners of NFL games, and which teams were home and away.
The C++ code then uses the data gathered from the Python code, and runs it through an algorithm to determine who will win a certain matchup.

Currently, you have to run the Python code first and then run the C++ code. I am actively working on wrapping the C++ code in Python so that it can all be done in one command.

To run the code on Windows:
  ```
  Vegas.py
  g++ VegasAlgorithm.cpp
  ./a.out
  ```

To run the code on Linux:
```
Vegas.py
g++ VegasAlgorithm.cpp
./a.exe
```

You will then type in the matchup that you want results for using the following format:
"homeTeam awayTeam"

For now, you need to type in the team name exactly as in this list:

    '49ers'
    'Bears'
    'Bengals'
    'Bills'
    'Broncos'
    'Browns'
    'TB'
    'ARI'
    'Chargers'
    'Chiefs'
    'Colts'
    'WAS'
    'Cowboys'
    'Dolphins'
    'Eagles'
    'Falcons'
    'Giants'
    'Jaguars'
    'Jets'
    'Lions'
    'Packers'
    'Panthers'
    'Patriots'
    'Raiders'
    'Rams'
    'Ravens'
    'Saints'
    'Seahawks'
    'Steelers'
    'Texans'
    'Titans'
    'Vikings'
    
The future plans for this project:
- Wrap the C++ code in Python so that it can be run in one command
- Instead of picking a certain matchup, it will output the predicted winners of every matchup for the following week.
- Add in predicted scores of the games to be used for betting lines
- Modify the algorithm to be more accurate
