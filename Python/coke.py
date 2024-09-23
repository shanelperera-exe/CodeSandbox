coins = [5, 10, 25]

def main():
    is_amount_due = True
    coke_price = 50

    while is_amount_due:
        print(f"Amount Due: {coke_price}")
        coin = int(input("Insert Coin: "))

        if coin in coins:
            coke_price -= coin
        else:
            print("Invalid Coin.")
        
        if coke_price <= 0:
            is_amount_due = False
            coke_price *= -1
        
    print(f"Change Owed: {coke_price}")


if __name__ == "__main__":
    main()