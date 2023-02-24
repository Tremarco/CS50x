from cs50 import get_string


def main():

    # get input from user using cs50 get_string function as requested
    text = get_string("Text: ")

    # calculate and store letters, words and sentences variables by calling the appropriate functions
    letters = letter_count(text)
    words = word_count(text)
    sentences = sentence_count(text)

    # L and S variables for use in coleman-liau formula, and index number itself as the rounded result of said formula
    L = float(letters/words * 100)
    S = float(sentences/words * 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # conditional checks for edge cases
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def letter_count(text):
    # initialise counter variable
    counter = 0

    # loop through chars in text
    for char in text:
        # if the char is alphabetical character
        if char.isalpha():
            # increment counter
            counter += 1

    return counter


def word_count(text):
    # initialise counter variable
    counter = 0

    # loop through chars in text
    for char in text:
        # if the char is a space, increment counter
        if char.isspace():
            counter += 1

    # increment counter once more outside the loop to account for assumption text won't end with a space
    counter += 1
    return counter


def sentence_count(text):
    # initialise counter variable
    counter = 0

    # loop through chars in text, if it is one of '?' '!' or '.', increment counter as it counts as sentence ending for purposes of this assignment
    for char in text:
        if char == '?' or char == '!' or char == '.':
            counter += 1

    return counter


main()
