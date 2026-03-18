#!/bin/sh

# Quick test script for the OTPA <-> ServerApp registration handshake.
# Usage:
#   ./run_registration_test.sh [port] [userID] [publicKey]
#
# Runs the server in the background, then runs the OTPA client against it,
# and finally terminates the server.

set -eu

PORT=${1:-55555}
USER_ID=${2:-1}
PUBLIC_KEY=${3:-0xDEADBEEF}

# Build needed binaries
gcc -Wall -Wextra -Wpedantic -std=c11 -o server server_main.c ServerApp.c common.c
gcc -Wall -Wextra -Wpedantic -std=c11 -o opta opta_main.c OPTA.c common.c

# Start the server
./server "$PORT" &
SERVER_PID=$!

cleanup() {
  kill -TERM "$SERVER_PID" 2>/dev/null || true
  wait "$SERVER_PID" 2>/dev/null || true
}
trap cleanup EXIT

# Give the server a moment to bind
sleep 0.1

# Run the OTPA client
./opta "$USER_ID" "$PUBLIC_KEY" "$PORT"

# Allow output to flush before the script exits
sleep 0.1
