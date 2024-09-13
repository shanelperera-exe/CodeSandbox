#!/bin/bash

# Captain Hook's Git Script

# Pirate greeting
echo "Ahoy, matey! Ready to set sail on the code seas? ⚓🏴‍☠️"

# Prompt for the commit message
echo "What be the message for this here commit?"
read commit_message

# Stage all changes
git add .

# Commit with the pirate-themed message
if [ -z "$commit_message" ]; then
  commit_message="Captain Hook: A treasure chest of changes! 🏴‍☠️"
fi

git commit -m "$commit_message"

# Push to the remote repository
echo "Hoist the sails! Pushing the code bounty to the remote repository..."
git push

# Success message
echo "Arrr, your code bounty be safely aboard the ship! 🏴‍☠️"

# Farewell message
echo "Captain Hook: May your code always find safe harbor. Until next time, matey! ⚓"
