# Android-Emulator-Detection
POC Tool to detect if app is ran on an emulator

[![Stars](https://img.shields.io/github/stars/reveny/Android-Emulator-Detection?label=Stars)](https://github.com/reveny)
[![Release](https://img.shields.io/github/v/release/reveny/Android-Emulator-Detection?label=Release&logo=github)](https://github.com/reveny/Android-Emulator-Detection/releases/latest)
[![Download](https://img.shields.io/github/downloads/reveny/Android-Emulator-Detection/total?label=Downloads&logo=github)](https://github.com/reveny/Android-Emulator-Detection/releases/)
[![Channel](https://img.shields.io/badge/Telegram-Channel-blue.svg?logo=telegram)](https://t.me/reveny1)
[![CI](https://github.com/reveny/Android-Emulator-Detection/actions/workflows/main.yml/badge.svg)](https://github.com/reveny/Android-Emulator-Detection/actions/workflows/main.yml)

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

## Contributions
Contributions are welcome to help improve this project! If you’re interested in adding features or enhancing functionality, feel free to submit a pull request or open an issue to discuss your ideas.

### To-Do List
- [ ] **Enhanced Emulator Detection**: Add more robust detection methods for various emulator environments, including less commonly used emulators.
- [ ] **Performance Optimizations**: Optimize the detection algorithms to minimize resource usage on the app.

If you’d like to contribute, please ensure that your code follows the project’s style.

## Preview
<img src="https://github.com/reveny/Android-Emulator-Detection/blob/main/preview.png" width="350">

## Changelog

### v1.5.0
- New Detections
- Updated UI
- Cleaned up old and inefficient code
- Changed versioning system

### v4
- Converted core features to library module for `.aar` release
- Changed versioning system
- Fixed issue #1
- **New Contributor**: @onedevapp

### v0.3
- Added detection by checking Native Bridge property

### v0.2
- Fixed various issues
- Added ARM Translation Detection

### v0.1
- Initial release with detection for Android Studio Emulator and gaming emulators (tested on LDPlayer)

