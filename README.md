# Android-Emulator-Detection
POC Tool to detect if app is ran on an emulator

# Features
- [x] Detect Android Studio Emulator
- [x] Detect Any Gaming Emulator
- [x] List Detections


<br>

# How To


```Java
//Import the package
package com.reveny.emulator.detection;

//Create a new EmulatorDetection object.
EmulatorDetection detection = new EmulatorDetection();

//Check whether is emulator or not
boolean status = detection.isDetected();    //True if running in emulator else false

//Get the detected result
String result = detection.getResult()   //Empty if status is false else gives all the detections
```
<br>

# Contact
Telegram Group: https://t.me/reveny1 <br>
Telegram Contact: https://t.me/revenyy

# Preview
![image](https://github.com/reveny/Android-Emulator-Detection/blob/main/image.png)
