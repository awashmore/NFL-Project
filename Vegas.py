from cmath import pi
from bs4 import BeautifulSoup
import requests
import string
import pandas as pd
import numpy as np

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

f = open('VegasNumbers.csv', 'r+')
f.truncate(0)
f.close()

for x in range (1,19):
    html_text = requests.get("https://sportsdata.usatoday.com/football/nfl/scores?type=Week+" + str(x) + "&season=2021-2022").text
    
    soup = BeautifulSoup(html_text, 'lxml')
    games = soup.find_all('ul', class_ = 'class-R0o3Uyv')

    for game in games:
        i = 0
        gameTeams = game.find_all('span', class_ = 'class-JBRBGd-')
        for gameTeam in gameTeams:
            if i == 0:
                i += 1
                awayTeam = gameTeam.text.rstrip('0123456789-')
            else:
                homeTeam = gameTeam.text.rstrip('0123456789-')

        gameScores = game.find_all('span', class_ = 'class-sy7S-6k')
        for gameScore in gameScores:
            if i == 1:
                i += 1
                awayScore = gameScore.text
            else:
                homeScore = gameScore.text

        frame21.loc[frame21.index.str.startswith(awayTeam), 'Week' + str(x)] = x
        frame21.loc[frame21.index.str.startswith(awayTeam), 'Home?' + str(x)] = 0
        frame21.loc[frame21.index.str.startswith(awayTeam), 'PF' + str(x)] = awayScore
        frame21.loc[frame21.index.str.startswith(awayTeam), 'PA' + str(x)] = homeScore

        frame21.loc[frame21.index.str.startswith(homeTeam), 'Week' + str(x)] = x
        frame21.loc[frame21.index.str.startswith(homeTeam), 'Home?' + str(x)] = 1
        frame21.loc[frame21.index.str.startswith(homeTeam), 'PF' + str(x)] = homeScore
        frame21.loc[frame21.index.str.startswith(homeTeam), 'PA' + str(x)] = awayScore
        
frame21.to_csv('VegasNumbers.csv')
