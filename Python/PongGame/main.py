from turtle import Screen, Turtle
from paddle import Paddle
from ball import Ball
from scoreboard import Scoreboard
import time

def main():
    screen = Screen()
    screen.setup(width=800, height=600)
    screen.bgcolor("black")
    screen.title("Pong")
    screen.tracer(0)

    l_paddle = Paddle((-350, 0))
    r_paddle = Paddle((350, 0))
    ball = Ball()
    scoreboard = Scoreboard()

    screen.listen()
    screen.onkey(r_paddle.go_up, "Up")
    screen.onkey(r_paddle.go_down, "Down")
    screen.onkey(l_paddle.go_up, "w")
    screen.onkey(l_paddle.go_down, "s")

    game_is_on = True
    while game_is_on:
        time.sleep(ball.move_speed)
        draw_net()
        screen.update()
        ball.move()

        # Detect collision with the wall
        if ball.ycor() > 280 or ball.ycor() < -280:
            ball.bounce_y()

        # Detect collision with the paddles
        if ball.distance(r_paddle) < 50 and ball.xcor() > 320 or ball.distance(l_paddle) < 50 and ball.xcor() < -320:
            ball.bounce_x()

        # Detect if the right paddle misses the ball
        if ball.xcor() > 380:
            ball.reset_position()
            scoreboard.l_point()

        # Detect if the left paddle misses the ball
        if ball.xcor() < -380:
            ball.reset_position()
            scoreboard.r_point()

    screen.exitonclick()

def draw_net():
    net = Turtle()
    net.color("white")
    net.hideturtle()
    net.penup()
    net.goto(0, 300)
    net.setheading(270)
    net.pendown()
    net.pensize(5)
    for _ in range(15):
        net.forward(20)
        net.penup()
        net.forward(20)
        net.pendown()
    net.penup()

if __name__ == "__main__":
    main()