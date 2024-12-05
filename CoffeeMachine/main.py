from art import logo, text

MENU = {
    "espresso": {
        "ingredients": {
            "water": 50,
            "coffee": 18,
        },
        "cost": 1.5,
    },
    "latte": {
        "ingredients": {
            "water": 200,
            "milk": 150,
            "coffee": 24,
        },
        "cost": 2.5,
    },
    "cappuccino": {
        "ingredients": {
            "water": 250,
            "milk": 100,
            "coffee": 24,
        },
        "cost": 3.0,
    }
}

resources = {
    "water": 300,
    "milk": 200,
    "coffee": 100,
}

QUARTER = 0.25
DIME = 0.10
NICKEL = 0.05
PENNY = 0.01

def main():
    print(logo)
    print(text)
    money = 0
    machine_on = True
    while machine_on:
        user_choice = input("What would you like? (espresso/latte/cappuccino): ").lower()
        if user_choice in ["espresso", "latte", "cappuccino"]:
            if check_resource_sufficiency(user_choice):
                price = process_coins(user_choice)
                money = update_machine(user_choice, money, price)
                print(f"Here is your {user_choice} ☕︎Enjoy!")
                continue
        if user_choice == "report":
            report(money)
        elif user_choice == "off":
            machine_on = False
        elif user_choice not in ["espresso", "latte", "cappuccino", "report", "off"]:
            print("Invalid choice. Please enter an available drink.")

def check_resource_sufficiency(choice):
    ingredients = MENU[choice]['ingredients']
    insufficient_resources = []

    for item, amount in ingredients.items():
        if resources[item] < amount:
            insufficient_resources.append(item)

    if insufficient_resources:
        for resource in insufficient_resources:
            print(f"Sorry there is not enough {resource}.")
        return False
    return True

def process_coins(choice):
    price = MENU[choice]['cost']
    while True:
        print("Please insert coins.")
        try:
            quarters = int(input("How many quarters?: "))
            dimes = int(input("How many dimes?: "))
            nickels = int(input("How many nickels?: "))
            pennies = int(input("How many pennies?: "))

            total_value_of_coins = quarters * QUARTER + dimes * DIME + nickels * NICKEL + pennies * PENNY

            if total_value_of_coins >= price:
                change = total_value_of_coins - price
                print(f"Here is ${change:.2f} in change.")
                return price
            elif total_value_of_coins < price:
                print("Sorry that's not enough money. Money refunded.")
                continue
        except ValueError:
            print("Invalid input.")
            continue

def report(money):
    for item, remaining_amount in resources.items():
        print(f"{item.capitalize()}: {remaining_amount}")
    print(f"Money: ${money}")

def update_machine(choice, money, price):
    ingredients = MENU[choice]['ingredients']
    for item, amount_needed in ingredients.items():
        resources[item] -= amount_needed

    money += price
    return money

if __name__ == "__main__":
    main()

