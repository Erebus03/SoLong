#!/bin/bash

# Check if a commit message is provided
if [ -z "$1" ]; then
  echo "Error: Please provide a commit message."
  echo "Usage: ./sync.sh \"Your commit message\""
  exit 1
fi

# Assign the commit message
commit_message="$1"

# Syncing steps
git add .
git commit -m "$commit_message"
git pull origin main --rebase
git push origin main

echo "Repository synced successfully!"
