import cs50


dollars = -1.0
coins = 0

# Prompt for changed owed until non negative float is given
while dollars < 0:
    dollars = cs50.get_float("Changed owed: ")
    cents = round(dollars * 100)

while cents != 0:
    # Try to remove a quarter
    if cents >= 25:
        cents -= 25

    # Try to remove a dime
    elif cents >= 10:
        cents -= 10 

    # Try to remove a nicke
    elif cents >= 5:
        cents -= 5

    # Try to remove a penny
    elif cents >= 1:
        cents -= 1
    
    else:
        print("There is a bug with the logic")
    
    coins += 1

print(coins)

