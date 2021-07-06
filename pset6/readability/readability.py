import cs50
import re


def main():
    text = cs50.get_string("Text: ")
    num_letters = (count_letters(text))
    num_words = (count_words(text))
    num_sentences = (count_sentences(text))

    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # print(f"Letters: {num_letters}")
    # print(f"Words: {num_words}")
    # print(f"Sentences: {num_sentences}")
    # print(f"L {L}")
    # print(f"S {S}")
    # print(f"index {index}")

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")

    
def count_letters(text):
    count = 0
    for ch in text:
        if ch.isalpha():
            count += 1
    
    return count


def count_words(text):
    return len(text.split(" "))


def count_sentences(text):
    count = 0
    for ch in text:
        if ch == "." or ch == "!" or ch == "?":
            count += 1

    return count


main()