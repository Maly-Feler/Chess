import websocket
import json
import time

ws = websocket.create_connection(
    "ws://localhost:8080"
)

message = {
    "type": "Command",
    "payload": "click 1 1"
}

ws.send(json.dumps(message))

message = {
    "type": "Command",
    "payload": "click 3 1"
}

ws.send(json.dumps(message))

message = {
    "type": "Command",
    "payload": "wait 5000"
}

# time.sleep(5000)

ws.send(json.dumps(message))

message = {
    "type": "Command",
    "payload": "print board"
}

ws.send(json.dumps(message))

print("sent")

ws.close()