import pandas

data = pandas.read_csv("nato_phonetic_alphabet.csv")

#TODO 1. Create a dictionary in this format:
phonetic_dict = {row.letter:row.code for (index, row) in data.iterrows()}

word = input("Enter a word: ").upper().strip()

#TODO 2. Create a list of the phonetic code words from a word that the user inputs.
output_list = [phonetic_dict[letter] for letter in word]

for word in output_list:
    print(word, end=" ")
print("")

