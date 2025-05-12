import cv2
import mediapipe as mp
import requests
import time

# Replace with your NodeMCU IP
NODEMCU_IP = "http://192.168.137.100" 

# MediaPipe hands setup
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(max_num_hands=1, min_detection_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

# Webcam setup
cap = cv2.VideoCapture(0)

# Store last gesture to avoid repeated commands
last_status = ""

def send_command(cmd):
    global last_status
    if cmd != last_status:  # Avoid repeated sending
        try:
            response = requests.get(f"{NODEMCU_IP}/{cmd}", timeout=1)
            print(f"Sent: {cmd} | Response: {response.text}")
            last_status = cmd
        except requests.exceptions.RequestException:
            print("Connection failed.")

while True:
    success, img = cap.read()
    if not success:
        break

    img = cv2.flip(img, 1)
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(img_rgb)

    if results.multi_hand_landmarks:
        hand = results.multi_hand_landmarks[0]
        mp_draw.draw_landmarks(img, hand, mp_hands.HAND_CONNECTIONS)

        lm = hand.landmark
        tip_ids = [4, 8, 12, 16, 20]  # Thumb to Pinky

        fingers = []

        # Thumb - check x direction for right hand
        fingers.append(1 if lm[tip_ids[0]].x < lm[tip_ids[0] - 1].x else 0)

        # Other fingers - check y direction
        for i in range(1, 5):
            fingers.append(1 if lm[tip_ids[i]].y < lm[tip_ids[i] - 2].y else 0)

        total_fingers = fingers.count(1)
        finger_count = sum(fingers[1:])  # Count fingers excluding thumb
        thumb_up = fingers[0] == 1

        if 1 <= finger_count <= 4:
            relay_number = finger_count
            action = "ON" if thumb_up else "OFF"
            command = f"{action}{relay_number}"
            send_command(command)

        # Draw status
        cv2.putText(img, f"Gesture: {''.join(map(str, fingers))}", (10, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Hand Relay Control", img)
    if cv2.waitKey(1) & 0xFF == 27:  # ESC key
        break

cap.release()
cv2.destroyAllWindows()
