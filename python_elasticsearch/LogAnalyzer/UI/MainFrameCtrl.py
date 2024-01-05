# -*- coding: utf-8 -*-
import elasticsearch.helpers

from UI.MainFrame import Ui_MainWindow
from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow, QFileDialog
from elasticsearch import Elasticsearch
from datetime import datetime
import json
import sys
import os


def generate_actions(did: str, filename: str):
    app = filename[filename.rfind('/'):]
    with open(filename, "r", encoding='utf-8', errors="surrogateescape") as f:
        lines = f.readlines()
        for line in lines:
            doc = {
                "app": app,
                "did": did,
                "timestamp": datetime.now().strftime('%Y-%m-%dT%H:%M:%SZ'),
                "content": line
            }
            yield doc


class MainFrameCtrl(Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.log_root = ''
        self.log_files = []
        self.es_client = None

    def setupUi(self, mainWindow):
        super().setupUi(mainWindow)
        self.pushButton.clicked.connect(self.select_dir_btn_clicked)
        self.btnUploadEs.clicked.connect(self.upload_es_btn_clicked)

    def select_dir_btn_clicked(self):
        directory = QFileDialog.getExistingDirectory(None, '选择目录')
        print(directory)  # 这里获取用户选择的目录地址
        self.lineEdit.setText(directory)

        for root, dirs, files in os.walk(directory, topdown=False):
            self.log_root = root
            for file in files:
                # self.log_files.append(os.path.join(root, file))
                self.log_files.append(file)
                # if file.find(".log") > 0:
                #     self.log_files.append(os.path.join(root, file))
            break

        print(self.log_files)

    # 整个日志文件作为一个ES document
    def upload_one_log_file(self, did: str, filename: str):
        self.txtLog.append("处理文件:" + filename)

        if self.es_client is None:
            self.txtLog.append("连接ES服务器")
            self.es_client = Elasticsearch(hosts=self.txtServer.text())

        content = ''
        with open(filename, "r", encoding='utf-8', errors="surrogateescape") as f:
            content = f.read()

        app = filename[filename.rfind('/'):]

        # did, timestamp, content, app
        doc = {
            "app": app,
            "did": did,
            "timestamp": datetime.now().strftime('%Y-%m-%dT%H:%M:%SZ'),
            "content": content
        }

        self.txtLog.append("ES请求内容: " + str(len(json.dumps(doc))) + "\n 结果:")

        res = self.es_client.index(index="ld_dev_logs", body=json.dumps(doc))

        self.txtLog.append(str(res))

    # 日志里面的每条记录作为一个document
    def upload_one_log_file_v2(self, did: str, filename: str):
        self.txtLog.append("处理文件:" + filename)

        if self.es_client is None:
            self.txtLog.append("连接ES服务器")
            self.es_client = Elasticsearch(hosts=self.txtServer.text())

        if self.es_client is None:
            self.txtLog.append("ES 对象创建失败")
            return

        success_cnt = 0
        for ok, action in elasticsearch.helpers.streaming_bulk(client=self.es_client, index="ld_dev_logs",
                                                               raise_on_error=False,
                                                               actions=generate_actions(did, filename)):
            if ok:
                success_cnt += 1

        self.txtLog.append("成功添加记录数量：" + str(success_cnt) + "\n")

    # qt slot function.
    def upload_es_btn_clicked(self):
        for file in self.log_files:
            self.upload_one_log_file_v2("testdid2", os.path.join(self.log_root, file))
