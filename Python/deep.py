user_ans = input("What is the Answer to the Great Question of Life, the Universe, and Everything?: ").strip().replace('-', " ")
if user_ans == "42" or user_ans == "forty two":
    print("Yes")
else:
    print("No")
