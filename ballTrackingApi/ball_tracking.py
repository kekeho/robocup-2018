import numpy as np
import cv2
from orange_mask import orange_detect


def track(frame):
    mask = orange_detect(frame)
    moment = cv2.moments(mask)
    if moment['m00'] != 0:
        x = int(moment['m10'] / moment['m00'])
        y = int(moment['m01'] / moment['m00'])
    else:
        x = 0
        y = 0

    return x, y


def main():
    cap = cv2.VideoCapture(0)

    while(cap.isOpened()):
        # フレームを取得
        ret, frame = cap.read()
        point = track(frame)
        print("\r{x}, {y}".format(x=point[0], y=point[1]), end='')
        # オレンジを検出 オレンジにマスク
        mask = orange_detect(frame)
        # オレンジ以外をマスク。オレンジはそのままの色表示。
        without_orange_mask = cv2.bitwise_and(frame, frame, mask=mask)
        # 結果表示
        cv2.imshow("Frame", frame)
        cv2.imshow("Orange", mask)

        # qキーが押されたら途中終了
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
