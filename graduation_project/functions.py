import random
import time
import classes
import gui

GKStack = classes.GKStack()
pList=[]
fund = 0

타이페이 = classes.estate("타이페이", (50000,50000,150000,250000), (2000,10000,90000,250000),1,1)
홍콩 = classes.estate("홍콩", (80000,50000,150000,250000), (4000,20000,180000,450000),2,2)
마닐라 = classes.estate("마닐라", (80000,50000,150000,250000), (4000,20000,180000,450000),3,3)
제주도 = classes.tour("제주도", 200000, 300000,4)
싱가포르 = classes.estate("싱가포르", (100000,50000,150000,250000), (6000,30000,270000,550000),5,4)
카이로 = classes.estate("카이로", (100000,50000,150000,250000), (6000,30000,270000,550000),6,5)
이스탄불 = classes.estate("이스탄불", (120000,50000,150000,250000), (8000,40000,300000,600000),7,6)
아테네 = classes.estate("아테네", (140000,100000,300000,500000), (10000,50000,450000,750000),8,7)
코펜하겐 = classes.estate("코펜하겐", (160000,100000,300000,500000), (12000,60000,500000,900000),9,8)
스톡홀름 = classes.estate("스톡홀름", (160000,100000,300000,500000), (12000,60000,500000,900000),10,9)
콩코드여객기 = classes.tour("콩코드여객기", 200000, 300000,11)
취리히 = classes.estate("취리히", (180000,100000,300000,500000), (14000,70000,500000,950000),12,10)
베를린 = classes.estate("베를린", (180000,100000,300000,500000), (14000,70000,500000,950000),13,11)
몬트리올 = classes.estate("몬트리올", (200000,100000,300000,500000), (16000,80000,550000,1000000),14,12)
부에노스아이레스 = classes.estate("부에노스아이레스", (220000,150000,450000,750000), (18000,90000,700000,1050000),15,13)
상파울로 = classes.estate("상파울로", (240000,150000,450000,750000), (20000,100000,750000,1100000),16,14)
시드니 = classes.estate("시드니", (240000,150000,450000,750000), (20000,100000,750000,1100000),17,15)
부산 = classes.tour("부산", 500000, 600000,18)
하와이 = classes.estate("하와이", (260000,150000,450000,750000), (22000,110000,800000,1150000),19,16)
리스본 = classes.estate("리스본", (260000,150000,450000,750000), (22000,110000,800000,1150000),20,17)
퀸엘리자베스호 = classes.tour("퀸엘리자베스호", 300000, 300000,21)
마드리드 = classes.estate("마드리드", (280000,150000,450000,750000), (24000,120000,850000,1200000),22,18)
도오쿄오 = classes.estate("도오쿄오", (300000,200000,600000,1000000), (26000,130000,900000,1270000),23,19)
콜롬비아호 = classes.tour("콜롬비아호", 450000, 400000,24)
파리 = classes.estate("파리", (320000,200000,600000,1000000), (26000,150000,1000000,1400000),25,20)
로마 = classes.estate("로마", (320000,200000,600000,1000000), (26000,150000,1000000,1400000),26,21)
런던 = classes.estate("런던", (350000,200000,600000,1000000), (35000,170000,1100000,1500000),27,22)
뉴욕 = classes.estate("뉴욕", (350000,200000,600000,1000000), (35000,170000,1100000,1500000),28,23)
서울 = classes.tour("서울", 1000000, 2000000,29)

def ranDice():
    #주사위 굴리기 그래픽과 함께 구현
    return random.randint(1,6)

def genTurn(player):                                                  #주사위를 굴리는 가장 기본적인 경우
    global pList
    douFlg = 0
    while(1):
        a, b = ranDice(), ranDice()
        print("플레이어 {0} 주사위 번호 {1} {2}" .format(player.number, a,b))
        player.I2CSendM(100+a*10+b)
        player.I2CRead()
        # 개인 LCD 출력
        if (a == b): douFlg += 1
        if (douFlg > 2):
            print("3연속 더블로 무인도로갑니다.")
            player.I2CSendM(1)
            player.I2CRead()
            time.sleep(0.3)
            player.setPos(11)
            player.I2CSend(3,3)
            break
        player.goFow(a+b, 0.4)
        landOrder(player)
        if (a != b or player.pos == 11 or pList.count(player) == 0): break
        elif(player.pos == 31):
            print("우주 여행을 하시겠습니까?")
            player.I2CSendM(2)
            spacetourFlg = player.I2CRead()
            if(spacetourFlg == '1'): break
            

def turn(player):
    if(player.pos == 11 and player.islandFlg < 3):              #무인도의 경우
        print("무인도입니다.")
        player.I2CSendM(6)
        player.I2CRead()
        if(player.GKList[1] == 1):
            print("무전기를 사용해 탈출하시겠습니까?")      #무전기의 경우
            player.I2CSendM(3)
            a = player.I2CRead()
            if(a == '1'):
                player.useGK(1,GKStack)
                print("무전기를 사용했습니다.")
                player.I2CSendM(4)
                player.I2CRead()
                print("출발합니다.")
                player.I2CSendM(5)
                player.I2CRead()
                player.islandFlg = 0
                player.I2CSend(3,4)
                genTurn(player)
            else:
                print("주사위를 굴립니다.")
                a, b = ranDice(), ranDice()
                print("주사위 번호 {0} {1}" .format(a, b))
                player.I2CSendM(100+a*10+b)
                player.I2CRead()
                if(a == b):
                    time.sleep(0.3)
                    print("더블이 나와 탈출합니다.")
                    player.I2CSendM(7)
                    player.I2CRead()
                    player.islandFlg = 0
                    player.I2CSend(3,4)
                    player.goFow(a+b, 0.4)
                    landOrder(player)
                else:
                    player.islandFlg += 1;
                    time.sleep(0.3)
                    print("무인도를 탈출하지 못했습니다.")
                    player.I2CSendM(8)
                    player.I2CRead()
                    player.I2CSend(3, 3-player.islandFlg)
                    time.sleep(0.3)
                    print("{}턴 남았습니다." .format(3 - player.islandFlg))
        else:
            a, b = ranDice(), ranDice()
            print("주사위 번호 {0} {1}" .format(a, b))
            player.I2CSendM(100+a*10+b)
            player.I2CRead()
            if(a == b):
                time.sleep(0.3)
                print("더블이 나와 탈출합니다.")
                player.I2CSendM(7)
                player.I2CRead()
                player.islandFlg = 0
                player.I2CSend(3,4)
                player.goFow(a+b, 0.4)
                landOrder(player)
            else:
                player.islandFlg += 1;
                time.sleep(0.3)
                print("무인도를 탈출하지 못했습니다.")
                player.I2CSendM(8)
                player.I2CRead()
                player.I2CSend(3,3- player.islandFlg)
                time.sleep(0.3)
                print("{}턴 남았습니다." .format(3 - player.islandFlg))
    elif(player.pos == 11 and player.islandFlg == 3):        #탈출의 경우
        print("무인도에서 모든 턴을 쉬었습니다.")
        player.I2CSendM(9)
        player.I2CRead()
        player.islandFlg = 0
        player.I2CSend(3,4)
        print("출발합니다.")
        genTurn(player)

    elif(player.pos == 31):                                  #콜롬비아호의 경우
        if(콜롬비아호.player == 0 or player.spaceGKFlag == 1):
            if(player.spaceGKFlag == 1): spaceGKFlag = 0
            print("우주 여행을 합니다.")
            player.I2CSendM(10)
            player.I2CRead()
            goTo = 1
            player.I2CSendM(11)
            classes.ledCon(player.number,player.pos,1)
            classes.ledCon(player.number,goTo,1)
            while(1):
                button = player.I2CRead()
                if(button=='1'):
                    if(goTo == 1): goTo = 40
                    elif(goTo == 32): goTo = 30
                    else:goTo -= 1
                    classes.ledCon(player.number, 1, 0)
                    classes.ledCon(player.number,player.pos,1)
                    classes.ledCon(player.number,goTo,1)
                elif(button=='2'):
                    if(goTo == 40): goTo = 1
                    elif(goTo == 30): goTo = 32
                    else:goTo += 1
                    classes.ledCon(player.number, 1, 0)
                    classes.ledCon(player.number,player.pos,1)
                    classes.ledCon(player.number,goTo,1)
                else:
                    classes.ledCon(player.number, 1, 0)
                    classes.ledCon(player.number,player.pos,1)
                    time.sleep(0.3)
                    break
            if(goTo>31): goTo -= 31
            else: goTo += 9
            player.goFow(goTo, 0.1)
            print("도착하였습니다.")
            player.I2CSendM(12)
            player.I2CRead()
            landOrder(player)
        else:
            print("우주 여행을 하시겠습니까?")  #1이 승낙 나머지 거절
            player.I2CSendM(2)
            spacetourFlg = player.I2CRead()
            if(player.mon >= 200000 and spacetourFlg == '1'):
                print("우주 여행을 합니다.")
                player.I2CSendM(10)
                player.I2CRead()
                print("돈을 지불합니다.")
                player.I2CSendM(13)
                player.I2CRead()
                콜롬비아호.player.setMon(콜롬비아호.player.mon+200000)
                player.setMon(player.mon-200000)
                goTo = 1
                player.I2CSendM(11)
                classes.ledCon(player.number,player.pos,1)
                classes.ledCon(player.number,goTo,1)
                while(1):
                    button = player.I2CRead()
                    if(button=='1'):
                        if(goTo == 1): goTo = 40
                        elif(goTo == 32): goTo = 30
                        else:goTo -= 1
                        classes.ledCon(player.number, 1, 0)
                        classes.ledCon(player.number,player.pos,1)
                        classes.ledCon(player.number,goTo,1)
                    elif(button=='2'):
                        if(goTo == 40): goTo = 1
                        elif(goTo == 30): goTo = 32
                        else:goTo += 1
                        classes.ledCon(player.number, 1, 0)
                        classes.ledCon(player.number,player.pos,1)
                        classes.ledCon(player.number,goTo,1)
                    else:
                        classes.ledCon(player.number, 1, 0)
                        classes.ledCon(player.number,player.pos,1)
                        time.sleep(0.3)
                        break
                if(goTo>31): goTo -= 31
                else: goTo += 9
                player.goFow(goTo, 0.1)
                print("도착하였습니다.")
                player.I2CSendM(12)
                player.I2CRead()
                landOrder(player)
            else:
                print("우주여행을 하지 않습니다.")
                player.I2CSendM(14)
                player.I2CRead()
                print("주사위를 굴립니다.")
                genTurn(player)
    else:
        genTurn(player)
        
 
def landOrder(player):
    global GKStack
    global fund
    if(player.pos == 1):
        startBonus(player)
    elif(player.pos == 2):
        if(타이페이.player == 0 or 타이페이.player == player):
            buyLand(player, 타이페이)
        else:
            payFee(player, 타이페이)
    elif(player.pos == 3):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)       
    elif(player.pos == 4):
        if(홍콩.player == 0 or 홍콩.player == player):
            buyLand(player, 홍콩)
        else:
            payFee(player, 홍콩)
    elif(player.pos == 5):
        if(마닐라.player == 0 or 마닐라.player == player):
            buyLand(player, 마닐라)
        else:
            payFee(player, 마닐라)
    elif(player.pos == 6):
        if(제주도.player == 0 or 제주도.player == player):
            buyTour(player, 제주도)
        else:
            payFee(player, 제주도)
    elif(player.pos == 7):
        if(싱가포르.player == 0 or 싱가포르.player == player):
            buyLand(player, 싱가포르)
        else:
            payFee(player, 싱가포르)
    elif(player.pos == 8):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)
    elif(player.pos == 9):
        if(카이로.player == 0 or 카이로.player == player):
            buyLand(player, 카이로)
        else:
            payFee(player, 카이로)
    elif(player.pos == 10):
        if(이스탄불.player == 0 or 이스탄불.player == player):
            buyLand(player, 이스탄불)
        else:
            payFee(player, 이스탄불)
    elif(player.pos == 11):
        print("무인도입니다. 3턴을 쉽니다.")
        player.I2CSendM(16)
        player.I2CRead()
        player.I2CSend(3,3)
    elif(player.pos == 12):
        if(아테네.player == 0 or 아테네.player == player):
            buyLand(player, 아테네)
        else:
            payFee(player, 아테네)
    elif(player.pos == 13):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)
    elif(player.pos == 14):
        if(코펜하겐.player == 0 or 코펜하겐.player == player):
            buyLand(player, 코펜하겐)
        else:
            payFee(player, 코펜하겐)
    elif(player.pos == 15):
        if(스톡홀름.player == 0 or 스톡홀름.player == player):
            buyLand(player, 스톡홀름)
        else:
            payFee(player, 스톡홀름)
    elif(player.pos == 16):
        if(콩코드여객기.player == 0 or 콩코드여객기.player == player):
            buyTour(player, 콩코드여객기)
        else:
            payFee(player, 콩코드여객기)
    elif(player.pos == 17):
        if(취리히.player == 0 or 취리히.player == player):
            buyLand(player, 취리히)
        else:
            payFee(player, 취리히)
    elif(player.pos == 18):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)
    elif(player.pos == 19):
        if(베를린.player == 0 or 베를린.player == player):
            buyLand(player, 베를린)
        else:
            payFee(player, 베를린)
    elif(player.pos == 20):
        if(몬트리올.player == 0 or 몬트리올.player == player):
            buyLand(player, 몬트리올)
        else:
            payFee(player, 몬트리올)
    elif(player.pos == 21):
        print("사회복지기금 수령처에 도착하셨습니다.")
        player.I2CSendM(17)
        player.I2CRead()
        print("기금을 수령하십시오.")
        player.I2CSendM(18)
        player.I2CRead()
        player.setMon(player.mon + fund)
        fund = 0
        time.sleep(1)
    elif(player.pos == 22):
        if(부에노스아이레스.player == 0 or 부에노스아이레스.player == player):
            buyLand(player, 부에노스아이레스)
        else:
            payFee(player, 부에노스아이레스)
    elif(player.pos == 23):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)
    elif(player.pos == 24):
        if(상파울로.player == 0 or 상파울로.player == player):
            buyLand(player, 상파울로)
        else:
            payFee(player, 상파울로)
    elif(player.pos == 25):
        if(시드니.player == 0 or 시드니.player == player):
            buyLand(player, 시드니)
        else:
            payFee(player, 시드니)
    elif(player.pos == 26):
        if(부산.player == 0 or 부산.player == player):
            buyTour(player, 부산)
        else:
            payFee(player, 부산)
    elif(player.pos == 27):
        if(하와이.player == 0 or 하와이.player == player):
            buyLand(player, 하와이)
        else:
            payFee(player, 하와이)
    elif(player.pos == 28):
        if(리스본.player == 0 or 리스본.player == player):
            buyLand(player, 리스본)
        else:
            payFee(player, 리스본)
    elif(player.pos == 29):
        if(퀸엘리자베스호.player == 0 or 퀸엘리자베스호.player == player):
            buyTour(player, 퀸엘리자베스호)
        else:
            payFee(player, 퀸엘리자베스호)
    elif(player.pos == 30):
        if(마드리드.player == 0 or 마드리드.player == player):
            buyLand(player, 마드리드)
        else:
            payFee(player, 마드리드)
    elif(player.pos == 31):
        print("우주왕복선에 도착하였습니다.")
        player.I2CSendM(19)
        player.I2CRead()
        print("다음 턴에 원하는 곳으로 이동합니다.")
        player.I2CSendM(20)
        player.I2CRead()
    elif(player.pos == 32):
        if(도오쿄오.player == 0 or 도오쿄오.player == player):
            buyLand(player, 도오쿄오)
        else:
            payFee(player, 도오쿄오)
    elif(player.pos == 33):
        if(콜롬비아호.player == 0 or 콜롬비아호.player == player):
            buyTour(player, 콜롬비아호)
        else:
            payFee(player, 콜롬비아호)
    elif(player.pos == 34):
        if(파리.player == 0 or 파리.player == player):
            buyLand(player, 파리)
        else:
            payFee(player, 파리)
    elif(player.pos == 35):
        if(로마.player == 0 or 로마.player == player):
            buyLand(player, 로마)
        else:
            payFee(player, 로마)
    elif(player.pos == 36):
        print("황금열쇠 칸에 도착하셨습니다.")
        player.I2CSendM(15)
        GKNum = GKStack.list.pop()
        gui.gameMessageFlg = GKNum
        while(1):
            if(gui.gameMessageFlg == 0): break;
        if(GKNum != 27 and GKNum != 30 and  GKNum != 31): GKStack.list.insert(0,GKNum)
        GKList(player, GKNum)
    elif(player.pos == 37):
        if(런던.player == 0 or 런던.player == player):
            buyLand(player, 런던)
        else:
            payFee(player, 런던)
    elif(player.pos == 38):
        if(뉴욕.player == 0 or 뉴욕.player == player):
            buyLand(player, 뉴욕)
        else:
            payFee(player, 뉴욕)
    elif(player.pos == 39):
        print("사회복지기금 접수처에 오셨습니다.")
        player.I2CSendM(21)
        player.I2CRead()
        print("15만원을 기부하십시오")
        player.I2CSendM(22)
        player.I2CRead()
        if(player.mon>=150000):
            player.setMon(player.mon - 150000)
            fund += 150000
        else:
            print("돈이 부족합니다. 부동산을 파십시오.")
            player.I2CSendM(23)
            player.I2CRead()
            if(sellEst(player, 150000) == 1):
                fund += player.mon
            else:
                player.setMon(player.mon - 150000)
                fund += 150000
        time.sleep(1)
    elif(player.pos == 40):
        if(서울.player == 0 or 서울.player == player):
            buyTour(player, 서울)
        else:
            payFee(player, 서울)

def buyTour(player, est):
    if(est.player == player):
        print("당신의 관광지입니다.")
        player.I2CSendM(24)
        player.I2CRead()
    else:
        print("관광지를 구매하시겠습니까?")
        player.I2CSendM(25)
        build = player.I2CRead()
        if(build == '1'):
            if(player.mon < est.price):
                print("돈이 부족합니다.")
                player.I2CSendM(26)
                player.I2CRead()
            else:
                player.setMon(player.mon - est.price)
                player.getEst(est)
                print("관광지 구매")
                player.I2CSendM(27)
                player.I2CRead()
        elif(build == '0'):
            print("구매하지 않으셨습니다.")
            player.I2CSendM(28)
            player.I2CRead()

def buyLand(player, est):
    if (sum(est.build)>1):
        print("당신의 땅입니다.")
        player.I2CSendM(24)
        player.I2CRead()
    elif(est.build[0]==0):
        print("대지를 구매하시겠습니까?")
        player.I2CSendM(29)
        build = player.I2CRead()
        if(build == '1'):
            if(player.mon < est.price[0]):
                print("돈이 부족합니다.")
                player.I2CSendM(26)
                player.I2CRead()
            else:
                player.setMon(player.mon - est.price[0])
                player.getEst(est)
                print("대지 구매")
                player.I2CSendM(27)
                player.I2CRead()
        elif(build == '0'):
            print("구매하지 않으셨습니다.")
            player.I2CSendM(28)
            player.I2CRead()

    elif(est.build[0]==1):
        print("어떤 건물을 지으시겠습니까(0 안 지음 1 별장 2 빌딩 3 호텔)")
        player.I2CSendM(30)
        player.I2CRead()
        while(1):
            player.I2CSendM(31)
            build = player.I2CRead()

            if(build == '2'):
                if(player.mon < est.price[1]):
                    print("돈이 부족합니다.")
                    player.I2CSendM(26)
                    player.I2CRead()
                else:
                    player.setMon(player.mon - est.price[1])
                    player.buildEst(est,[1,1,0,0])           
                    print("별장을 지었습니다.")
                    player.I2CSendM(32)
                    player.I2CRead()
                    break
            elif(build == '3'):
                if(player.mon < est.price[2]):
                    print("돈이 부족합니다.")
                    player.I2CSendM(26)
                    player.I2CRead()
                else:
                    player.setMon(player.mon - est.price[2])
                    player.buildEst(est,[1,0,1,0])
                    print("빌딩을 지었습니다.")
                    player.I2CSendM(33)
                    player.I2CRead()
                    break
            elif(build == '4'):
                if(player.mon < est.price[3]):
                    print("돈이 부족합니다.")
                    player.I2CSendM(26)
                    player.I2CRead()
                else:
                    player.setMon(player.mon - est.price[3])
                    player.buildEst(est, [1,0,0,1])
                    print("호텔을 지었습니다.")
                    player.I2CSendM(34)
                    player.I2CRead()
                    break
            elif(build == '1'):
                print("아무것도 짓지 않았습니다.")
                player.I2CSendM(35)
                player.I2CRead()
                break

def playerDead(player):
    global pList
    pList.remove(player)
    print("당신은 죽었습니다. 자본의 힘이 느껴지십니까?")
    player.I2CSendM(36)
    player.I2CSend(4,0)

def calFee(est):                 #요금 계산
    fee = 0                                         
    if(sum(est.build)==1): fee = est.fee[0]
    elif(sum(est.build)>1):
        for a in range(1,4): fee += est.fee[a]*est.build[a]
    return fee

def calPrice(est):              #가격 계산
    price = 0
    if(type(est.build) != list): price = est.price
    else:
        for a in range(0,4): price += est.price[a]*est.build[a]
    return price

def startBonus(player):
    i = 0
    player.I2CSendM(46)
    player.I2CRead()
    print("당신의 땅 중 한곳에 원하는 건물을 지을 수 있습니다.")
    player.I2CSendM(47)
    player.I2CRead()
    landList = []
    for a in player.estList:
        if(type(a.build) == list and sum(a.build) == 1):
            landList.append(a)
    if(len(landList)==0):
        player.I2CSendM(48)
        player.I2CRead()
    else:
        player.I2CSendM(49)
        player.I2CSendM(landList[i].code)
        button = player.I2CRead()
        while(1):
            if('3' == button):
                player.I2CSendM(40)
                buyLand(player,landList[i])
                break
            elif('2' == button):
                if(i == len(landList) - 1):
                    i = 0
                    player.I2CSendM(landList[i].code)
                    button = player.I2CRead()
                else:
                    i += 1
                    player.I2CSendM(landList[i].code)
                    button = player.I2CRead()
            elif('1' == button):
                if(i == 0):
                    i = len(landList) - 1
                    player.I2CSendM(landList[i].code)
                    button = player.I2CRead()
                else:
                    i -= 1
                    player.I2CSendM(landList[i].code)
                    button = player.I2CRead()


def sellEst(player, fee):
    i = 0
    if(len(player.estList)==0):
        playerDead(player)
        return 1
    player.I2CSendM(37)
    if(type(player.estList[i].build) == int):
        price = player.estList[i].price*(1/2)
    else:
        price = calPrice(player.estList[i])*(1/2)
    player.I2CSendM(player.estList[i].code)
    player.I2CSendM((int)(price/1000))
    button = player.I2CRead()
    while(True):
        if(button == '3'):
            if(type(player.estList[i].build) == int):
                player.setMon(player.mon+player.estList[i].price*(1/2))
            else:
                player.setMon(player.mon+calPrice(player.estList[i])*(1/2))
            player.delEst(player.estList[i])
            player.I2CSendM(38)
            player.I2CRead()
            if(player.mon >= fee):
                player.I2CSendM(40)
                break
            if(len(player.estList)==0):
                player.I2CSendM(40)
                playerDead(player)
                return 1
                break
            print("아직 돈이 부족합니다.")
            player.I2CSendM(39)
            player.I2CRead()
            i = 0
            if(type(player.estList[i].build) == int):
                price = player.estList[i].price*(1/2)
            else:
                price = calPrice(player.estList[i])*(1/2)
            player.I2CSendM(player.estList[i].code)
            player.I2CSendM((int)(price/1000))
            button = player.I2CRead()
        elif(button == '1'):
            if(i == len(player.estList) - 1): i = 0
            else: i += 1
            if(type(player.estList[i].build) == int):
                price = player.estList[i].price*(1/2)
            else:
                price = calPrice(player.estList[i])*(1/2)
            player.I2CSendM(player.estList[i].code)
            player.I2CSendM((int)(price/1000))
            button = player.I2CRead()
        elif(button == '2'):
            if(i == 0): i = len(player.estList) - 1
            else: i -= 1
            if(type(player.estList[i].build) == int):
                price = player.estList[i].price*(1/2)
            else:
                price = calPrice(player.estList[i])*(1/2)
            player.I2CSendM(player.estList[i].code)
            player.I2CSendM((int)(price/1000))
            button = player.I2CRead()
                
    

def payFee(player, est):
    if(player.GKList[0] > 0):                        #황금열쇠가 있을 경우
        player.I2CSendM(42)
        player.I2CRead()
        print("황금열쇠를 사용하시겠습니까?")
        player.I2CSendM(41)
        a =  player.I2CRead()
        if(a == '1'):
            player.useGK(0, GKStack)
    else:    
        if(type(est.build) == int):                 #관광지의 경우
            print("요금을 지불하십시오.")
            player.I2CSendM(43)
            player.I2CRead()
            if(player.mon < est.fee):               #돈이 부족할 경우
                print("돈이 부족합니다.")
                print("부동산을 파십시오.")
                player.I2CSendM(23)
                player.I2CRead()
                if(sellEst(player, est.fee) == 1):
                    est.player.setMon(est.player.mon + player.mon)
                else:
                    player.setMon(player.mon - est.fee) 
                    est.player.setMon(est.player.mon + est.fee)
                    player.I2CSendM(13)
                    player.I2CRead()
            
            else:
                player.setMon(player.mon - est.fee)        #돈이 있어 지불
                est.player.setMon(est.player.mon + est.fee)
                print("요금을 지불하였습니다." )
                player.I2CSendM(13)
                player.I2CRead()

        else :                                          #부동산의 경우
            print("요금을 지불하십시오.")
            player.I2CSendM(43)
            player.I2CRead()

            fee = calFee(est)
        
            if(player.mon < fee):                           #돈이 부족할 경우
                print("돈이 부족합니다.")
                print("부동산을 파십시오.")
                player.I2CSendM(23)
                player.I2CRead()
                if(sellEst(player, fee) == 1):
                    est.player.setMon(est.player.mon + player.mon)
                else:
                    player.setMon(player.mon - fee) 
                    est.player.setMon(est.player.mon + fee)
                    print("요금을 지불하였습니다." )
                    player.I2CSendM(13)
                    player.I2CRead()
            
            else:
                player.setMon(player.mon - fee)        #돈이 있어 지불
                est.player.setMon(est.player.mon + fee)
                print("요금을 지불하였습니다." )
                player.I2CSendM(13)
                player.I2CRead()



def GKList(player, number):
    global GKStack
    global fund
    if(number == 1):                            #항공여행
        print('"콩코드여객기"를 타고 "타이페이"로 갑니다.')
        time.sleep(2)
        if(player.pos < 16):
            player.goFow(16-player.pos, 0.1)
        elif(player.pos > 16):
            player.goFow(56-player.pos, 0.1)
        landOrder(player)
        player.goFow(42-player.pos, 0.1)
        print('"타이페이"에 도착했습니다.')
        landOrder(player)

    elif(number == 2):                          #관광여행 홍콩
        print('"퀸엘리자베스호"를 타고 "홍콩"로 갑니다.')
        time.sleep(2)
        if(player.pos < 29):
            player.goFow(29-player.pos, 0.1)
        elif(player.pos > 29):
            player.goFow(69-player.pos, 0.1)
        landOrder(player)
        player.goFow(44-player.pos, 0.1)
        print('"홍콩"에 도착했습니다.')
        landOrder(player)

    elif(number == 3):                          #고속도로
        print("출발지로 바로 이동합니다.")             
        time.sleep(2)
        player.goFow(41-player.pos, 0.1)
        print("출발지에 도착했습니다.")
        landOrder(player)

    elif(number == 4):                          #관광여행 서울       
        print('"서울"로 출발합니다.')
        time.sleep(2)
        player.goFow(40-player.pos, 0.1)
        print('"서울"에 도착했습니다.')
        landOrder(player)

    elif(number == 5):                          #관광여행 부산
        print('"부산"으로 출발합니다.')
        time.sleep(2)
        if(player.pos < 26):
            player.goFow(26-player.pos, 0.1)
        elif(player.pos > 26):
            player.goFow(66-player.pos, 0.1)
        landOrder(player)
        print('"부산"에 도착했습니다.')

    elif(number == 6):                          #관광여행 제주도
        print('"제주도"로 출발합니다.')
        time.sleep(2)
        if(player.pos < 6):
            player.goFow(6-player.pos, 0.1)
        elif(player.pos > 6):
            player.goFow(46-player.pos, 0.1)
        landOrder(player)
        print('"제주도"에 도착했습니다.')

    elif(number == 7):                          #뒤로 2칸
        print("뒤로 2칸 갑니다.")
        time.sleep(2)
        player.goBack(2, 0.4)
        landOrder(player)
        
    elif(number == 8):                          #뒤로 3칸
        print("뒤로 3칸 갑니다.")
        time.sleep(2)
        player.goBack(3, 0.4)
        landOrder(player)

    elif(number == 9):                          #무인도로 가시오
        print("무인도로 갑니다. 님은 월급도 못받음 ㅉㅉ")
        time.sleep(2)
        player.setPos(11)
        landOrder(player)

    elif(number == 10):                         #사회복지기금
        print("사회복지기금 수령처로 이동합니다.")
        time.sleep(2)
        if(player.pos < 21):
            player.goFow(21-player.pos, 0.1)
        elif(player.pos > 21):
            player.goFow(61-player.pos, 0.1)
        print("사회복지기금 수령처로 이동했습니다.")
        landOrder(player)

    elif(number == 11):                         #세계일주
        print("세계일주를 합니다.")
        time.sleep(2)
        player.goFow(40, 0.1)
        player.setMon(player.mon + fund)
        fund = 0
        player.I2CSendM(18)
        player.I2CRead()

    elif(number == 12 or number == 13):         #우주여행
        print("우주여행 승강장으로 바로 이동합니다.")
        time.sleep(2)
        if(player.pos < 31):
            player.goFow(31-player.pos, 0.1)
        elif(player.pos > 31):
            player.goFow(71-player.pos, 0.1)
        player.spaceGKFlag = 1
        landOrder(player)
        
    elif(number == 14):                         #노벨평화상
        print("노벨 평화상을 받았습니다.")
        player.setMon(player.mon + 300000)
        time.sleep(2)
    
    elif(number == 15):                         #노후 연금
        print("노후 연금을 받았습니다.")
        player.setMon(player.mon + 50000)
        time.sleep(1)

    elif(number == 16):                         #복권 당첨
        print("복권에 당첨되었습니다.")
        player.setMon(player.mon + 200000)
        time.sleep(1)

    elif(number == 17):                         #생일 축하
        print("생일 축하금을 받습니다.")
        global pList
        mon = 0
        for p in pList:
            if(player != p):
                if(p.mon >= 1000):
                    p.setMon(player.mon - 1000)
                    mon += 1000
        player.setMon(player.mon + 3000)        
        time.sleep(1)

    elif(number == 18):                         #자동차 경주 우승금
        print("자동차 경주 우승금을 받았습니다.")
        player.setMon(player.mon + 100000)
        time.sleep(1)

    elif(number == 19):                         #장학금
        print("장학금을 받았습니다.")
        player.setMon(player.mon + 190000)
        time.sleep(1)

    elif(number == 20):                         #건물 방범비
        print("건물 방범비를 냅니다.")
        time.sleep(1)
        fee = 0
        for est in player.estList:
            if(type(est.build) != int ):
                fee += est.build[1] * 10000
                fee += est.build[2] * 30000
                fee += est.build[3] * 50000
        print("총비용은 {}입니다." .format(fee))
        time.sleep(1)
        if(player.mon<fee):
            print("부동산을 팝니다.")
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")

    elif(number == 21):                         #건물 수리비
        print("건물 수리비를 냅니다.")
        time.sleep(1)
        fee = 0
        for est in player.estList:
            if(type(est.build) != int ):
                fee += est.build[1] * 30000
                fee += est.build[2] * 60000
                fee += est.build[3] * 100000
        print("총비용은 {}입니다." .format(fee))
        time.sleep(1)
        if(player.mon<fee):
            print("부동산을 팝니다.")
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")

    elif(number == 22):                         #정기 종합 소득세
        print("건물 방범비를 냅니다.")
        time.sleep(1)
        fee = 0
        for est in player.estList:
            if(type(est.build) != int ):
                fee += est.build[1] * 50000
                fee += est.build[2] * 100000
                fee += est.build[3] * 150000
        print("총비용은 {}입니다." .format(fee))
        time.sleep(1)
        if(player.mon<fee):
            print("부동산을 팝니다.")
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")

    elif(number == 23):                         #과속 운전
        print("과속 운전 벌금을 냅니다.")
        fee = 50000
        if(player.mon<fee):
            print("부동산을 팝니다.")
            player.I2CSendM(23)
            player.I2CRead()
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
                player.I2CSendM(13)
                player.I2CRead()
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")
            player.I2CSendM(13)
            player.I2CRead()
        
    elif(number == 24):                         #병원비
        print("병원비를 냅니다.")
        fee = 50000
        if(player.mon<fee):
            print("부동산을 팝니다.")
            player.I2CSendM(23)
            player.I2CRead()
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
                player.I2CSendM(13)
                player.I2CRead()
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")
            player.I2CSendM(13)
            player.I2CRead()

    elif(number == 25):                         #해외 유학
        print("해외유학비를 냅니다.")
        fee = 50000
        if(player.mon<fee):
            print("부동산을 팝니다.")
            player.I2CSendM(23)
            player.I2CRead()
            if(sellEst(player, fee) != 1):
                player.setMon(player.mon - fee)
                print("비용을 지불했습니다.")
                player.I2CSendM(13)
                player.I2CRead()
        else:
            player.setMon(player.mon - fee)
            print("비용을 지불했습니다.")
            player.I2CSendM(13)
            player.I2CRead()

    elif(number == 26):                         #무전기
        print("무전기를 받았습니다.")
        player.getGK(1)
        player.I2CSendM(45)
        ans = player.I2CRead()
        if(ans=='1'): player.sellRadio(GKStack)
        

    elif(number == 27 or number == 28):         #반액대매출
        print("가장 비싼 땅을 반값에 파십시오.")
        time.sleep(1)
        fee = 0
        estList = 0
        if(len(player.estList)==0):
            print("팔 자산이 없습니다.")
            player.I2CSendM(44)
            player.I2CRead()
        else:
            for est in player.estList:
                if(type(est.build) != int ):
                    if(est.price[0] > fee):
                        fee = est.price[0]
                        estList = player.estList.index(est)
                else:
                    if(est.price > fee):
                        fee = est.price
                        estList = player.estList.index(est)
            if(type(player.estList[estList].build) != int ):
                player.setMon(player.mon + (1/2)*calPrice(player.estList[estList]))
            else:
                player.setMon(player.mon + (1/2)*player.estList[estList].price)
            print("{}을 팔았습니다." .format(player.estList[estList].name))
            player.I2CSendM(38)
            player.I2CRead()
            player.delEst(player.estList[estList])

    elif(number == 29 or number == 30):
        print("우대권을 받았습니다.")
        player.getGK(0)
           









        
