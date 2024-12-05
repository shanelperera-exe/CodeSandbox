def main():
    time = input("What time is it?: ").strip()
    time_in_hours = convert(time)
    if 7 <= time_in_hours <= 8:
        print("breakfast time")
    elif 12 <= time_in_hours <= 13:
        print("lunch time")
    elif 18 <= time_in_hours <= 19:
        print("dinner time")

def convert(time):
    hours, minutes = time.split(":")
    hours = int(hours)
    minutes = int(minutes)
    if 0 <= hours <= 24 and 0 <= minutes < 60:
        return hours + minutes / 60
    else:
        return "Invalid time."

if __name__ == "__main__":
    main()