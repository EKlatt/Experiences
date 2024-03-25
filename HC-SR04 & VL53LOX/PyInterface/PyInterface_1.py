# https://tmml.sourceforge.net/doc/tk/keyword-index.html#KW-container
# https://docs.python.org/3/library/tkinter.ttk.html
# https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/index.html
# https://www.pythontutorial.net/tkinter/tkinter-button/
# https://www.pythontutorial.net/tkinter/tkinter-combobox/
# https://www.plus2net.com/python/tkinter-Combobox.php
# https://www.inf-schule.de/software/gui/entwicklung_tkinter/auswahl/listbox
# https://pyserial.readthedocs.io/en/latest/shortintro.html
# https://github.com/pyserial/pyserial/issues/655
# https://docs.huihoo.com/tkinter/tkinter-reference-a-gui-for-python/grid.html
# https://www.w3resource.com/python-exercises/tkinter/python-tkinter-canvas-and-graphics-exercise-4.php
# https://tkdocs.com/shipman/ttk-style-layer.html

from tkinter import *
from tkinter.ttk import *
import tkinter as tk
import tkinter.ttk as ttk
from tkinter import font
from tkinter import scrolledtext
from tkinter.messagebox import showinfo
from serial.tools.list_ports import comports
import serial

import platform
MyPlatform = platform.system()      # Determine Windows or Linux
print(MyPlatform)

# Varibale "ser_open" holds the status of a choosed Port, if Port opened then True
ser_open = False

data_points = [(0,0,0)]             # Sample data points (x, y, z) for the line graph
count = 0                           # counts the datapoints
VLnew = False                       # only True if V52LOX data are valid
HCnew = False                       # only True if HC_SR04 data are valid

def message_box(msg):               # for debugging purposes
    showinfo(
        title='Debug',
        message=msg
    )

def callPorts():                    # function when "Update Ports" button is pressed
    my_new=[]
    for port in comports():
        my_new.append(port)
    MyListBox['values'] = my_new

def port_changed(event):            # function when item in ListBox has changed
    MyText.insert(tk.INSERT, 'Port choosed\n')

def callOpenPort():                 # function when "Open Port" button is pressed
    global ser                      # get the global ser-object for change

    comPort = MyListBox.get()       # get a choosed item from list of ports

    if MyPlatform=='Windows':
        comPort = comPort[0:4]      # selects the Portname COMx (works for Windows)
    if MyPlatform=='Linux':
        # pass                      # selects the Portname (works for Linux)
        token = comPort.split(chr(0x20))    # just a space: chr(0x20)
        comPort = token[0]

    baudRate = 115200
    ser = serial.Serial(comPort , baudRate, timeout=0, writeTimeout=0)  #ensure non-blocking

    global ser_open                  # get the global ser-object for change
    ser_open = True                  # tells the readSerial()-function that port a por is open

    bootStrap = ''                  # get rid off ESP32 bootstrap messages until BootStrapReady-message
    while bootStrap != 'BootStrapReady':
        bootStrap = ser.readline().decode("utf-8").rstrip()

    MyText.insert(tk.INSERT, 'Port: ' + ser.name + ' open\n')

serBuffer = ''                                  # make my own buffer for incoming data via Serial

def readSerial():                               # get data from Serial port
    while ser_open:
        c = ser.read().decode("ascii")          # read a character from Serial
        if len(c) == 0:                         # was anything read?
            break                               # no leave while
        global serBuffer                        # get global buffer
        if c == '\r':
            c = ''                              # don't want returns
        if c == '\n':
            serBuffer += "\n"                   # add the newline to the buffer
                                                # terminate reading
            MyText.insert('0.0', serBuffer)     # add the line to "MyText"
            evaluateInput()

            serBuffer = ""                      # empty the buffer

        else:
            serBuffer += c                      # add to the buffer

    root.after(10, readSerial)                  # check serial again soon

def evaluateInput():                            # evaluate data from Serial port
                                                # expected data format: name:value
                                                # e.g. HC:213
    token = serBuffer.split(':')
    if len(token) > 1:
        sensor = token[0]
        if token[1].rstrip().isnumeric():
            value = int(token[1])
        else:
            sensor = 'NoSensor'
            value = 0
            MyText.insert('0.0', sensor, ':', value)

        if sensor=='VLOVER':
            MyShowVL.delete(0,tk.END)
            MyShowVL.insert(tk.END, "Over")
        if sensor=='HCOVER':
            MyShowHC.delete(0,tk.END)
            MyShowHC.insert(tk.END, "Over")
        if sensor=='VL':
            MyShowVL.delete(0,tk.END)
            MyShowVL.insert(tk.END, value)
            global VLgraph
            VLgraph = value/20
            MyBarVL['value'] = VLgraph
            global VLnew
            VLnew = True
        if sensor=='HC':
            MyShowHC.delete(0,tk.END)
            MyShowHC.insert(tk.END, value)
            global HCgraph
            HCgraph = value/20
            MyBarHC['value'] = HCgraph
            global HCnew
            HCnew = True

        if VLnew and HCnew:
            graph_data(VLgraph, HCgraph )
            VLnew = False
            HCnew = False

def graph_data( VLvalue, HCvalue ):
    global data_points
    global count
    count = count + 1
    data_points.append((count, int(VLvalue), int(HCvalue)))
    if count==45:
        count = 0
        data_points = [(0,0,0)]
        MyGraph.delete('all')

    draw_line_graph()

def on_closing():
    if ser_open:
        ser.close()
    root.destroy()
    print('Application stopped')

root = tk.Tk()
root.geometry("1024x768")
root.resizable(False, False)
root.title('V53LOX & HC-SR04')

style = ttk.Style()
style.theme_use('clam')
frame1 = ttk.Frame(root)
frame1['borderwidth'] = 5
frame1['relief'] = 'solid'
frame1.place(x=10, y=10, width=400, height=740 )

frame2 = ttk.Frame(root)
frame2['borderwidth'] = 5
frame2['relief'] = 'solid'
frame2.place(x=420, y=10, width=580, height=300 )

frame3 = ttk.Frame(root)
frame3['borderwidth'] = 5
frame3['relief'] = 'solid'
frame3.place(x=420, y=320, width=580, height=430 )

style.configure("yellow.TLabel", font=('TkTextFont', 20), background='#e8eb34')
MyLabel1 = ttk.Label(frame1, style='yellow.TLabel', text='COM-Port')
MyLabel1.place(x=10, y=10, width=150)

MyLabel2 = ttk.Label(frame1, style='yellow.TLabel', text='list:')
MyLabel2.place(x=10, y=60, width=150)

MyLabel3 = ttk.Label(frame1, style='yellow.TLabel', text='Monitor')
MyLabel3.place(x=10, y=170, width=150)

MyLabel4 = ttk.Label(frame2, style='yellow.TLabel',text='V52LOX')
MyLabel4.place(x=10, y=10, width=150)

MyLabel5 = ttk.Label(frame2, style='yellow.TLabel', text='HC_SR04')
MyLabel5.place(x=300, y=10, width=150)

MyShowlFont = font.Font(family='TkTextFont', size=40, weight='normal')
style.configure("green.TEntry", foreground='green')
MyShowVL = ttk.Entry(frame2, font=MyShowlFont, style='green.TEntry', justify='center')
MyShowVL.place(x=10, y=60, width=240)


style.configure("red.TEntry", foreground='red')
MyShowHC = ttk.Entry(frame2, font=MyShowlFont, style='red.TEntry', justify='center')
MyShowHC.place(x=300, y=60, width=240)

listbox_var = tk.StringVar()
MyListBox = ttk.Combobox(frame1, textvariable=listbox_var)
MyListFont = font.Font(family='TkTextFont',size=14)
MyListBox['font'] = MyListFont
MyListBox['state'] = 'readonly'
MyListBox.place(x=10,y=110,width=370,height=50)
MyListBox.bind('<<ComboboxSelected>>', port_changed)

# we have a ComboBox for the Serial Ports, lets try to find some ports
try:
    callPorts()                                         # Look for COM-Ports
    MyListBox.current(0)
except:
    pass

style.configure('big.TButton', font=('TkTextFont', 20), foreground="blue")
MyButton1 = ttk.Button(frame1, text='Update Ports!', command=callPorts, style="big.TButton")
MyButton1.place(x=180, y=10, width=200, height=40)

MyButton2 = ttk.Button(frame1, text='Open Port', command=callOpenPort, style="big.TButton")
MyButton2.place(x=180, y=60, width=200, height=40)

MyText = scrolledtext.ScrolledText(frame1, wrap=tk.WORD)
MyText.place(x=10, y=220, width=320, height=480)
MyText.configure(font=("Times New Roman", 15))

MyText.insert(tk.INSERT, 'EBW\n')
MyText.insert(tk.INSERT, '1. Update Ports\n')
MyText.insert(tk.INSERT, '2. Choose Port from list\n')
MyText.insert(tk.INSERT, '3. Open Port & Start\n')

style.configure("green.Horizontal.TProgressbar", background='green')
MyBarVL = ttk.Progressbar(frame2, orient='horizontal', style='green.Horizontal.TProgressbar', length=530, mode='determinate')
MyBarVL.place(x=10, y=150, height=50)

style.configure("red.Horizontal.TProgressbar", background='red')
MyBarHC = ttk.Progressbar(frame2, orient='horizontal', style='red.Horizontal.TProgressbar', length=530, mode='determinate')
MyBarHC.place(x=10, y=220, height=50)

MyGraph = tk.Canvas(frame3, width=550, height=400, bg="white")
MyGraph.place(x=10, y=10)

def draw_line_graph():
    x_scale = 10  # Scale for x-axis
    y_scale = 2  # Scale for y-axis
    z_scale = 2  # Scale for Z-axis
    x_offset = 30
    y_offset = 380

    # Draw x and y axes
    MyGraph.create_line(x_offset, y_offset, x_offset + 500, y_offset, width=2)
    MyGraph.create_line(x_offset, y_offset, x_offset, y_offset - 350, width=2)

    # Draw data points and lines
    for i in range(len(data_points) - 1):
        x1, y1, z1 = data_points[i]
        x2, y2, z2 = data_points[i + 1]
        x1_scaled, y1_scaled, z1_scaled = x1 * x_scale + x_offset, y_offset - y1 * y_scale, y_offset - z1 * z_scale
        x2_scaled, y2_scaled, z2_scaled = x2 * x_scale + x_offset, y_offset - y2 * y_scale, y_offset - z2 * z_scale

        MyGraph.create_oval(x1_scaled - 3, y1_scaled - 3, x1_scaled + 3, y1_scaled + 3, fill="blue")
        MyGraph.create_line(x1_scaled, y1_scaled, x2_scaled, y2_scaled, fill="green", width=4)

        MyGraph.create_oval(x1_scaled - 3, z1_scaled - 3, x1_scaled + 3, z1_scaled + 3, fill="blue")
        MyGraph.create_line(x1_scaled, z1_scaled, x2_scaled, z2_scaled, fill="red", width=4)

MyListBox.focus()


root.after(100, readSerial)                 # interrupt for update data from Serial interface
root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()