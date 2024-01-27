from UI.MainFrame import Ui_MainWindow
from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow, QFileDialog
from PyQt5 import QtCore,QtGui
from datetime import datetime
import json
import sys
import os

from UI import codeEditor
from UI.highlighter import pyHighlight

class MainFrameCtrl(Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.log_root = ''
        self.log_files = []
        self.lines = list()
        self.es_client = None

    def setupUi(self, mainWindow):
        super().setupUi(mainWindow)
        self.highlighter = pyHighlight.PythonHighlighter(self.plainTextEdit.document())

        self.menu_select_file.triggered.connect(self.menu_select_file_clicked)
        self.btnSearch.clicked.connect(self.btnSearch_clicked)
        self.btnSearchInFile.clicked.connect(self.btnSearchInFile_clicked)

        self.textBrowser.cursorPositionChanged.connect(self.search_result_pos_changed)

        self.txtDid.textChanged.connect(self.analyze_do)
        self.checkBox_ReadProp.stateChanged.connect(self.analyze_do)
        self.checkBox_bind.stateChanged.connect(self.analyze_do)
        self.checkBox_rpt.stateChanged.connect(self.analyze_do)

        # self.pushButton.clicked.connect(self.select_dir_btn_clicked)
        # self.btnUploadEs.clicked.connect(self.upload_es_btn_clicked)

    def menu_select_file_clicked(self):
        directory = QFileDialog.getExistingDirectory(None, '选择目录')
        print(directory)  # 这里获取用户选择的目录地址
        self.log_root = directory
        self.load_file('msg_dev')

    def btnSearch_clicked(self):
        r = QtCore.QRegExp(self.txtSearch.text().strip())

        flags = QtGui.QTextDocument.FindFlags()
        if self.checkBoxCap.isChecked():
            flags += QtGui.QTextDocument.FindCaseSensitively  # by default it is case insensitive

        if self.checkBoxWhole.isChecked():
            flags += QtGui.QTextDocument.FindWholeWords

        try:
            result = self.plainTextEdit.find(r, flags)
            if not result:
                self.plainTextEdit.moveCursor(QtGui.QTextCursor.Start)
                result = self.plainTextEdit.find(r, flags)
        except:
            self.statusbar.showMessage("查找完成")

        print(result)

    def btnSearchInFile_clicked(self):
        r = QtCore.QRegExp(self.txtSearch.text().strip())

        flags = QtGui.QTextDocument.FindFlags()
        if self.checkBoxCap.isChecked():
            flags |= QtGui.QTextDocument.FindCaseSensitively  # by default it is case insensitive

        if self.checkBoxWhole.isChecked():
            flags |= QtGui.QTextDocument.FindWholeWords

        self.textBrowser.setText("搜索结果\r\n")
        last_pos = 0
        current_pos = 0
        # self.plainTextEdit.moveCursor(QtGui.QTextCursor.Start)
        while True:
            cursor = self.plainTextEdit.document().find(r, position=last_pos, options=flags)
            if cursor:
                current_pos = cursor.position()
                if current_pos <= last_pos:
                    print("search reach end of file")
                    break

                self.textBrowser.append("block :" + str(cursor.blockNumber()) + ":")
                last_pos = current_pos
            else:
                break

    def jump_to_line(self, no: int):
        self.plainTextEdit.setFocus()
        cursor = QtGui.QTextCursor(self.plainTextEdit.document().findBlockByNumber(no))
        self.plainTextEdit.setTextCursor(cursor)

    def search_result_pos_changed(self):
        print("search_result_pos_changed")
        cursor = self.textBrowser.textCursor()
        current_line = cursor.blockNumber()
        block = self.textBrowser.document().findBlockByLineNumber(current_line)
        if block:
            s_text:str = block.text()
            lst = s_text.split(':')
            if len(lst) >= 2:
                original_line = lst[1]
                print(s_text + "   原文件block行:" + original_line)
                # jump to line
                self.jump_to_line(int(original_line))
        pass

    # 使用python的字符串搜索, 过滤好之后，将结果显示在原文档处；如果直接在界面上过滤，多次过滤，就没有之前的原始文本了.
    def analyze_do(self):
        pattern = r''
        if len(self.txtDid.text().strip()) > 0:
            pattern = pattern + ('|' if len(pattern) else '') + self.txtDid.text().strip()

        if self.checkBox_ReadProp.isChecked():
            

    def load_file(self, filename):
        filename = os.path.join(self.log_root, filename)
        with open(filename, "r", encoding='utf-8', errors="surrogateescape") as f:
            self.lines = f.readlines()

        self.log_content = ''.join(self.lines)
        self.plainTextEdit.setPlainText(self.log_content)

        print("load complete.")
