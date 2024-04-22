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

    def setupUi(self, mainWindow):
        super().setupUi(mainWindow)
        self.btnDecode.clicked.connect(self.btnDecode_clicked)

        self.txtReg0.setText( "0" )
        self.txtReg1.setText( "0x5" )
        self.txtReg2.setText( "0xc1" )
        self.txtReg3.setText( "0x13" )
        self.txtReg4.setText( "0xb" )
        self.txtReg5.setText( "0x60" )
        self.txtReg6.setText( "0xe0" )


    def decodeIER(self):
        IER = int( self.txtReg1.text(), 16)

        txt : str = ""

        if IER & 0x80 :
            txt = "bit7=1 CTS int enabled\n"
        else:
            txt = "bit7=0 CTS int not enabled\n"

        if IER & 0x40:
            txt += ( "bit6=1 RTS int enabled\n" )
        else:
            txt += ( "bit6=0 RTS int not enabled\n" )

        if IER & 0x20:
            txt += "bit5=1 XOFF int enabled\n"
        else:
            txt += "bit5=0 XOFF int not enabled\n"

        if IER & 0x10:
            txt += "bit4=1 Sleep Mode enabled\n"
        else:
            txt += "bit4=0 Sleep Mode not enabled\n"

        if IER & 0x8:
            txt += "bit3=1 Modem State Int\n"
        else:
            txt += "bit3=0 Modem State Int\n"

        if IER & 0x4:
            txt += "bit2=1 RxLine State Int\n"
        else:
            txt += "bit2=0 RxLine State Int\n"

        if IER & 0x2:
            txt += "bit1=1 Tx Empty Int\n"
        else:
            txt += "bit1=0 Tx Empty Int\n"

        if IER & 0x1:
            txt += "bit0=1 Rx Data Int\n"
        else:
            txt += "bit0=0 Rx Data Int\n"

        self.descReg1.setText(txt)


    def decodeLCR(self):
        LCR = int( self.txtReg3.text(), 16)

        txt : str = ""

        if LCR & 0x80 :
            txt = "bit7=1 Divisor enabled\n"
        else:
            txt = "bit7=0 数据寄存器被选择 Normal\n"

        if LCR & 0x40:
            txt += ( "bit6=1 SetTxBreak\n" )
        else:
            txt += ( "bit6=0 SetTxBreak\n" )

        if LCR & 0x20:
            txt += "bit5=1 Parity 强制奇偶校验位为0/1\n"
        else:
            txt += "bit5=0 Parity\n"

        if LCR & 0x10:
            txt += "bit4=1 EvenParity  1： 偶校验\n"
        else:
            txt += "bit4=0 EvenParity  0: 奇校验 \n"

        if LCR & 0x8:
            txt += "bit3=1 Parity Enable, 发送填充奇偶位，接收检查奇偶位\n"
        else:
            txt += "bit3=0 Parity Enable，无奇偶校验\n"

        txt += "bit2= " + str(LCR & 0x4) + ": stopBits  Length \n 映射: 0 -> 1; 1 -> 2 \n"

        txt += "wordLength: " + str(LCR & 0x03)
        txt += "\n  映射关系: 0 - 5;  1 - 6; 2 - 7; 3 - 8 bytes"

        self.descReg3.setText(txt)

    def decode_LSR(self):
        LSR = int( self.txtReg5.text(), 16 )
        txt = "读寄存为为LSR 功能，写为XFR\n 线路状态\n"

        if LSR & 1:
            txt += "bit0=1 Rx Data Ready\n"
        else:
            txt += "bit0=0 Rx Data Ready : False\n"

        if LSR & (1 << 1):
            txt += "bit1=1 Rx Data Overrun (接收FIFO满导致)\n"

        if LSR & (1 << 2):
            txt += "bit1=1 Rx Parity Error \n"

        if LSR & (1 << 3):
            txt += "bit1=1 Rx Framing Error \n"

        if LSR & (1 << 4):
            txt += "bit1=1 Rx Break \n"

        if LSR & (1 << 5):
            txt += "bit1=1 THR empty \n"

        if LSR & (1 << 6):
            txt += "bit1=1 TSR empty \n"

        if LSR & (1 << 7):
            txt += "bit1=1 Rx Fifo error (总标记）\n"

        self.descReg5.setText(txt)

    def decode_MSR(self):
        MSR = int( self.txtReg6.text(), 16 )
        txt = "modem 状态\n"

        if MSR & 1:
            txt += "bit0=1  CTS# 信号有变化\n"

        if MSR & (1 << 1):
            txt += "bit1=1  DSR# 信号有变化\n"

        if MSR & (1 << 2):
            txt += "bit2=1  RI# 信号有变化\n"

        if MSR & (1 << 3):
            txt += "bit3=1  CD# 信号有变化\n"

        if MSR & (1 << 4):
            txt += "bit4=1  CTS# 信号状态，1发送暂停 0恢复发送\n"

        if MSR & (1 << 5):
            txt += "bit5=1  DSR# 信号状态， Data Set Ready\n"

        if MSR & (1 << 6):
            txt += "bit5=1  RI# 信号状态\n"

        if MSR & (1 << 7):
            txt += "bit7=1  CD# 信号状态,载波检测？\n"

        self.descReg6.setText( txt )

    def decodeMCR(self):
        MCR = int( self.txtReg4.text(), 16 )
        txt = "modem 控制寄存器\n"

        if MCR & 1:
            txt += "bit0=1  设置DTR# 为0， Data Terminal Ready\n"
        else:
            txt += "bit0=0  设置DTR# 为1\n"

        if MCR & (1 << 1):
            txt += "bit1=1  设置RTS# 为0, 硬件流控，本机要发数据\n"
        else:
            txt += "bit1=0  设置RTS# 为1，硬件流控，本机不打算发数据\n"

        if MCR & (1 << 2):
            txt += "bit2=1  OP1#\n"
        else:
            txt += "bit2=0  OP1#\n"

        if MCR & (1 << 3):
            txt += "bit3=1  OP2#\n"
        else:
            txt += "bit3=0  OP2#\n"

        if MCR & (1 << 4):
            txt += "bit4=1  Internal LoopBack 模式\n"
        else:
            txt += "bit4=0  Internal LoopBack 模式 False\n"

        if MCR & (1 << 5):
            txt += "bit5=1  Enable open source interrupt output mode\n"
        else:
            txt += "bit5=0  Enable active or three-state interrupt output (default).\n"

        if MCR & (1 << 6):
            txt += "bit6=1  特殊功能 Enable infrared IrDA receive and transmit inputs/outputs.\n"
        else:
            txt += "bit6=0  Enable the standard modem receive and transmit input/output interface (default). .\n"

        if MCR & (1 << 7):
            txt += "bit6=1  = Divide by four.\n"
        else:
            txt += "bit6=0  = Divide by one \n"

        self.descReg4.setText( txt )

    def decodeISR(self):
        ISR = int( self.txtReg2.text(), 16 )
        txt = "中断寄存器，读清除\n"

        if ISR & 1:
            txt += "bit0=1 无中断\n"
        else:
            txt += "bit0=0 有中断pending"

        status = (ISR >> 1) & 0x3F
        if status == 3:
            txt += "LSR \n"
        elif status == 6:
            txt += "RXRDY: Receive Data Timeout \n"
        elif status == 2:
            txt += "RXRDY: Receive Data Ready \n"
        elif status == 1:
            txt += "TXRDY: Transmit Ready \n"
        elif status == 0:
            txt += "Modem status register \n"
        elif status == 0x10:
            txt += "Recived XOFF or special char \n"
        elif status == 0x20:
            txt += "CTS# RTS# changed status \n"
        else:
            txt += "未定义的中断状态 \n"

        self.descReg2.setText(txt)

    def btnDecode_clicked(self):
        reg_LCR = int( self.txtReg3.text(), 16)

        if reg_LCR & 0x80 == 0 :
            DLAB = 0
            self.descReg3.setText("bit7  0 : 数据寄存器被选择")
        else:
            DLAB = 1
            self.descReg3.setText( "bit7  1 : 比特率被选择 (==0xBF 增强功能)" )

        self.decodeLCR()

        if DLAB == 0:
            self.descReg0.setText("RHR: Receive Thresh Holder\n")
            self.descReg0.setText("写寄存器则设置THR: Transmit Thresh Holder\n" )

            self.descReg1.setText( "中断使能\n" )
            self.decodeIER()
            self.decode_LSR()
            self.decode_MSR()
            self.decodeMCR()
            self.decodeISR()

        else:
            self.descReg0.setText("DLL: divisor 波特率除法因子的低位")
            self.descReg1.setText("DLL: divisor 波特率除法因子的高位" )

        pass

