import sys
import time

def animate_dots(stop_event, message):
    print(f"{message}", end="", flush=True)
    while not stop_event.is_set():
        for dots in range(4):  # Animate 0 to 3 dots
            if stop_event.is_set():
                break
            sys.stdout.write(f"\r{message}" + "." * dots)
            sys.stdout.flush()
            time.sleep(0.5)
    sys.stdout.write(f"\r{message}... Done!\n")

def logo():
    logo = """            
            ___________
    =  = ==(___________) \033[1;34;40mFlight Deal Finder\033[0m
                \\_____\\___________________,-~~~~~~~`-.._
                /     o O o o o o O O o o o o o o O o  |\\_
                `~-.__        ___..----..                  )
                      `---~~\\___________/------------`````
                      =  ===(_________D"""
    print(logo)