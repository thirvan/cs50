import csv
import sys


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read content of csv file into a list 
    with open(sys.argv[1], "r") as datafile:
        reader = csv.reader(datafile)
        # Store the column header in a list
        header = datafile.readline().strip().split(",")

        # Store each person in a list
        persons = [] 
        for person in reader:
            persons.append(person)
    
    # Read DNA sequence
    with open(sys.argv[2], "r") as sequencefile:
        sequence = sequencefile.readline()
    
    # Create a list of the SRTs from the column headers
    srts = header[1:]

    # Store the longest run of each SRT from the DNA sequence in a list
    srt_counts = []
    for srt in srts:
        count = get_longest_run(sequence, srt)
        srt_counts.append(count)

    match = False
    i = 0
    # Compare the SRTs of each person with the ones from the sequence
    while match == False and i < len(persons):
        person = persons[i]
        # Convert the counts of each person to int
        person_srt_counts = [int(count) for count in person[1:]]
        if person_srt_counts == srt_counts:
            match = True
            print(person[0])

        i += 1
    
    if not match:
        print("No match")


def get_longest_run(sequence, srt):
    """ Return the maximum number of times that SRT repeats in sequence """
    max = 0

    srtlen = (len(srt))

    # Check the number of successive substrings for each position in sequence 
    # to get the max
    for i in range(len(sequence) - srtlen):
        repeats = get_num_repeats(sequence, srt, i)
        if max < repeats:
            max = repeats
    return max


def get_num_repeats(sequence, srt, idx):
    """ Return the number of times srt repeats in sequence starting from index 
        idx """
    repeated = True
    count = 0

    while repeated:
        # Compute the index of the end of the substring for current repeat count
        end_idx = idx + (len(srt) * (count + 1))
        sub_sequence = sequence[idx:end_idx]
        repeated_srt = srt * (count + 1)

        if sub_sequence == repeated_srt:
            count += 1
        else:
            repeated = False

    return count


if __name__ == "__main__":
    main()
