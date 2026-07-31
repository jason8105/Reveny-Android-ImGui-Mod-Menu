#!/system/bin/sh
# Service script for Zygisk module
# This script runs when the service starts

LOG_TAG="ZygiskImGui"
LOG_FILE="/data/local/tmp/zygisk_imgui.log"

echo "[$LOG_TAG] Service script started" >> $LOG_FILE

# Add any service initialization commands here if needed

exit 0
