def main():
    user_input = input("camelCase: ").strip()

    snakecase = ""
    for letter in user_input:
        if letter.isupper():
            snakecase += "_" + letter.lower()
        else:
            snakecase += letter
    
    print(f"snake_case: {snakecase}")

if __name__ == "__main__":
    main()