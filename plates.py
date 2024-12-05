def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    if check_pattern(s) and check_length(s) and check_pattern(s) and check_punctuations(s):
        return True
    elif s.isalpha() and check_length(s):
        return True
    else:
        return False

def check_start(s):
    return True if s[0:2].isalpha() else False
    
def check_length(s):
    return True if 2 <= len(s) <= 6 else False

def check_pattern(s):
    for c in s:
        if c.isdigit():
            index_of_digit = s.index(c)
            if s[index_of_digit:].isdigit() and int(c) != 0:
                return True
            else:
                return False

def check_punctuations(s):
    return True if s.isalnum() else False


if __name__ == "__main__":
    main()