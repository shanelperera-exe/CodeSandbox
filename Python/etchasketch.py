from turtle import Turtle, Screen

tim = Turtle()
screen = Screen()

def main():
    screen.listen()

    screen.onkey(key="w", fun=go_forwards)
    screen.onkey(key="s", fun=go_backwards)
    screen.onkey(key="a", fun=go_counter_clockwise)
    screen.onkey(key="d", fun=go_clockwise)
    screen.onkey(key="c", fun=clear_drawing)

    screen.exitonclick()

def go_forwards():
    tim.forward(10)

def go_backwards():
    tim.backward(10)

def go_counter_clockwise():
    new_heading = tim.heading() + 10
    tim.setheading(new_heading)

def go_clockwise():
    new_heading = tim.heading() - 10
    tim.setheading(new_heading)

def clear_drawing():
    tim.clear()
    tim.penup()
    tim.home()
    tim.pendown()

if __name__ == "__main__":
    main()