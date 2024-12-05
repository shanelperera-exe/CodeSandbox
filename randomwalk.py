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
# pen_colours = ["red", "gold1", "green", "blue", "PaleVioletRed1", "purple", "orange", "brown"]
directions = [0, 90, 180, 270]

tim.speed("fast")

for _ in range(200):
    colour = get_random_colour()
    tim.pen(pencolor=colour, pensize=10)
    tim.forward(30)
    tim.setheading(random.choice(directions))

screen = turtle.Screen()
screen.exitonclick()

