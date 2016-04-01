VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Com_device 
   Caption         =   "Com_device"
   ClientHeight    =   3030
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2955
   LinkTopic       =   "Form1"
   ScaleHeight     =   3030
   ScaleWidth      =   2955
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer2 
      Interval        =   10
      Left            =   10
      Top             =   1560
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Ввод"
      Height          =   375
      Left            =   0
      TabIndex        =   3
      Top             =   2640
      Width           =   615
   End
   Begin VB.CommandButton Command1 
      Caption         =   "LED"
      Height          =   375
      Left            =   0
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   720
      Width           =   495
   End
   Begin VB.PictureBox Picture1 
      Height          =   3015
      Left            =   600
      ScaleHeight     =   2955
      ScaleWidth      =   2235
      TabIndex        =   0
      Top             =   0
      Width           =   2295
   End
   Begin VB.Timer Timer1 
      Interval        =   50
      Left            =   0
      Top             =   1200
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   0
      Top             =   2040
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   495
      Left            =   0
      TabIndex        =   1
      Top             =   120
      Width           =   495
   End
End
Attribute VB_Name = "Com_device"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
        MSComm1.CommPort = 1
        MSComm1.Settings = "1200,N,8,1"
        MSComm1.PortOpen = True
        MSComm1.RTSEnable = True
        MSComm1.DTREnable = True
        Command1.Tag = 0
            Timer2.Enabled = True
End Sub
Private Sub Timer1_Timer()
            MSComm1.DTREnable = True
        If MSComm1.CTSHolding = False Then  'опрос вывода CTS (Clear To Send )
            Label1.Caption = 0
            Label1.BackColor = vbBlue
            Picture1.Picture = LoadPicture(App.Path & "\2.gif")
           Else
            Label1.Caption = 1
            Label1.BackColor = vbRed
            Picture1.Picture = LoadPicture(App.Path & "\1.gif")
        End If
End Sub
Private Sub Command1_Click()
    If Command1.Tag = 0 Then
    MSComm1.RTSEnable = False   'включить светодиод
    Command1.Tag = 1
    Command1.BackColor = vbRed
    Else
    MSComm1.RTSEnable = True    'выключить светодиод
    Command1.Tag = 0
    Command1.BackColor = &H8000000F
    End If
End Sub

Private Sub Command2_Click()
On Error Resume Next
    Pr = "Введите число от 0 до 255"
'при Num={0,128(80),192(C0),224(E0),240(F0),248(F8),252(FC),254(FE),255(FF)} получим
'гладкий неизрезаный импульс. Макс.длительность при Num=0, минимальная при Num=255
    Num = InputBox(Pr, , Num)
End Sub

Private Sub Timer2_Timer()
  MSComm1.Output = Chr(Num)
End Sub
