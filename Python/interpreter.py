def main():
    formatted_expression = input("Expression: ").strip().split(" ")
    x = int(formatted_expression[0])
    y = formatted_expression[1]
    z = int(formatted_expression[2])
    answer = float(calculate(x, y, z))
    print(f"{answer:.1f}")

def calculate(x, y, z):
    if y == "+":
        ans = x + z
    elif y == "-":
        ans = x - z
    elif y == "*":
        ans = x * z
    elif y == "/":
        ans = x / z
    else:
        print("Invalid Operator.")
    return ans

if __name__ == "__main__":
    main()