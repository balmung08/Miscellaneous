import serial
import RPi.GPIO as GPIO
import judge
import threading
import time
import oled
import connect

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(26,GPIO.OUT,initial=GPIO.LOW)#blue
pwm = GPIO.PWM(26,50)

ser0 = serial.Serial ("/dev/ttyUSB0", 9600)
ser1 = serial.Serial ("/dev/ttyUSB1", 9600)
G,H = [],[]
s = 2

def status():
    global s,G
    while True:
        oled.loading(G,s)
def get_g():
    global G
    while True:
        try:
            if(len(G)>=300):
               continue 
            data0 = ser0.readline()
            data0 = int(data0)
            G.append(data0)
            oled.loading(G,s)
        except Exception as e:
            print(e)
def get_h():
    global H
    while True:
        try:
            if(len(H)>=300):
               continue 
            data1 = ser1.readline()
            data1 = int(data1)
            if 50<=data1<=130:
                H.append(data1)
        except Exception as e:
            print(e)
def main():
    global s
    connect.update(2)
    state = 0
    while True:
        if len(G)>=300 and len(H)>=300 and (state==0):
            print("doing")
            A,B,a1,a2,b1,b2,HL_std = judge.judge_standard(G,H)
            state = 1
            s = 0
            connect.update(s)
            #print(A,B,a1,a2,b1,b2,HL_std)
            G.clear()
            H.clear()
        i = 0
        while state:
            if len(G)>=300 and len(H)>=300:
                s = judge.judge_process(G,H,A,B,a1,a2,b1,b2,HL_std)
                G.clear()
                H.clear()
                connect.update(s)
                if s==1 or s==3:
                    pwm.start(20)
                    time.sleep(1)
                    pwm.start(0)
                i+=1

class myThread(threading.Thread):
    def __init__(self, threadID, name, function):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.function = function
    def run(self):
        self.function()
        # self.lock.acquire()

thread1 = myThread(1, "Thread-1", get_g)
thread2 = myThread(2, "Thread-2", get_h)
thread3 = myThread(3, "Thread-3", main)
thread3 = myThread(4, "Thread-4", status)
thread1.daemon = True
thread2.daemon = True
thread4.daemon = True
# 开启新线程
thread1.start()
thread2.start()
thread3.start()
thread4.start()

