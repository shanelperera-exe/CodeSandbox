import pandas

data = pandas.read_csv("nato_phonetic_alphabet.csv")

phonetic_dict = {row.letter:row.code for (index, row) in data.iterrows()}

# while True:
#     word = input("Enter a word: ").upper().strip()
#     try:
#         output_list = [phonetic_dict[letter] for letter in word]
#     except KeyError:
#         print("Sorry, only letters in alphabet please.")
#         continue
#     else:
#         break
#
# for word in output_list:
#     print(word, end=" ")
# print("")

def generate_phonetic():
    word = input("Enter a word: ").upper().strip()
    try:
        output_list = [phonetic_dict[letter] for letter in word]
    except KeyError:
        print("Sorry, only letters in alphabet please.")
        generate_phonetic()
    else:
        for word in output_list:
            print(word, end=" ")
        print("")

generate_phonetic()