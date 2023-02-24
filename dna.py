import csv
import sys


def main():

    # Check for command line usage
    argc = len(sys.argv)
    if argc != 3:
        print("Error: Incorrect number of command line arguments. USAGE: python dna.py CSV TXT")

    # Create list to store person dicts in
    persons = []

    # use with open so we don't need to worry about closing later
    with open(sys.argv[1], "r") as STRfile:
        # initialise reader
        reader = csv.DictReader(STRfile)
        # pull STR names from fieldnames, slicing from 1 to end to avoid persons name
        STRs = reader.fieldnames[1:]
        # for each line in CSV file
        for i in reader:
            # store the person's name as the key
            person = i

            # for each STR in the CSV file
            for STR in STRs:
                # save it into that person's dictionary
                person[STR] = int(person[STR])
            # append to our list of dictionaries
            persons.append(person)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as TXTfile:
        DNA = TXTfile.read()

    # create new dictionary for all STRs in the given CSV file, set all values to 0 for now
    STR_count = dict.fromkeys(STRs, 0)

    # go through each STR, calling the given helper function to set the value at given key index to be the longest match of that STR in the DNA sequence given
    for STR in STRs:
        STR_count[STR] = longest_match(DNA, STR)

    # Check database for matching profiles
    # counter variable to keep track of how many "misses" we have had
    miss_counter = 0

    # for each person in our list of person dicts
    for person in persons:
        # initialise counter variable to keep track of how many matches we have had
        match_counter = 0

        # for each STR that person has
        for STR in STRs:
            # if it matches exactly
            if person[STR] == STR_count[STR]:
                # increment match counter by 1
                match_counter += 1
        # if the match counter is the same as the number of STR sequences in the given CSV file, its a match
        if match_counter == len(STR_count):
            # print the name accordingly
            print(f"{person['name']}")
        # if for any reason the match counter is not the same, it isn't a match
        else:
            # append miss counter accordingly
            miss_counter += 1

    # if the miss counter variable is the same as the length of our persons list, then we had no matches despite successfully checking every person
    if miss_counter == len(persons):
        # print as much
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
