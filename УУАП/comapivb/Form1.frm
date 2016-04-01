VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "mscomm32.ocx"
Begin VB.Form Form1 
   BackColor       =   &H80000003&
   Caption         =   "УУАП тест v.1.01"
   ClientHeight    =   3240
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   6615
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   204
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3240
   ScaleWidth      =   6615
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Alignment       =   2  'Центровка
      Appearance      =   0  'Плоска
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   1560
      TabIndex        =   12
      Text            =   "12"
      Top             =   2760
      Width           =   375
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Отправить"
      Height          =   375
      Left            =   4440
      TabIndex        =   10
      Top             =   2280
      Width           =   1335
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   4800
      Top             =   2640
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.CheckBox Check2 
      Caption         =   "Бленкер 2"
      Height          =   255
      Left            =   2760
      TabIndex        =   9
      Top             =   2280
      Value           =   1  'Отмечено
      Width           =   1335
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Бленкер 1"
      Height          =   255
      Left            =   1080
      TabIndex        =   8
      Top             =   2280
      Value           =   1  'Отмечено
      Width           =   1335
   End
   Begin VB.HScrollBar HScroll4 
      Height          =   255
      Left            =   1080
      Max             =   255
      TabIndex        =   6
      Top             =   1200
      Value           =   60
      Width           =   4695
   End
   Begin VB.HScrollBar HScroll3 
      Height          =   255
      Left            =   1080
      Max             =   255
      TabIndex        =   2
      Top             =   600
      Value           =   60
      Width           =   4695
   End
   Begin VB.HScrollBar HScroll2 
      Height          =   255
      Left            =   1080
      Max             =   255
      TabIndex        =   1
      Top             =   1680
      Value           =   60
      Width           =   4695
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      Left            =   1080
      Max             =   255
      TabIndex        =   0
      Top             =   120
      Value           =   60
      Width           =   4695
   End
   Begin VB.Label Label9 
      BackColor       =   &H80000003&
      Caption         =   "Стрелка Пу-"
      Height          =   255
      Left            =   0
      TabIndex        =   16
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label Label8 
      BackColor       =   &H80000003&
      Caption         =   "Индекс Пу-"
      Height          =   255
      Left            =   0
      TabIndex        =   15
      Top             =   1200
      Width           =   1095
   End
   Begin VB.Label Label7 
      BackColor       =   &H80000003&
      Caption         =   "Стрелка a-"
      Height          =   255
      Left            =   0
      TabIndex        =   14
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label Label6 
      BackColor       =   &H80000003&
      Caption         =   "Индекс а-"
      Height          =   255
      Left            =   0
      TabIndex        =   13
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Центровка
      BackColor       =   &H80000003&
      Caption         =   "СOM"
      Height          =   255
      Left            =   1080
      TabIndex        =   11
      Top             =   2805
      Width           =   495
   End
   Begin VB.Label Label4 
      BackColor       =   &H80000003&
      Caption         =   "60"
      Height          =   255
      Left            =   6000
      TabIndex        =   7
      Top             =   1200
      Width           =   495
   End
   Begin VB.Label Label3 
      BackColor       =   &H80000003&
      Caption         =   "60"
      Height          =   255
      Left            =   6000
      TabIndex        =   5
      Top             =   600
      Width           =   495
   End
   Begin VB.Label Label2 
      BackColor       =   &H80000003&
      Caption         =   "60"
      Height          =   255
      Left            =   6000
      TabIndex        =   4
      Top             =   1680
      Width           =   495
   End
   Begin VB.Label Label1 
      BackColor       =   &H80000003&
      Caption         =   "60"
      Height          =   255
      Left            =   6000
      TabIndex        =   3
      Top             =   120
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'COMAPIvb v.1.01
'Electron18
'www.softelectro.ru
'06.04.2012
Option Explicit



Private Sub Check1_Click()
MSComm1.CommPort = Text1.Text
' 9600 baud, no parity, 8 data, and 1 stop bit.
MSComm1.Settings = "9600,n,8,1"
MSComm1.PortOpen = True
' Send the attention command to the modem.
MSComm1.Output = Chr(48) & Chr(6) & Chr(Check1 + 2 * Check2)

' Close the serial port.
MSComm1.PortOpen = False
End Sub

Private Sub Check2_Click()
MSComm1.CommPort = Text1.Text
' 9600 baud, no parity, 8 data, and 1 stop bit.
MSComm1.Settings = "9600,n,8,1"
MSComm1.PortOpen = True
' Send the attention command to the modem.
MSComm1.Output = Chr(48) & Chr(6) & Chr(Check1 + 2 * Check2)

' Close the serial port.
MSComm1.PortOpen = False
End Sub

Private Sub Command5_Click()
' Buffer to hold input string
Dim Instring As String
' Use COM1.
MSComm1.CommPort = Text1.Text
' 9600 baud, no parity, 8 data, and 1 stop bit.
MSComm1.Settings = "9600,n,8,1"
' Tell the control to read entire buffer when Input
' is used.
MSComm1.InputLen = 0
' Open the port.
MSComm1.PortOpen = True
' Send the attention command to the modem.
MSComm1.Output = Chr(48) & Chr(16) & Chr(HScroll1) & Chr(HScroll2) & Chr(HScroll3) & Chr(HScroll4)

' Close the serial port.
MSComm1.PortOpen = False
End Sub



Private Sub HScroll1_Change()
Label1.Caption = HScroll1
End Sub

Private Sub HScroll2_Change()
Label2.Caption = HScroll2
End Sub

Private Sub HScroll3_Change()
Label3.Caption = HScroll3
End Sub

Private Sub HScroll4_Change()
Label4.Caption = HScroll4
End Sub

Private Sub Label6_Click()

End Sub

Private Sub Text1_Change()
If Not IsNumeric(Text1.Text) Then Text1.Text = 12
End Sub
