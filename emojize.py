import emoji

def main():
    user_input = input("Input: ").strip()
    emojized_text = emoji.emojize(user_input, language='alias')
    print(emojized_text)

if __name__ == "__main__":
    main()