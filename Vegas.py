from cmath import pi
from bs4 import BeautifulSoup
import requests
import string
import pandas as pd
import numpy as np

#adding the names for the different teams
frame21 = pd.DataFrame(index = 
[
    '49ers',
    'Bears',
    'Bengals',
    'Bills',
    'Broncos',
    'Browns',
    'TB',
    'ARI',
    'Chargers',
    'Chiefs',
    'Colts',
    'WAS',
    'Cowboys',
    'Dolphins',
    'Eagles',
    'Falcons',
    'Giants',
    'Jaguars',
    'Jets',
    'Lions',
    'Packers',
    'Panthers',
    'Patriots',
    'Raiders',
    'Rams',
    'Ravens',
    'Saints',
    'Seahawks',
    'Steelers',
    'Texans',
    'Titans',
    'Vikings'
], 
columns = [])

#opens an excel spreadsheet that will be written to
f = open('VegasNumbers.csv', 'r+')
f.truncate(0) #removes all previous data in the spreadsheet

#for every nfl week we want to look at
for x in range (1,18):
    #goes to the usatoday website for every week of the specified season
    html_text = requests.get("https://sportsdata.usatoday.com/football/nfl/scores?type=Week+" + str(x) + "&season=2021-2022").text
    
    soup = BeautifulSoup(html_text, 'lxml') #gets the lxml parser from beautiful soup
    games = soup.find_all('ul', class_ = 'class-R0o3Uyv') #this is the list containing every game of the week

    for game in games: # for every game of that current week
        i = 0
        gameTeams = game.find_all('span', class_ = 'class-JBRBGd-') #gets the html code for every matchup
        for gameTeam in gameTeams:
            if i == 0:
                i += 1
                awayTeam = gameTeam.text.rstrip('0123456789-') #gets the away team's name
            else:
                homeTeam = gameTeam.text.rstrip('0123456789-') #gets the home team's name

        gameScores = game.find_all('span', class_ = 'class-sy7S-6k') #gets the score for both teams
        for gameScore in gameScores: 
            if i == 1: #if this is the first score in this span, then it is the score for the away team
                i += 1
                awayScore = gameScore.text
            else:
                homeScore = gameScore.text

        #adds the following columns for the away team (if the column already exists, then update the data for the row of the away team):
        frame21.loc[frame21.index.str.startswith(awayTeam), 'Week' + str(x)] = x #adds a column for every week
        frame21.loc[frame21.index.str.startswith(awayTeam), 'Home?' + str(x)] = 0 #adds a column for if they were home or away that week
        frame21.loc[frame21.index.str.startswith(awayTeam), 'PF' + str(x)] = awayScore #adds a column for the points scored
        frame21.loc[frame21.index.str.startswith(awayTeam), 'PA' + str(x)] = homeScore #adds a column for points allowed
        
        #adds the same columns for the home team (if the column already exists, then update the data for the row of the away team):
        frame21.loc[frame21.index.str.startswith(homeTeam), 'Week' + str(x)] = x
        frame21.loc[frame21.index.str.startswith(homeTeam), 'Home?' + str(x)] = 1
        frame21.loc[frame21.index.str.startswith(homeTeam), 'PF' + str(x)] = homeScore
        frame21.loc[frame21.index.str.startswith(homeTeam), 'PA' + str(x)] = awayScore
        
frame21.to_csv('VegasNumbers.csv') #moves all of this data to the excel spreadhseet
f.close()
