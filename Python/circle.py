import math

def main():
    radius = get_radius()
    circumference = calc_circumference(radius)
    area = calc_area(radius)

    print(f"Circumference: {circumference:.2f} cm")
    print(f"Area: {area:.2f} cm²")


def get_radius():
        r = float(input("Enter the radius of the circle (cm): "))
        return r

def calc_circumference(r):
     c = 2 * math.pi * r
     return c

def calc_area(r):
     a = math.pi * pow(r,2)
     return a

if __name__ == "__main__":
    main()
