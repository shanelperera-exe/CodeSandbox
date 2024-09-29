grocery_list = {}

def main():
    while True:
        try:
            item = input("").strip().lower()   
        except EOFError:
            break
        else:
            if item in grocery_list:
                grocery_list[item] += 1
            else:
                grocery_list[item] = 1

    print("")
    print_grocery_list()

def print_grocery_list():
    for item in sorted(grocery_list):
        print(f"{grocery_list[item]} {item.upper()}")


if __name__ == "__main__":
    main()    