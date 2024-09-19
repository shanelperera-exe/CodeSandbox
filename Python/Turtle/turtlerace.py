from turtle import Turtle, Screen
import random

def main():
    is_race_on = False
    screen = Screen()
    screen.setup(width=500, height=400)
    user_bet = screen.textinput(title="Make your bet", prompt="Which turtle will win the race? Enter a colour: ")
    all_turtles = arrange_turtles()
    play_game(all_turtles, user_bet, is_race_on)

    screen.exitonclick()


def arrange_turtles():
    colours = ["red", "orange", "yellow", "green", "blue", "purple"]
    y_coordinate = -80

    all_turtles = []
    for turtle_index in range(0, 6):
        new_turtle = Turtle(shape="turtle")
        new_turtle.color(colours[turtle_index])
        new_turtle.penup()
        new_turtle.goto(x=-230, y=y_coordinate)
        y_coordinate += 30
        all_turtles.append(new_turtle)

    return all_turtles

def play_game(all_turtles, user_bet, is_race_on):
    if user_bet:
        is_race_on = True

    while is_race_on:

        for t in all_turtles:
            if t.xcor() > 230:
                is_race_on = False
                winning_color = t.pencolor()
                if winning_color == user_bet:
                    print(f"You've won! The {winning_color} turtle is the winner!")
                else:
                    print(f"You've lost! The {winning_color} turtle is the winner!")

            random_pace = random.randint(0, 10)
            t.forward(random_pace)


if __name__ == "__main__":
    main()