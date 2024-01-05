

##appMain.py单继承方法，能更好地进行界面与逻辑的分离
import sys
# import PyQt5.QtWidgets

from UI.MainFrameCtrl import MainFrameCtrl
from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = QMainWindow()

    ex = MainFrameCtrl()

    ex.setupUi(w)

    w.show()

    sys.exit(app.exec_())
