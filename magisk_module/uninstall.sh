#!/system/bin/sh
# Uninstall script for Zygisk module
# This script runs when the module is uninstalled

LOG_TAG="ZygiskImGui"
LOG_FILE="/data/local/tmp/zygisk_imgui.log"

echo "[$LOG_TAG] Uninstall script started" >> $LOG_FILE

# Clean up any files created by the module

exit 0
