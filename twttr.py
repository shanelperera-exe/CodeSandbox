vowels = ["A", "E", "I", "O", "U", "a", "e", "i", "o", "u"]

def main():
    text = input("Input: ").strip()
    print("Output: ", end="")

    for c in text:
        if c not in vowels:
            print(c, end="")
    
    print("")

if __name__ == "__main__":
    main()