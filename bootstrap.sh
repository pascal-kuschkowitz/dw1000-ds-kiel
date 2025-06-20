#!/bin/bash
set -e

REPO_URL="https://github.com/YOUR_USERNAME/YOUR_REPO.git"
TARGET_DIR="/home/pi/myapp"

echo "[*] Cloning or updating repo..."

if [ ! -d "$TARGET_DIR/.git" ]; then
  git clone "$REPO_URL" "$TARGET_DIR"
else
  git -C "$TARGET_DIR" pull
fi

echo "[*] Setting up auto-update cronjob..."
CRON_JOB="*/10 * * * * cd $TARGET_DIR && git pull origin main"
(crontab -l 2>/dev/null | grep -v "$REPO_URL" ; echo "$CRON_JOB") | crontab -
