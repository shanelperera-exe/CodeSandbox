import requests
import os
from twilio.rest import Client

API_KEY = os.environ["OWM_API_KEY"]
ACCOUNT_SID = "ACbbef7f076edb70b892fe25e14ee4ec6a"
AUTH_TOKEN = os.environ["TWILIO_AUTH_TOKEN"]

MY_LAT = 9.6615   # 7.082857
MY_LONG = 80.0255  # 79.868403

def main():
    weather_data = get_weather_data()
    will_rain(weather_data)

def get_weather_data():
    parameters = {
        "lat": MY_LAT,
        "lon": MY_LONG,
        "appid": API_KEY,
        "cnt": 4
    }

    response = requests.get(url="https://api.openweathermap.org/data/2.5/forecast", params=parameters)
    response.raise_for_status()
    weather_data = response.json()
    return weather_data

def will_rain(weather_data):
    rain = False
    for hour_data in weather_data["list"]:
        condition_code = hour_data["weather"][0]["id"]
        if int(condition_code) < 700:
            rain = True
    if rain:
        send_message()

def send_message():
    client = Client(ACCOUNT_SID, AUTH_TOKEN)

    # SMS
    message = client.messages.create(
        body="It's going to rain today.Remember to bring an umbrella.☔",
        from_="+1 775 458 9306",
        to="+94 77 637 9650",
    )

    # Whatsapp
    # message = client.messages.create(
    #   from_="whatsapp:+14155238886",
    #   body="It's going to rain today. Remember to bring an umbrella",
    #   to="whatsapp:+94702233551"
    # )

    print(message.status)

if __name__ == "__main__":
    main()