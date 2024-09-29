def main():
    x, y = get_fraction()
    fuel = calculate_fuel(x, y)
    print(fuel)

def get_fraction():
    while True:
        try:
            fraction = input("Fraction: ").strip()
            x, y = fraction.split("/")
            x = int(x)
            y = int(y)

            if y == 0:
                raise ZeroDivisionError
            if x > y:
                raise ValueError
        
        except ValueError:
            pass
        except ZeroDivisionError:
            pass
        else:
            return x, y


def calculate_fuel(x, y):
    percentage = (x/y) * 100
    percentage = round(percentage)

    if percentage <= 1:
        return "E"
    elif percentage >= 99:
        return "F"
    else:
        return f"{percentage}%"

if __name__ == "__main__":
    main()