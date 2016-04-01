VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H80000003&
   Caption         =   "COMAPIvb v.1.01"
   ClientHeight    =   2505
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11865
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   204
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   2505
   ScaleWidth      =   11865
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text2 
      Appearance      =   0  'Flat
      Height          =   330
      Left            =   1800
      TabIndex        =   5
      Text            =   "Hello World!"
      Top             =   1485
      Width           =   9105
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   1800
      TabIndex        =   4
      Top             =   1035
      Width           =   9105
   End
   Begin VB.CommandButton Command4 
      Appearance      =   0  'Flat
      Caption         =   "Write port"
      Height          =   330
      Left            =   270
      TabIndex        =   3
      Top             =   1485
      Width           =   1455
   End
   Begin VB.CommandButton Command3 
      Appearance      =   0  'Flat
      Caption         =   "Read port"
      Height          =   330
      Left            =   270
      TabIndex        =   2
      Top             =   1035
      Width           =   1455
   End
   Begin VB.CommandButton Command2 
      Appearance      =   0  'Flat
      Caption         =   "Close port"
      Height          =   330
      Left            =   270
      TabIndex        =   1
      Top             =   585
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      Caption         =   "Open port"
      Height          =   330
      Left            =   270
      TabIndex        =   0
      Top             =   135
      Width           =   1455
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

'Open port
Private Sub Command1_Click()
    Dim Retval As Boolean
    Retval = Com_Open
End Sub
'Close port
Private Sub Command2_Click()
    Dim Retval As Boolean
    Retval = Com_Close
End Sub
'Read port
Private Sub Command3_Click()
    Dim s As String
    Dim a As Long
    Com_Read
    For a = 1 To Com_Byte_Read
            s = s & Chr(Buf(a - 1))
    Next a
    Text1.Text = s
End Sub
'Write port
Sub Command4_Click()
    Dim s As String
    Dim n As Long
    Dim a As Integer
    Dim Retval As Long
    s = Text2.Text
    s = Mid(s, 1, 255)
    n = Len(s)
    For a = 1 To n
        Buf(a - 1) = Asc(Mid(s, a, 1))
    Next a
    Com_Write
End Sub
'Exit programm
Private Sub Form_Unload(Cancel As Integer)
    Dim Retval As Long
    Retval = CloseHandle(Com_Handle)
End Sub
