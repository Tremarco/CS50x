# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 10000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # with open so we don't need to worry about closing the file later
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        # for each line in the file
        for i in reader:
            # store the team name as the key
            team = i
            # and index into that key, cast to int and save that to appropriate key in our mini dict
            team['rating'] = int(team['rating'])
            # append the new mini dict item to our list, creating a list of tiny dicts, one for each team inside our teams list
            teams.append(team)

    counts = {}
    # simulate world cup N times
    for tournament in range(N):
        # store the champ as a variable to use for indexing into counts and incrementing
        campione = simulate_tournament(teams)
        # if the champ isn't already in the counts dict, they haven't won yet
        if campione not in counts:
            # so set them in there as 1
            counts[campione] = 1
        else:
            # otherwise they've already won one, so add one to existing count
            counts[campione] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # store the number of teams in the tournament in a variable (assuming it will be some power of 2)
    teams_left = len(teams)
    # as long as there is more than 1 team left
    while teams_left > 1:
        # reduce teams to be the winners returned from our call of simulate_round
        teams = simulate_round(teams)
        # recursively call simulate tournament again
        return simulate_tournament(teams)

    # when we have exited the while loop, only 1 team remains so return them as the winners
    return teams[0]["team"]


if __name__ == "__main__":
    main()