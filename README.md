# Android-Emulator-Detection
POC Tool to detect if app is ran on an emulator

# Features
- [x] Detect Android Studio Emulator
- [x] Detect Any Gaming Emulator
- [x] List Detections

# How To Use

```Java
// Import the package
import com.reveny.emulatordetector.plugin.EmulatorDetection;

// Create a new EmulatorDetection object.
EmulatorDetection detection = new EmulatorDetection();

// Check whether is emulator or not
boolean status = detection.isDetected();    // True if running in emulator else false

// Get the detected result
String result = detection.getResult();   // Empty if status is false else gives all the detections
```

## Contact
For any questions, collaboration requests, or updates, feel free to reach out via:

Telegram Channel: [Join Channel](https://t.me/reveny1) <br>
Telegram Contact: [Contact Me](https://t.me/revenyy) <br>
Website: [My Website](https://reveny.me) <br>
Email: [contact@reveny.me](mailto:contact@reveny.me) <br>

## License
While this project is licensed under the GPLv3 License, 
I would appreciate it if you contacted me first for commercial use to support further development. 
See the [LICENSE](LICENSE) file for full details.

## Contribution
If you have any ideas or suggestions to improve this project, feel free to create a pull request or contact me directly.

# Preview
![image](https://github.com/reveny/Android-Emulator-Detection/blob/main/preview.png)
