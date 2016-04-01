Attribute VB_Name = "Module1"
'COMAPIvb v.1.01
'Electron18
'www.softelectro.ru
'06.04.2012

Option Explicit

'The declaration of used functions API
Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, ByVal lpSecurityAttributes As Long, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Declare Function ReadFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, lpOverlapped As Long) As Boolean
Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Boolean
Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Declare Function SetCommState Lib "kernel32" (ByVal hFile As Long, lpDCB As DCB) As Boolean
Declare Function SetCommTimeouts Lib "kernel32" (ByVal hFile As Long, lpCommTimeouts As COMMTIMEOUTS) As Boolean
Declare Function GetLastError Lib "kernel32" () As Long


Public Com_Handle As Long 'Descriptor of port
Public Buf(255) As Byte 'The buffer of port
Public Com_Byte_Read As Long 'количество принятых байт
'Structure for parameter setup of port
Type DCB
    DCBlength As Long       'Length of structure in byte.
    BaudRate As Long        'Speed of data exchangeб, bps
    fBitFields As Long      'Bit field for setting of port
    wReserved As Integer    'Reserved
    XonLim As Integer       'minimum number of bytes in the buffer to send Xon
    XoffLim As Integer      'maximum number of bytes in the buffer for sending Xof
    ByteSize As Byte        'the number of bits in a symbol
    Parity As Byte          'parity check mode
    StopBits As Byte        'Stop bit length
    XonChar As Byte         'character code Xon
    XoffChar As Byte        'character code Xof
    ErrorChar As Byte       'code symbol error
    EofChar As Byte         'character code data end
    EvtChar As Byte         'character code Events
    wReserved1 As Integer   'Reserved
End Type
Public DCB1 As DCB
'Structure for parameter setup of port
Type COMMTIMEOUTS
    ReadIntervalTimeout As Long       'интервал между символами
    ReadTotalTimeoutMultiplier As Long        'множитель для периода простоя чтения
    ReadTotalTimeoutConstant As Long      'постоянная для периода простоя чтения
    WriteTotalTimeoutMultiplier As Long    'множитель для периода простоя записи
    WriteTotalTimeoutConstant As Long       'постоянная для периода простоя записи
End Type
Public COMMTIMEOUTS1 As COMMTIMEOUTS


'Function of opening of port
Function Com_Open()
    Dim Retval As Long
    Dim Retval_B As Boolean
    Dim Retval_S As Boolean
    
    Retval = CreateFile("COM1:", &HC0000000, 0, 0, 3, 0, 0)
    If Retval = -1 Then
        MsgBox ("The open error of port:" & GetLastError)
    Else
        Com_Handle = Retval
        'set dcb
        DCB1.BaudRate = 1200
        DCB1.ByteSize = 8
        DCB1.DCBlength = 28
        DCB1.EofChar = 0
        DCB1.ErrorChar = 0
        DCB1.EvtChar = 0
        DCB1.fBitFields = 1
        DCB1.Parity = 0
        DCB1.StopBits = 0
        DCB1.wReserved = 0
        DCB1.wReserved1 = 0
        DCB1.XoffChar = 0
        DCB1.XoffLim = 0
        DCB1.XonChar = 0
        DCB1.XonLim = 0
        Retval_S = SetCommState(Com_Handle, DCB1)
        'set timeout
        COMMTIMEOUTS1.ReadIntervalTimeout = -1
        COMMTIMEOUTS1.ReadTotalTimeoutConstant = 0
        COMMTIMEOUTS1.ReadTotalTimeoutMultiplier = 0
        COMMTIMEOUTS1.WriteTotalTimeoutConstant = 5000
        COMMTIMEOUTS1.WriteTotalTimeoutMultiplier = 0
        Retval_B = SetCommTimeouts(Com_Handle, COMMTIMEOUTS1)
        
        If Retval_B = False Or Retval_S = False Then
            MsgBox ("Error DCB&Timout:" & GetLastError)
        End If
        MsgBox ("Open port HANDLE:" & Com_Handle)
       
    End If
    
End Function
'Function of closing the port
Function Com_Close()
    Dim Retval As Long
    
    Retval = CloseHandle(Com_Handle)
    If Retval = 0 Then
        MsgBox ("Close port ERROR:" & GetLastError)
    Else
        MsgBox ("Close port")
    End If
End Function

'Recording function to the port
Function Com_Write()
    Dim Len_Buf As Long
    Dim Retval As Boolean
    PurgeBuf
    Retval = WriteFile(Com_Handle, Buf(0), 255, Len_Buf, 0)
    If Retval = False Then
        MsgBox ("Write port ERROR:" & GetLastError)
    Else
        MsgBox ("Data write: Ok")
    End If
   
End Function

'function of reading from the port
Function Com_Read()
    Dim Retval As Boolean
    PurgeBuf
    Retval = ReadFile(Com_Handle, Buf(0), 255, Com_Byte_Read, 0)
    If Retval = False Then
        MsgBox ("Read port ERROR:" & GetLastError & Err.Description)
    Else
        MsgBox ("Data read: Ok")
    End If
  
End Function
'clear buffer
Sub PurgeBuf()
    Dim a As Integer
    
    For a = 0 To 255
        Buf(a) = &H20
    Next a
End Sub
