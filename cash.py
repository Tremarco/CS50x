from cs50 import get_float


def main():
    # use get float from cs50 library as requested in specs
    n = get_float("Enter change owed: ")
    while n < 0:
        n = get_float("Enter change owed: ")
    # convert 0.XX format into cents by multiplying by 100 then casting to int
    total = int(n * 100)
    # initialise counter for number of coins needed
    coins = 0

    # run while loop as long as total change owed remains above 0
    while total > 0:
        # if changed owed is above 25
        if total >= 25:
            # ammend coins counter by floor division of 25
            coins += total // 25
            # set total to be the remainder
            total = total % 25
        # same logic for both dimes and nickels
        elif total >= 10:
            coins += total // 10
            total = total % 10
        elif total >= 5:
            coins += total // 5
            total = total % 5
        # if this else block executes, there are 4 cents or less remaining change owed
        else:
            # simply add the remaining total to the number of coins and set total to 0, therefore breaking the loop
            coins += total
            total = 0
    # print total number of coins
    print(coins)


main()