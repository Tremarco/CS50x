def main():
    # call height function and store returned int in variable
    height = get_height()

    # iterate over each row in height
    for row in range(height):
        # print the empty spaces before the bricks, set end to "" to avoid unwanted \n
        print(" " * (height - (row + 1)), end="")
        # print the bricks themselves, adding one two row to account for row initially equalling 0 rather than 1
        print("#" * (row + 1), end="")
        # print the two const spaces in middle of row
        print("  ", end="")
        # print the bricks on the right hand side, this time leaving end as \n to allow cursor to move to newline in prep for next row
        print("#" * (row + 1))


def get_height():
    # infinite loop
    while True:
        try:
            # get input from user and cast to int
            n = int(input("Height: "))
            # if input is valid and in range
            if n > 0 and n < 9:
                # return n, breaking the loop and passing n back to main
                return n
            # otherwise, print error message and reprompt
            print("ERROR: please enter an integer between 1 and 8")
        # if input cannot be cast to int, anticipate ValueError, handle and reprompt
        except ValueError:
            print("ERROR: please enter an integer between 1 and 8")


main()