import datetime as dt
import random
import smtplib

MY_EMAIL = "gtest4py@gmail.com"
MY_PASSWORD = "wwhq svkw vjac qpgq"

def main():
    current = dt.datetime.now()
    day_of_week = current.weekday()

    if 0 <= day_of_week <= 4:
        random_quote = get_quote()
        send_email(random_quote)

def get_quote():
    try:
        with open("quotes.txt", "r") as data_file:
            quotes = data_file.readlines()
    except FileNotFoundError:
        print("Error! File not found.")
    else:
        return random.choice(quotes)

def send_email(quote):
    with smtplib.SMTP("smtp.gmail.com") as connection:
        connection.starttls()
        connection.login(user=MY_EMAIL, password=MY_PASSWORD)
        connection.sendmail(from_addr=MY_EMAIL, to_addrs="ytest4py@outlook.com", msg=f"Subject:Monday Motivation\n\n{quote}")

    print("Email sent successfully.")

if __name__ == "__main__":
    main()