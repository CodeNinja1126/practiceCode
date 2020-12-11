import time
import serial
import random

port0 = "COM11"
port1 = "COM10"
port2 = "COM7"

ser0 = serial.Serial(port0,115200)
ser1 = serial.Serial(port1,9600)
ser2 = serial.Serial(port2,9600)


def ledCon(playerNumber, posNumber, onOff):
    if(onOff==1):
        ser0.write("{0} {1}\n" .format(playerNumber,posNumber) .encode())
    elif(onOff==0):
        ser0.write("{}\n" .format(playerNumber*(-1)) .encode())

    
class player:
    def __init__(self, mon, pos, n):
        self.mon = mon
        self.pos = pos
        self.islandFlg = 0
        self.number = n
        self.estList = []
        self.GKList = [0,0]
        self.spaceGKFlag = 0
        print("플레이어 {0} 위치 {1} 돈 {2}" .format(self.number,self.pos, self.mon))
        ledCon(self.number, self.pos, 1)
        self.I2CSend(0, (int)(mon/1000))
        # 돈 정보 개인 LCD 출력
    def setData(self, mon, pos):
        if(pos > 40) : self.pos = pos - 40
        ledCon(self.number, self.pos, 0)
        self.mon = mon
        self.pos = pos
        print("플레이어 {0} 위치 {1} 돈 {2}" .format(self.number,self.pos, self.mon))
        ledCon(self.number, self.pos, 1)
        self.I2CSend(0, (int)(mon/1000))
        # 돈 정보 개인 LCD 수정
    def setPos(self, pos):
        ledCon(self.number, self.pos, 0)
        self.pos = pos
        if(self.pos > 40) : self.pos -= 40
        elif(self.pos < 1): self.pos += 40
        print("플레이어 {0} 위치 {1}" .format(self.number, self.pos))
        ledCon(self.number, self.pos, 1)
    def setMon(self, mon):
        self.mon = int(mon)
        print("플레이어 {0} 돈 {1}" .format(self.number, self.mon))
        self.I2CSend(0, (int)(mon/1000))
        # 돈 정보 개인 LCD 출력
    def getEst(self, est):
        self.estList.append(est)
        est.setPlayer(self)
        if(type(est) == tour):
            est.build = 1
            self.I2CSend(1, 1000+est.code*10)
        else:
            est.setBuild([1,0,0,0])
            self.I2CSend(1, 1000+est.code*10)
            ser2.write("{0} {1}\n" .format(est.servo ,1) .encode())
        print("자산 {} 추가" .format(est.name))
        # 땅 LED 출력
        # 자산 정보 개인 LCD 추가
    def buildEst(self, est, build):
        est.setBuild(build)
        self.I2CSend(1, est.code*10)
        self.I2CSend(1, 1000+est.code*10+build[1:].index(1)+1)
        ser2.write("{0} {1}\n" .format(est.servo ,build[1:].index(1)+2) .encode())
        print("자산 {}에 건물변경" .format(est.name))
        # LED 휘도 변경
        # 개인 LCD 변경
    def delEst(self, est):
        self.estList.remove(est)
        est.resetEst()
        self.I2CSend(1, est.code*10)
        if(type(est.build) == list):
            ser2.write("{0} {1}\n" .format(est.servo ,0) .encode())
        print("자산 {} 삭제" .format(est.name))
        # 자산 정보 개인 LCD 수정
        # 땅 LED OFF
    def getGK(self, GK):
        if(GK == 0):
            self.GKList[0] += 1
            self.I2CSend(2, 1)
            print("황금 열쇠 우대권 획득 ")
        elif(GK == 1):
            self.GKList[1] += 1
            self.I2CSend(2, 11)
            print("황금 열쇠 무전기 획득 ")
        # 황금 열쇠 정보 개인 LCD 추가
    def useGK(self, GK, GKStack):
        if(GK == 0):
            self.GKList[0] -= 1
            GKStack.list.insert(0,30)
            self.I2CSend(2, 0)
            print("황금 열쇠 우대권 사용")
        elif(GK == 1):
            self.GKList[1] -= 1
            GKStack.list.insert(0,26)
            self.I2CSend(2, 10)
            print("황금 열쇠 무전기 사용")
        # 황금 열쇠 정보 개인 LCD 추가
    def sellRadio(self, GKStack):
        self.GKList[1] -= 1
        GKStack.list.insert(0,26)
        self.I2CSend(2, 10)
        self.setMon(self.mon + 500000)
        print("황금 열쇠 무전기를 팔았습니다.")
    def goFow(self, n, sleep):
        for a in range(n):
            self.setPos(self.pos+1)
            if (self.pos == 1):
                self.setMon(self.mon + 200000)
                print("월급을 받았습니다.")
            time.sleep(sleep)
    def goBack(self, n, sleep):
        for a in range(n):
            self.setPos(self.pos-1)
            if (self.pos == 1):
                self.setMon(self.mon + 200000)
                print("월급을 받았습니다.")
            time.sleep(sleep)
    def I2CSend(self, kind, value):
        ser1.write("0{}\n" .format(self.number*1000000+kind*100000+value) .encode())
    def I2CSendM(self, value):
        ser1.write("1{}\n" .format(self.number*1000000+value) .encode())
    def I2CRead(self):
        value = ser1.read().decode()
        return value

class estate:
    def __init__(self, name, price, fee, code,servo):
        self.name = name
        self.price = price
        self.fee = fee
        self.player = 0
        self.code = code
        self.servo = servo
        self.build = [0,0,0,0]
        # price는 튜플, (대지료, 별장, 빌딩, 호텔) 단 관광지는 정수형
        # fee도 튜플, (대지료, 별장, 빌딩, 호텔) 단 관광지는 정수형
    def setBuild(self, build):
        self.build = build
        # build는 리스트, [대지, 별장, 빌딩, 호텔]
    def setPlayer(self, player):
        self.player = player
        # 땅 LED 출력
    def resetEst(self):
        self.player = 0
        self.setBuild([0,0,0,0])
        # 땅 LED OFF

class tour:
    def __init__(self, name, price, fee, code):
        self.name = name
        self.price = price
        self.fee = fee
        self.player = 0
        self.build = 0
        self.code = code
    def setBuild(self, build):
        self.build = build
    def setPlayer(self, player):
        self.player = player
    def resetEst(self):
        self.player = 0
        self.setBuild(0)
        # 땅 LED OFF

class GKStack:
    def __init__(self):
        self.list = list(range(1,31))
        random.shuffle(self.list)
    
