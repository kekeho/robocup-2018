import cv2
from orange_mask import orange_detect
from picamera import PiCamera
from picamera.array import PiRGBArray


def track(frame):
    img, contours, hie = cv2.findContours(
        frame, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    max_area = -1
    max_area_id = 0

    if len(contours) == 0:
        return 0, 0

    for i in range(0, len(contours)):
        area = cv2.contourArea(contours[i])
        if max_area < area:
            max_area = area
            max_area_id = i

    moment = cv2.moments(contours[max_area_id])

    if moment['m00'] != 0:
        x = int(moment['m10'] / moment['m00'])
        y = int(moment['m01'] / moment['m00'])
    else:
        x = 0
        y = 0

    return x, y


def main():
    camera = PiCamera()
    camera.resolution = (1280, 720)
    camera.framerate = 32
    raw_cap = PiRGBArray(camera, size=(1280, 720))

    for frame_array in camera.capture_continuous(raw_cap, format='bgr', use_video_port=True):
        frame = frame_array.array
        # オレンジを検出 オレンジにマスク
        mask = orange_detect(frame)
        # オレンジのトラッキング
        point = track(mask)
        cv2.line(mask, (point[0] - 20, point[1]),
                 (point[0] + 20, point[1]), (0, 0, 255), 5)  # マーカー横線
        cv2.line(mask, (point[0], point[1] - 20),
                 (point[0], point[1] + 20), (0, 0, 255), 5)  # マーカー縦線
        # 結果表示
        cv2.imshow("Frame", frame)
        cv2.imshow("Orange", mask)

        # qキーが押されたら途中終了
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
