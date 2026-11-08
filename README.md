# Obstacle Avoiding Robot

An Arduino UNO based obstacle avoiding robot, simulated in Proteus. An ultrasonic sensor measures the distance in front of the robot. If the path is clear the robot moves forward. If an obstacle is close, it stops, moves backward and turns right. The distance and the current action are shown on a 16x2 LCD.

**Course:** Microprocessor and Microcontroller Sessional (CSE 3212)
**University:** Jamalpur Science and Technology University (JSTU)
**Department:** Computer Science and Engineering

## Team

| Name | ID |
|---|---|
| Farjana Akter Mim | 23211102 |
| Pallobi Barmon | 22211122 |

## Components

| Component | Purpose |
|---|---|
| Arduino UNO (ATmega328P) | Main controller |
| Ultrasonic sensor (HC-SR04) | Measures distance to obstacles |
| L293D motor driver | Drives the two DC motors |
| 2 x DC motor | Left and right wheels |
| LCD 16x2 (LM016L) | Shows distance and status |
| 1k potentiometer | Used in simulation to change the sensor input |

**Software:** Arduino IDE, Proteus

## Pin Connections

| Arduino Pin | Connected To |
|---|---|
| D2, D3 | L293D IN1, IN2 (Left motor) |
| D4, D5 | L293D IN3, IN4 (Right motor) |
| D6 | Ultrasonic Trigger |
| D7 | Ultrasonic Echo |
| D13 | LCD RS |
| D12 | LCD E |
| D8 - D11 | LCD D4 - D7 |
| 5V / GND | Sensor, L293D (VS, VSS, EN1, EN2), LCD |

## How It Works

1. The Arduino sends a 10 microsecond pulse on the trigger pin.
2. The echo time is measured with `pulseIn()` and converted to distance:
   `distance = duration * 0.034 / 2` (cm). If no echo returns, the distance is set to 400 cm.
3. The distance is shown on the LCD.
4. Decision:
   - **Distance > 20 cm:** both motors rotate forward ("Moving Forward").
   - **Distance <= 20 cm:** the robot runs this sequence:
     1. Stop and show "Obstacle Found" (0.5 s)
     2. Move backward (0.5 s)
     3. Turn right: left motor forward, right motor backward (0.6 s)
     4. Stop briefly (0.2 s)
5. The loop repeats continuously.

## Simulation Results

Add your Proteus screenshots to an `images/` folder and update the file names below.

| State | Screenshot |
|---|---|
| System ready | `images/ready.png` |
| Distance 55 cm, Moving Forward | `images/forward.png` |
| Distance 10 cm, Obstacle Found | `images/obstacle.png` |
| Moving Backward | `images/backward.png` |
| Turning Right | `images/right.png` |

Example of embedding in this file:

```markdown
![Moving Forward](images/forward.png)
```

## How to Run the Simulation

1. Open the Arduino code in Arduino IDE.
2. Go to **Sketch > Export Compiled Binary** to generate the `.hex` file.
3. Open the Proteus project file.
4. Double-click the Arduino UNO, set **Program File** to the `.hex` file and click OK.
5. Press the **Play** button.
6. Change the potentiometer / sensor test input to simulate different distances and watch the LCD and motors.

## Limitations

- Only one front sensor, so it cannot detect obstacles at the sides or behind.
- It always backs up and turns right, even if the right side is blocked.
- No speed control. Motors run at full speed (PWM is not used on the enable pins).
- `delay()` blocks the code, so the robot senses nothing while backing up and turning.
- Tested only in Proteus simulation, not on real hardware.

## Future Scope

- Mount the sensor on a servo to scan left and right and choose the clearer path.
- Use PWM on the enable pins for smooth speed control and slowing down near obstacles.
- Add side ultrasonic and IR sensors for wider awareness.
- Add Bluetooth or Wi-Fi for manual override and phone monitoring.
- Build the real hardware, then add a camera and AI for path planning.

## Project Structure

Adjust to match your repository.

```
.
├── code/            # Arduino sketch (.ino)
├── proteus/         # Proteus project files
├── images/          # Simulation screenshots
├── presentation/    # Project slides
└── README.md
```
