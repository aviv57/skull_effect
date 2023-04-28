# Skull effect
 
Skull Effect is a project that demonstrates how to trigger rgb LED cathodes effects on an Arduino board using a remote server. The project consists of two directories, [skull_effect_loop](/skull_effect_loop) and [backend](/backend). 

## Requirements

To use this project, you need to have the following:

- An ESP8266 development board
- Python 3.9 or later
- Pip package manager

## Installation

1. Clone this repository to your local machine:
```
git clone https://github.com/aviv57/skull_effect.git
```
2. Navigate to the `backend` directory and install the required packages:
```
cd backend
pip install -r requirements.txt
```

## Usage

### skull_effect_loop

The `skull_effect_loop` directory contains the Arduino code that waits for an event from a remote server and starts LED effects when an event is received. To use this code, follow these steps:

1. Open the `skull_effect_loop.ino` file in the Arduino IDE.
2. Connect your Arduino board to your computer via USB.
3. Upload the code to the board.
4. Once the code is uploaded, open the serial monitor in the Arduino IDE to see the output.

### backend

The `backend` directory contains a mini server written using FastAPI. The server has two endpoints:

1. `/set_event`: Sets an event that the Arduino board will listen for.
2. `/wait_for_event`: This endpoint is used by the Arduino code to get notification as soon as the event is sent to the backend server.

To use the server, follow these steps:

1. Open a terminal window and navigate to the `backend` directory.
2. Run the server with the following command:
```
uvicorn main:app
```
3. Once the server is running, you can make requests to the two endpoints using a tool like cURL or Postman.


## Contributing

If you would like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your changes.
3. Make your changes and commit them with descriptive commit messages.
4. Push your changes to your fork.
5. Create a pull request.