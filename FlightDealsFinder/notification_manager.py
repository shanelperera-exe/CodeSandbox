import os
import smtplib
from twilio.rest import Client
from dotenv import load_dotenv

load_dotenv()

class NotificationManager:
    def __init__(self):
        # Retrieve environment variables only once
        self.smtp_address = os.environ["EMAIL_PROVIDER_SMTP_ADDRESS"]
        self.email = os.environ["TEST_EMAIL_ADDRESS"]
        self.email_password = os.environ["TEST_EMAIL_PASSWORD"]
        self.twilio_virtual_number = os.environ["TWILIO_PHONENUMBER"]
        self.twilio_verified_number_msg = os.environ["TEST_PHONENUMBER"]
        self.twilio_verified_number_w = os.environ["TWILIO_VERIFIED_NUMBER"]
        self.whatsapp_number = os.environ["TWILIO_WHATSAPP_NUMBER"]
        self.client = Client(os.environ["TWILIO_ACCOUNT_SID"], os.environ["TWILIO_AUTH_TOKEN"])

    def send_sms(self, message_body):
        """
        Sends an SMS message through the Twilio API.
        This function takes a message body as input and uses the Twilio API to send an SMS from
        a predefined virtual number (provided by Twilio) to your own "verified" number.
        It logs the unique SID (Session ID) of the message, which can be used to
        verify that the message was sent successfully.

        Parameters:
        message_body (str): The text content of the SMS message to be sent.

        Returns:
        None

        Notes:
        - Ensure that `TWILIO_VIRTUAL_NUMBER` and `TWILIO_VERIFIED_NUMBER` are correctly set up in
        your environment (.env file) and correspond with numbers registered and verified in your
        Twilio account.
        - The Twilio client (`self.client`) should be initialized and authenticated with your
        Twilio account credentials prior to using this function when the Notification Manager gets
        initialized.
        """
        message = self.client.messages.create(
                from_=self.twilio_virtual_number,
                body=message_body,
                to=self.twilio_verified_number_msg
            )
        # Prints if successfully sent.
        print(message.sid)

        # Is SMS not working for you or prefer whatsapp? Connect to the WhatsApp Sandbox!
        # https://console.twilio.com/us1/develop/sms/try-it-out/whatsapp-learn

    def send_whatsapp(self, message_body):
        message = self.client.messages.create(
            from_=f"whatsapp:{self.whatsapp_number}",
            body=message_body,
            to=f"whatsapp:{self.twilio_verified_number_w}"
        )
        print(message.sid)

    def send_emails(self, email_list, email_body):
        with smtplib.SMTP(self.smtp_address, 587) as self.connection:
            self.connection.starttls()
            self.connection.login(user=self.email, password=self.email_password)
            for email in email_list:
                self.connection.sendmail(
                    from_addr=self.email,
                    to_addrs=email,
                    msg=f"Subject:New Low Price Flight!\n\n{email_body}".encode('utf-8')
                )