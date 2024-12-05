months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]


def main():
    while True:
        try:
            user_input = input("Date: ").strip()

            # Handling MM/DD/YYYY format
            if "/" in user_input:
                month, day, year = user_input.split("/")
                month = int(month)
                day = int(day)
                year = int(year)

            # Handling "Month Day, Year" format
            elif "," in user_input:
                month_day, year = user_input.split(", ")
                month_name, day = month_day.split(" ")
                
                # Find month number from the name
                if month_name in months:
                    month = months.index(month_name) + 1
                else:
                    raise ValueError("Invalid month name")
                
                day = int(day)
                year = int(year)

            else:
                raise ValueError("Invalid date format")

            # Check if the day and month are valid
            if month < 1 or month > 12 or day < 1 or day > 31:
                raise ValueError("Invalid day or month value")
            
            # Output the date in YYYY-MM-DD format
            print(f"{year}-{month:02}-{day:02}")
            break

        except ValueError:
            # Reprompt the user on error
            pass


if __name__ == "__main__":
    main()
