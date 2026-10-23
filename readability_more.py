# Harvard CS50x - Week 6 - Problem Set 6 
# Readability (Python): https://cs50.harvard.edu/x/psets/6/readability/
# Python version of week 2 Readability


def main():
    text = input("Text: ")

    sum_words = get_sum_words(text)

    sum_letters = get_sum_letters(text)

    sum_sentences = get_sum_sentences(text)

    L = average_per_100(sum_letters, sum_words)

    S = average_per_100(sum_sentences, sum_words)

    # Text grade based on Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def get_sum_words(text):
    splited = text.split()
    return len(splited)


def get_sum_letters(text):
    count_letters = 0

    for i in text:
        if i.isalpha():
            count_letters += 1

    return count_letters


def get_sum_sentences(text):
    count_sentences = 0

    for i in text:
        if i in ".?!":
            count_sentences += 1

    return count_sentences


def average_per_100(a, b):
    average_per_100 = (a / b) * 100

    return average_per_100


main()
