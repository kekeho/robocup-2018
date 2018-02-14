import cv2
from orange_mask import orange_detect


def track(frame):
    moment = cv2.moments(frame)
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

        # オレンジを検出 オレンジにマスク
        mask = orange_detect(frame)
        # オレンジのトラッキング
        point = track(mask)
        cv2.line(mask, (point[0]-20, point[1]), (point[0]+20, point[1]), (0,0,255), 5) #マーカー横線
        cv2.line(mask, (point[0], point[1]-20), (point[0], point[1]+20), (0,0,255), 5) #マーカー縦線
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