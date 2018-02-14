import cv2, matplotlib
import numpy as np
import matplotlib.pyplot as plt

def read_img(name_i):
    img = cv2.imread(name_i)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    return img
    
img = read_img('lena_std.tif')
plt.imshow(img)