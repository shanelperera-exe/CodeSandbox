import os
import requests
from dotenv import load_dotenv
import threading
from settings import animate_dots

load_dotenv()

class DataManager:
    def __init__(self):
        self._user = os.environ["SHEETY_FLIGHT_USERNAME"]
        self._password = os.environ["SHEETY_FLIGHT_PASSWORD"]
        self.prices_endpoint = os.environ["SHEETY_FLIGHT_PRICES_ENDPOINT"]
        self.users_endpoint = os.environ["SHEETY_FLIGHT_USERS_ENDPOINT"]
        self._authorization = (self._user, self._password)
        self.destination_data = {}
        self.customer_data = {}

    def get_destination_data(self):
        response = requests.get(url=self.prices_endpoint, auth=self._authorization)
        response.raise_for_status()
        data = response.json()
        self.destination_data = data["prices"]
        return self.destination_data

    def update_destination_codes(self):
        # Start the animation in a separate thread
        stop_event = threading.Event()
        animation_thread = threading.Thread(target=animate_dots, args=(stop_event, "Updating destination codes"))
        animation_thread.start()

        try:
            for city in self.destination_data:
                new_data = {
                    "price": {
                        "iataCode": city["iataCode"]
                    }
                }
                response = requests.put(
                    url=f"{self.prices_endpoint}/{city['id']}",
                    json=new_data,
                    auth=self._authorization
                )
                response.raise_for_status()
        finally:
            # Signal the animation thread to stop
            stop_event.set()
            animation_thread.join()  # Wait for the animation thread to finish


    def get_customer_emails(self):
        response = requests.get(url=self.users_endpoint, auth=self._authorization)
        response.raise_for_status()
        self.customer_data = response.json()["users"]
        return self.customer_data
