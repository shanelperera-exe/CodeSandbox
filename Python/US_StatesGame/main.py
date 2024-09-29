import turtle
import pandas

def main():
    screen = setup_screen()
    
    data = pandas.read_csv("50_states.csv")
    all_states = data["state"].to_list()
    guessed_states = []

    while len(guessed_states) < 50:
        answer_state = screen.textinput(title=f"{len(guessed_states)}/50 States Correct", prompt="Enter a state: (or enter 'Exit' to exit the game.)").title().strip()
        if answer_state == "Exit":
            write_missing_states(all_states, guessed_states)
            break
        if (answer_state in all_states) and (answer_state not in guessed_states):
            guessed_states.append(answer_state)
            write_states_on_map(data, answer_state)


    screen.exitonclick()

def setup_screen():
    screen = turtle.Screen()
    screen.setup(width=730, height=496)
    screen.title("U.S. States Game")
    image = "blank_states_img.gif"
    screen.addshape(image)
    turtle.shape(image)
    return screen
    
def write_states_on_map(data, answer_state):
    t = turtle.Turtle()
    t.hideturtle()
    t.penup()
    state_data = data[data["state"] == answer_state]
    t.goto(x=state_data["x"].item(), y=state_data["y"].item())
    t.write(state_data["state"].item(), align='center', font=('Courier', 8, 'bold'))

def write_missing_states(all_states, guessed_states):
    missing_states = [state for state in all_states if state not in guessed_states]
    new_data = pandas.DataFrame(missing_states)
    new_data.to_csv("states_to_learn.csv")


if __name__ == "__main__":
    main()