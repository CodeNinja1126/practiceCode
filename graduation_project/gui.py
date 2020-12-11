import tkinter
import os
import tkinter.font
import time
import sys

startFlg = 0
startMoney = 0
timeoutTurn = 0
poormanFlg = 0
gameMessageFlg = 0


def root():
    loop = tkinter.Tk()
    f = tkinter.Frame(loop)
    loop.title("Cremarble")
    loop.geometry("800x480")

    button = tkinter.Button(f,width=50, height=20,
                            text = "시작", 
                            command = lambda:  start(loop, f)).place(x = 225, y = 75)

    f.pack(fill="both", expand=True)
    loop.mainloop()



def start(loop, f):
    global startFlg
    if(startFlg != 0):
        startFlg = 2
        f.destroy()
        f = tkinter.Frame(loop)
    
        button1 = tkinter.Button(f,width=30, height=15,
                            text = "스탠다드", 
                            command = lambda: standard(loop, f)).place(x = 30, y = 100)

        button2 = tkinter.Button(f,width=30, height=15,
                            text = "제한 턴 게임", 
                            command = lambda: timeout(loop, f)).place(x = 280, y = 100)

        button3 = tkinter.Button(f,width=30, height=15,
                            text = "거지왕 게임",
                            command = lambda: poorman(loop, f)).place(x = 530, y = 100)

        f.pack(fill="both", expand=True)

def standard(loop, f):
    global startMoney
    global timeoutTurn
    
    startMoney = 2000000
    timeoutTurn = 0

    f.destroy()
    f = tkinter.Frame(loop)

    label1 = tkinter.Label(f,text = "돈").place(x = 0,y = 100)

    entry=tkinter.Entry(f)
    entry.insert(10,str(startMoney))
    entry.place(x = 50,y = 100)

    button1 = tkinter.Button(f,width=10, height=5,text = '+',
                             command = lambda: moneyUpDown(1,entry)).place(x = 200, y = 100)
    button2 = tkinter.Button(f,width=10, height=5,text = '-', 
                             command = lambda: moneyUpDown(0,entry)).place(x = 270, y = 100)
    startBtn = tkinter.Button(f,width=30, height=15,
                            text = "게임 시작!!!", 
                            command = lambda: gameStart(loop,f)).place(x = 530, y = 100)
    
    f.pack(fill="both", expand=True)

def timeout(loop, f):
    global startMoney
    global timeoutTurn
    
    startMoney = 2000000
    timeoutTurn = 15

    f.destroy()
    f = tkinter.Frame(loop)
    
    label1 = tkinter.Label(f,text = "돈").place(x = 0,y = 100)
    label2 = tkinter.Label(f,text = "턴 수").place(x = 0,y = 200)
    
    entry1=tkinter.Entry(f)
    entry1.insert(10,str(startMoney))
    entry1.place(x = 50,y = 100)

    entry2=tkinter.Entry(f)
    entry2.insert(10,str(timeoutTurn))
    entry2.place(x = 50,y = 200)

    button1 = tkinter.Button(f,width=10, height=5,text = '+',
                             command = lambda: moneyUpDown(1,entry1)).place(x = 200, y = 100)
    button2 = tkinter.Button(f,width=10, height=5,text = '-',
                             command = lambda: moneyUpDown(0,entry1)).place(x = 270, y = 100)

    button3 = tkinter.Button(f,width=10, height=5,text = '+', 
                             command = lambda: turnUpDown(1,entry2)).place(x = 200, y = 200)
    button4 = tkinter.Button(f,width=10, height=5,text = '-', 
                             command = lambda: turnUpDown(0,entry2)).place(x = 270, y = 200)

    startBtn = tkinter.Button(f,width=30, height=15,
                            text = "게임 시작!!!", 
                            command = lambda: gameStart(loop,f)).place(x = 530, y = 100)
    
    f.pack(fill="both", expand=True)

def poorman(loop, f):
    global startMoney
    global timeoutTurn
    global poormanFlg

    poormanFlg = 1
    
    startMoney = 2000000
    timeoutTurn = 15

    f.destroy()
    f = tkinter.Frame(loop)

    label1 = tkinter.Label(f,text = "턴 수").place(x = 0,y = 100)

    entry2=tkinter.Entry(f)
    entry2.insert(10,str(timeoutTurn))
    entry2.place(x = 50,y = 100)

    button3 = tkinter.Button(f,width=10, height=5,text = '+',
                             command = lambda: turnUpDown(1,entry2)).place(x = 200, y = 100)
    button4 = tkinter.Button(f,width=10, height=5,text = '-', 
                             command = lambda: turnUpDown(0,entry2)).place(x = 270, y = 100)

    startBtn = tkinter.Button(f,width=30, height=15,
                            text = "게임 시작!!!", 
                            command = lambda: gameStart(loop,f)).place(x = 530, y = 100)
    
    f.pack(fill="both", expand=True)

def moneyUpDown(signed, entry):
    global startMoney
    if(startMoney<3000000 and signed == 1):
        entry.delete(0,10)
        startMoney += 100000
        entry.insert(10,str(startMoney))
    elif(startMoney>1000000 and signed == 0):
        entry.delete(0,10)
        startMoney -= 100000
        entry.insert(10,str(startMoney))


def turnUpDown(signed, entry):
    global timeoutTurn
    if(timeoutTurn<30 and signed == 1):
        entry.delete(0,10)
        timeoutTurn += 5
        entry.insert(10,str(timeoutTurn))
    elif(timeoutTurn>10 and signed == 0):
        entry.delete(0,10)
        timeoutTurn -= 5
        entry.insert(10,str(timeoutTurn))

def gameStart(loop,f):
    global startFlg
    global gameMessageFlg
    startFlg = 3
    f.destroy()

    f = tkinter.Frame(loop)


    button1 = tkinter.Button(f,width=20, height=10,
                            text = "재시작", 
                            command = lambda: restart()).place(x = 0, y = 200)
    
    f.pack(fill="both", expand=True)
        
    if(gameMessageFlg == 0):
        font=tkinter.font.Font( size=40, slant="italic")
        button2 = tkinter.Button(f,width=10, height=5,
                            text = "황금열쇠", font = font, 
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)

    elif(gameMessageFlg == 1):
        
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "콩코드 여객기를\n타고 타이페이로\n갑니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 2):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "퀸 엘리자베스호를\n타고 홍콩으로\n 갑니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 3):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "출발지로 \n바로 이동합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 4):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "서울로\n출발합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 5):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "부산으로\n출발합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 6):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "제주도로\n출발합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 7):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "뒤로 두 칸\n갑니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 8):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "뒤로 세 칸\n갑니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 9):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "무인도로\n갑니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 10):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "사회복지기금\n수령처로 \n이동합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 11):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "세계일주를\n합니다.\n사회복지기금을\n수령합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 12 or gameMessageFlg == 13 ):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "우주여행\n승강장으로\n이동합니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 14):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "노벨 평화상을\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 15):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "노후 연금을\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 16):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "복권에\n당첨되었습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 17):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "생일 축하금을\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 18):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "자동차 경주\n우승금을\n받았습니다", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 19):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "장학금을\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 20):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "건물 방범비를\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 21):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "건물 수리비를\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 22):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "정기종합소득세를를\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 23):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "과속운전벌금을\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 24):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "병원비를\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 25):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "해외 유학비를\n냅니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 26):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "무전기를\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 27 or gameMessageFlg == 28):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "가장 비싼 땅을\n반값에\n파십시오.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0
    elif(gameMessageFlg == 29 or gameMessageFlg == 30):
        font=tkinter.font.Font( size=30, slant="italic")
        button2 = tkinter.Button(f,width=15, height=7,
                            text = "우대권을\n받았습니다.", font = font,
                            command = lambda: gameStart(loop,f)).place(x = 250, y = 100)
        gameMessageFlg = 0

def restart():
    os.system('sudo reboot')



    
