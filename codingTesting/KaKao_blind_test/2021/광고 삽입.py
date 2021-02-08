'''
https://programmers.co.kr/learn/courses/30/lessons/72414
광고 삽입
'''

def time_to_sec(time):
    temp = list(map(int, time.split(sep=':')))
    temp = temp[0]*3600 + temp[1]*60 + temp[2]
    return temp 

def solution(play_time, adv_time, logs):
    answer = ''
    viewer_array = [0 for _ in range(360000)]
    
    play_time = time_to_sec(play_time)
    adv_time = time_to_sec(adv_time)
    
    for log in logs:
        temp = log.split(sep='-')
        temp1 = time_to_sec(temp[0])
        temp2 = time_to_sec(temp[1])
        
        viewer_array[temp1] += 1
        viewer_array[temp2] -= 1
        
    for i in range(1, play_time):
        viewer_array[i] += viewer_array[i - 1]
    
    right_time = [0,0]
    for i in range(adv_time):
        right_time[1] += viewer_array[i]
    
    temp_time = right_time[1]
    for i in range(play_time - adv_time):
        temp_time = temp_time - viewer_array[i] + viewer_array[i + adv_time]
        
        if temp_time > right_time[1]:
            right_time[0] = i + 1
            right_time[1] = temp_time
            
    answer = f'{right_time[0]//3600:02d}:{(right_time[0]//60)%60:02d}:{right_time[0]%60:02d}'
    
    return answer
