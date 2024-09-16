from menu import Menu, MenuItem
from coffee_maker import CoffeeMaker
from money_machine import MoneyMachine

menu = Menu()
coffee_maker = CoffeeMaker()
money_machine = MoneyMachine()

def main():
    machine_on = True
    while machine_on:
        options = menu.get_items()
        choice = input(f"What would you like? ({options.removesuffix("/")}): ").lower().strip()
        if choice == "report":
            coffee_maker.report()
            money_machine.report()
        elif choice == "off":
            machine_on = False
        else:
            drink = menu.find_drink(choice)
            if coffee_maker.is_resource_sufficient(drink) and money_machine.make_payment(drink.cost):
                coffee_maker.make_coffee(drink)


if __name__ == "__main__":
    main()