import csv
import sys

def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read content of csv file into a list 
    with open(sys.argv[1], "r") as datafile:
        reader = csv.reader(datafile)
        header = datafile.readline().strip().split(",")
        
        persons = [] 
        for person in reader:
            persons.append(person)
    
    print(persons)

    # Read DNA sequence
    with open(sys.argv[2], "r") as sequencefile:
        sequence = sequencefile.readline()
    
    print(header)
    print(sequence)

    srts = header[1:]

    srt_counts = []
    for srt in srts:
        print(srt)
        count = get_longest_run(sequence, srt)
        srt_counts.append(count)

    srt_counts = [4, 1, 5]
    print(srt_counts)
    match = False
    i = 0
    while match == False and i < len(persons):
        person = persons[i]
        print(person[0])

        person_srt_counts = [ int(count) for count in  person[1:]]
        print(person_srt_counts)
        if person_srt_counts == srt_counts:
            match = True
            print(person[0])
        i += 1
    
    if not match:
        print("No match")
        


# Return the maximum number of times that SRT repeats in sequence
def get_longest_run(sequence, srt):
    max = 0
    print(srt)

    srtlen = (len(srt))
    print(srtlen)

    for i in range(len(sequence) - srtlen):
        print("i: " + str(i))
        repeats = get_num_repeats(sequence, srt, i)
        if max < repeats:
            max = repeats

    return max

# Return the number of times srt repeats in sequence starting from index idx 
def get_num_repeats(sequence, srt, idx):
    repeated = True
    count = 0

    while repeated:

        sub_sequence_idx = idx + (len(srt) * (count + 1))
        sub_sequence = sequence[idx:sub_sequence_idx]
        repeated_srt = srt * (count + 1)

        print("sub_sequence_idx: " + str(sub_sequence_idx))
        print(f"sub_sequence: {sub_sequence}")
        print(f"repeated_srt: {repeated_srt}")

        if sub_sequence == repeated_srt:
            count += 1
            print(sequence[idx:idx + (len(srt) * count + 1)])
            print('     MATCH')
            print("count: " + str(count))
        else:
            repeated = False


    return count


if __name__ == "__main__":
    main()
