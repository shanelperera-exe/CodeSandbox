# Drawing a triangle, square, pentagon, hexagon, heptagon, octagon, nonagon, decagon using Turtle

from turtle import Turtle, Screen

shapes = [
    {"shape": "triangle", "sides": "3", "colour": "red"},
    {"shape": "square", "sides": "4", "colour": "gold1"},
    {"shape": "pentagon", "sides": "5", "colour": "green"},
    {"shape": "hexagon", "sides": "6", "colour": "blue"},
    {"shape": "heptagon", "sides": "7", "colour": "PaleVioletRed1"},
    {"shape": "octagon", "sides": "8", "colour": "purple"},
    {"shape": "nonagon", "sides": "9", "colour": "orange"},
    {"shape": "decagon", "sides": "10", "colour": "brown"},
]

tim = Turtle()
tim.shape("turtle")
tim.color("black")

for shape in shapes:
    colour = shape["colour"]
    sides = int(shape["sides"])
    angle = 360 / sides
    for _ in range(sides):
        tim.pen(pencolor=colour, pensize=2)
        tim.forward(100)
        tim.right(angle)

screen = Screen()
screen.exitonclick()