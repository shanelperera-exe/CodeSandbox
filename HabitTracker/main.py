import requests
from datetime import datetime

PIXELA_ENDPOINT = "https://pixe.la/v1/users"
USERNAME = "shanelperera"
TOKEN = "R1DQ17TSKdwZ2drs86THOOb9bP0g"
GRAPH_ID = "graph1"

def main():
    print("""\n██╗  ██╗ █████╗ ██████╗ ██████╗ ██╗████████╗    ████████╗██████╗  █████╗  ██████╗██╗  ██╗███████╗██████╗ 
██║  ██║██╔══██╗██╔══██╗██╔══██╗██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗
███████║███████║██████╔╝██████╔╝██║   ██║          ██║   ██████╔╝███████║██║     █████╔╝ █████╗  ██████╔╝
██╔══██║██╔══██║██╔══██╗██╔══██╗██║   ██║          ██║   ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗
██║  ██║██║  ██║██████╔╝██████╔╝██║   ██║          ██║   ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗██║  ██║
╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═════╝ ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝""")
    print("-" * 105)
    print("\033[1;32;40mMotivation gets you started, Habit keeps you going!\033[0m\n")
    print("Welcome to Habit Tracker!\n")

    print("This application requires a Pixela account. More info:\033[1;34mhttps://pixe.la\033[0m")
    print("Don't have a Pixela account? \033[1;34m[C] Create Account!\033[0m\n")
    print("\033[1;31m[1]\033[0m Create a habbit")
    print("\033[1;31m[2]\033[0m Add data to a habit")
    print("\033[1;31m[3]\033[0m Update data of a habit")
    print("\033[1;31m[4]\033[0m Delete data from a habit")

    valid_options = ["1", "2", "3", "4", 'c']
    while True:
        user_input = input("\nSelect an option:").strip().lower()
        if user_input not in valid_options:
            print("Invalid input. Try again.")
            continue
        else:
            break


    match user_input:
        case 'c':
            create_account()
        case "1":
            pass

def create_account():
    user_params = {
        "token": TOKEN,
        "username": USERNAME,
        "agreeTermsOfService": "yes",
        "notMinor": "yes"
    }

    # Creating Pixela account
    response = requests.post(url=PIXELA_ENDPOINT, json=user_params)
    response.raise_for_status()
    print(response.text)

def create_habit():
    graph_endpoint = f"{PIXELA_ENDPOINT}/{USERNAME}/graphs"

    graph_config = {
        "id": GRAPH_ID,
        "name": "Cycling Graph",
        "unit": "Km",
        "type": "float",
        "color": "shibafu"
    }

    headers = {
        "X-USER-TOKEN": TOKEN
    }

    # Creating the graph
    response = requests.post(url=graph_endpoint, json=graph_config, headers=headers)
    response.raise_for_status()
    print(response.text)


# pixel_creation_endpoint = f"{graph_endpoint}/{GRAPH_ID}"
#
# today = datetime.now()
# formatted_date = today.strftime("%Y%m%d")
#
# # Get any date
# # today = datetime(year=2024, month=12, day=3)
#
# pixel_data = {
#     "date": formatted_date,
#     "quantity": "15.0"
# }
#
# # Add pixels to the graph
# # response = requests.post(url=pixel_creation_endpoint, json=pixel_data, headers=headers)
# # response.raise_for_status()
# # print(response.text)
#
# # Update Pixels
#
# update_pixel_endpoint = f"{pixel_creation_endpoint}/{formatted_date}"
#
# updated_pixel_data = {
#     "quantity": "12.0"
# }
#
# # response = requests.put(url=update_pixel_endpoint, json=updated_pixel_data, headers=headers)
# # response.raise_for_status()
# # print(response.text)
#
#
# # Delete pixels
#
# delete_pixel_endpoint = update_pixel_endpoint
#
# response = requests.delete(url=delete_pixel_endpoint, headers=headers)
# response.raise_for_status()
# print(response.text)

if __name__ == "__main__":
    main()