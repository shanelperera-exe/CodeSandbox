class User:
    def __init__(self, user_id, username):
        self.id = user_id
        self.username = username

user1 = User("001", "Shanel")

print(user1.username)

user2 = User("002", "Bob")

print(user1.id)

