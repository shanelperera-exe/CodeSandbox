##################### Automated Birthday Wisher Project ######################

import smtplib
from datetime import datetime
import pandas
from random import randint

PLACEHOLDER = "[NAME]"
MY_EMAIL = "gtest4py@gmail.com"
MY_PASSWORD = "wwhq svkw vjac qpgq"

def main():
    today = get_today_info()
    birthday = check_for_birthdays(today)
    email_body = generate_email_body(birthday)
    send_email(email_body, birthday)

def get_today_info():
    today = (datetime.now().month, datetime.now().day)
    return today

def check_for_birthdays(today):
    try:
        data = pandas.read_csv("birthdays.csv")
        birthdays_dict = {(data_row['month'], data_row['day']): data_row for (index,data_row) in data.iterrows()}
    except FileNotFoundError:
        exit("Error! 'Birthdays.csv' data file not found.")
    else:
        if today in birthdays_dict:
            return birthdays_dict[today]

def generate_email_body(birthday):
    random_letter_num = randint(1,3)
    try:
        with open(f"letter_templates/letter_{random_letter_num}.txt") as letter:
            letter_contents = letter.read()
    except FileNotFoundError:
        exit(f"Error! letter_{random_letter_num}.txt file not found.")
    else:
        new_message = letter_contents.replace(PLACEHOLDER, birthday["name"])
        return new_message

def send_email(body, birthday):
    recipient_address = birthday["email"]
    with smtplib.SMTP("smtp.gmail.com") as connection:
        connection.starttls()
        connection.login(user=MY_EMAIL, password=MY_PASSWORD)
        connection.sendmail(from_addr=MY_EMAIL, to_addrs=recipient_address, msg=f"Subject:Happy Birthday!\n\n{body}")
        print("Email sent successfully.")


if __name__ == "__main__":
    main()

