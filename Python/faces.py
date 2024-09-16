def main():
    user_input = input("Enter a string: ")
    print(convert(user_input))

def convert(text):
    text = text.replace(":)", "🙂")
    text = text.replace(":(", "🙁")
    return text

if __name__ == "__main__":
    main()