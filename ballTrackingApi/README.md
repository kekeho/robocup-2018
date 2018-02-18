# 2018 Robocup | Ball Tracking API 
Tracking ⚽ which colored orange

# Dependence
- opencv
- python3
- mjpg_streamer

# Usage
## 1. stream raspi camera 
```
cd mjpg_streamer/mjpg_streamer-experimental
./mjpg_streamer -o "./output_http.so -w ./www" -i "./input_raspicam.so -x 640 -y 380 -fps 30 -q 70"
```

## 2. launch tracking app