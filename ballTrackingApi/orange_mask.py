import cv2
import numpy as np


def orange_detect(img):
    """
    オレンジ色のものにマスクを掛ける。
    引数imgには動画の各フレームを入力
    """
    #MOG2による背景 ノイズ除去のため
    fgbg = cv2.createBackgroundSubtractorMOG2()
    fgmask = fgbg.apply(img)
    
    # HSV色空間に変換
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # 赤色のHSVの値域1
    hsv_min = np.array([15 / 2, 150, 50])  # opencvのHueはHue/2を指定する
    hsv_max = np.array([50 / 2, 255, 255])
    mask = cv2.inRange(hsv, hsv_min, hsv_max)
    
    mask = cv2.bitwise_and(mask, mask, mask=fgmask)
    return mask


def main():
    """
    モジュール単体で実行した場合。WEBカメラが起動してオレンジ色の物のみ表示する。
    """
    # カメラのキャプチャ
    cap = cv2.VideoCapture(0)

    while(cap.isOpened()):
        # フレームを取得
        ret, frame = cap.read()

        # オレンジを検出 オレンジにマスク
        mask = orange_detect(frame)
        # オレンジ以外をマスク。オレンジはそのままの色表示。
        without_orange_mask = cv2.bitwise_and(frame, frame, mask=mask)
        # 結果表示
        cv2.imshow("Frame", frame)
        cv2.imshow("Orange", without_orange_mask)

        # qキーが押されたら途中終了
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
