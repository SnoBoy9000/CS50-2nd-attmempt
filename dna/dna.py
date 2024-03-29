import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    # Read database file and DNA sequence file into variables
        # Need to open on same line instead of 2 so that everything else at correct indentation level
        # If anything else oustide with open, then files will be closed
    with open(sys.argv[1]) as csv_file, open(sys.argv[2]) as sequence:
        database = csv.DictReader(csv_file)
        # Use .read() instead of csv.reader() because want to open the sequence here,
        # but iterate over it later in the script
        # see https://stackoverflow.com/questions/50466932/difference-between-csv-reader-and-read-when-importing-csv-file
        dna_sequence = sequence.read()
    # Find longest match of each STR in DNA sequence
        for strs in dna_sequence:
            longest_sequence = longest_match(dna_sequence, strs)
        # Check database for matching profiles
        for person in database:
            for field in person:
                if field == "name":
                    continue
                if (person[field]) != longest_sequence[field]:
                    break
            else:
                print(person["name"])
                break
        else:
            print("No match")


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
