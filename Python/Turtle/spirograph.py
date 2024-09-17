import turtle
import random

def get_random_colour():
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    random_colour = (r, g, b)
    return random_colour

tim = turtle.Turtle()

tim.shape("turtle")
tim.color("black")
turtle.colormode(255)
tim.speed("fastest")

def draw_spirograph(size_of_the_gap):
    for _ in range(int(360 / size_of_the_gap)):
        colour = get_random_colour()
        tim.pen(pencolor=colour, pensize=1)
        tim.circle(100)
        tim.setheading(tim.heading() + size_of_the_gap)

draw_spirograph(5)

screen = turtle.Screen()
screen.exitonclick()