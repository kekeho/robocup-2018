import sys
from PyQt5.QtWidgets import *

def main():
    app = QApplication(sys.argv)
    w = QWidget()
    w.resize(400,400)
    w.setWindowTitle('cacaca')
    w.show()
    sys.exit(app.exec_())
    
if __name__ == '__main__':
    main()