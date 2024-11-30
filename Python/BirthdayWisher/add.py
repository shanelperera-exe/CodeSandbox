import csv

def main():
    print("*** Add a Birthday ***")
    print("-" * 22)
    data = get_data()
    store_data(data)

    while True:
        response = input("Do you want to add another birthday? (Y/N): ").lower()
        if response == "y":
            main()
        elif response == "n":
            exit()
        else:
            continue

def get_data():
    name = input("Enter name: ").strip().title()
    email = input("Enter email: ")
    while True:
        try:
            year = int(input("Enter birthday year: "))
            month = int(input("Enter birthday month: "))
            day = int(input("Enter birthday day: "))
            
            # Ensure all inputs are positive integers
            if year > 0 and month > 0 and day > 0:
                return (name, email, year, month, day)
            else:
                print("Year, month, and day must be positive integers.")
        except ValueError:
            print("Invalid input. Please enter numeric values for year, month, and day.")

def store_data(data):
    file_name = "birthdays.csv"
    try:
        with open(file_name, "a") as data_file:
            writer  = csv.writer(data_file)
            writer.writerow(data)
    except FileNotFoundError:
        print(f"Error! {file_name} not found.")
    else:
        print("Birthday stored successfuly.\n")

if __name__ == "__main__":
    main()