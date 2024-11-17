from tkinter import *

MILES_TO_KM_RATIO = 1.60934

def main():
    window = Tk()
    window.title("Miles to Km Converter")
    window.minsize(width=300, height=100)
    window.config(padx=20, pady=20)

    miles_input = Entry(width=10)
    miles_input.grid(column=1, row=0)

    miles_label = Label(text="Miles")
    miles_label.grid(column=2, row=0)

    is_equal_label = Label(text="is equal to")
    is_equal_label.grid(column=0, row=1)

    km_result_label = Label(text="0")
    km_result_label.grid(column=1, row=1)

    km_label = Label(text="Km")
    km_label.grid(column=2, row=1)

    calc_button = Button(text="Calculate", command=lambda: miles_to_km(miles_input, km_result_label))
    calc_button.grid(column=1, row=2)

    window.mainloop()

def miles_to_km(miles_input, km_result_label):
    miles = float(miles_input.get())
    km = miles * MILES_TO_KM_RATIO
    km_result_label.config(text=f"{km}")

if __name__ == "__main__":
    main()