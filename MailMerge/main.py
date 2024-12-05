PLACEHOLDER = "[name]"

with open("./Input/Names/invited_names.txt") as names_file:
    names = names_file.readlines()

with open("./Input/Letters/starting_letter.txt") as base_later:
        letter_contents = base_later.read()
        for name in names:
            stripped_name = name.strip()
            new_letter = letter_contents.replace(PLACEHOLDER, stripped_name)
            with open(f"./Output/ReadyToSend/letter_for_{stripped_name}.docx", "w") as completed_letter:
                completed_letter.write(new_letter)


