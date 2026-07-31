#!/system/bin/sh
# Post-fs-data script for Zygisk module initialization
# This script runs after the filesystem is mounted

LOG_TAG="ZygiskImGui"
LOG_FILE="/data/local/tmp/zygisk_imgui.log"

echo "[$LOG_TAG] Post-fs-data script started" >> $LOG_FILE

# Add any initialization commands here if needed

exit 0
