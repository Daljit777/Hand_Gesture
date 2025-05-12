<h1>Hand Gesture Controlled Smart Home Automation</h1>

**A new way to control your appliances: Hands-Free, Intuitive, and Smart.**

<h3>Overview</h3>

I'm excited to share my latest innovation in the **IoT domain** — a gesture-based home automation system that allows users to control electrical appliances (like a bulb) simply using their hand movements!
Imagine just raising your fingers or showing your thumb to control appliances — **no app, no touch, just pure intuitive control using computer vision.** That’s what this project is all about.

## How It Works
| Hand Gesture          | Action                  | Relay | Result    |
| --------------------- | ----------------------- | ----- | --------- |
| Thumb Up              | Turn OFF Appliance      | -     | Bulb OFF  |
| Index                 | Turn ON Relay 1         | 1     | Bulb 1 ON |
| Two Fingers           | Turn ON Relay 2         | 2     | Bulb 2 ON |
| Three Fingers         | Turn ON Relay 3         | 3     | Bulb 3 ON |
| Four Fingers          | Turn ON Relay 4         | 4     | Bulb 4 ON |
> Showing your **thumb** signals **OFF**, hiding it while showing other fingers triggers **ON**.

## Tech Stack
* **Python (OpenCV, MediaPipe)** – For gesture recognition using the webcam
* **ESP8266 NodeMCU** – To control relays based on commands
* **Relay Module** – To switch electrical appliances like bulbs
* **HTTP Requests** – Communicate between PC and NodeMCU

## Circuit Diagram
**Connection Details:**
* **NodeMCU ESP8266**
  * D1 → IN1 (Relay 1)
  * D2 → IN2 (Relay 2)
  * D3 → IN3 (Relay 3)
  * D4 → IN4 (Relay 4)
  * VIN & GND → Power Supply
    
* **Relay Module**
  * COM & NO → Connected to bulb
  * 5V & GND → Powered via NodeMCU
* **Bulb** – Connected in series with NO (Normally Open) and COM

> Make sure the **COM & NO** ports are used for correct switching logic: **Relay ON = Circuit Closed = Bulb ON**

## Installation

1. Install dependencies:

```bash
pip install opencv-python mediapipe requests
```

2. Upload code to NodeMCU via Arduino IDE.

3. Update your `NODEMCU_IP` in the Python script:

```python
NODEMCU_IP = "http://192.168.xxx.xxx"  # Replace with your IP
```

4. Run the Python code:

## Demo
> In the video, you'll see how I use my hand:
▶️ [Watch Demo Video]
https://youtu.be/pHN0Y94csPE?si=bEOZh8s0axcghbNp

* **Showing my thumb** = Turning OFF the appliance
* **Showing index finger** = Turning ON Relay 1 (Bulb ON)
* And so on up to 4 fingers

This demonstrates **intelligent and contactless control** over a real electrical appliance!

## Use Cases
* Smart Homes
* Elderly or disabled assistance
* Contactless control in hospitals or labs
* Educational IoT and AI Projects

## Future Scope
* Add voice + gesture combination
* Integrate with Google Assistant or Alexa
* Use IR sensors for additional interaction layers
* Train custom gestures with TensorFlow

## Acknowledgement
I explored AI tools and online resources to understand how gesture control systems work, and then I applied that knowledge to build my own. I focused more on understanding the logic and how everything connects rather than just memorizing syntax.
