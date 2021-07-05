import cs50
import re


def main():
    # Prompt user to input a card number until and int is inputed
    number = cs50.get_int("Number: ")
    number = str(number)
    
    # If checksum is valid check for each card using regex
    if checksum(number) == 0:
        if re.search("^3(4|7)\d{13}$", number):
            print("AMEX")
        elif re.search("^5[1-5]\d{14}$", number):
            print("MASTERCARD")
        elif re.search("^4(\d{12}|\d{15})$", number):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
        

def checksum(number):
    sum1 = 0
    sum2 = 0

    # Multiply every other digit by 2, starting with the number’s second-to-last
    # digit, and then add those products’ digits together.
    for i in range(len(number) - 2, -1, -2):
        digit = number[i]
        product = int(digit) * 2
        for d in str(product):
            sum1 += int(d)
    
    for i in range(len(number) - 1, -1, -2):
        digit = number[i]
        sum2 += int(digit)

    # Add the sum to the sum of the digits that weren’t multiplied by 2.
    checksum = (sum1 + sum2) % 10
    return checksum


main()