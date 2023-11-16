import numpy as np
from scipy import signal

def judge_standard(G,H):
    print('请保持心情平静，正常持握方向盘，等待系统采集您的正常状态生理信号')
    gl = G[0:299]
    gl_array = np.array(gl)
    hl = H[0:299]
    hl_array = np.array(hl)
    cnt_arraygl = np.where(gl_array, 0, 1)
    cnt_arrayhl = np.where(hl_array, 0, 1)
    num_gl = np.sum(cnt_arraygl)
    num_hl = np.sum(cnt_arrayhl)
    if num_gl > 30 & num_hl > 30:
        print("请将双手放到标准持握位置，基态信息采集对您很重要")
        G.clear()
        H.clear()
    elif num_gl > 20 & num_hl <=20:
        print("请不要单手持握方向盘，请将左手放在方向盘标准持握处，基态信息采集对您很重要")
        G.clear()
        H.clear()
    elif num_gl <= 20 & num_hl > 20:
        print("请不要单手持握方向盘，请将右手放在方向盘标准持握处，基态信息采集对您很重要")
        G.clear()
        H.clear()
    else:
        b1, a1 = signal.butter(4, 0.9, 'lowpass')
        b2, a2 = signal.butter(2, 0.9, 'lowpass')
        filt_gl = signal.filtfilt(b1, a1, gl_array)
        filt_hl = signal.filtfilt(b2, a2, hl_array)
        # 判据标准
        GL_mean = np.mean(filt_gl)
        HL_mean = np.mean(filt_hl)   # 平均值
        GL_max_min = np.ptp(filt_gl)
        HL_max_min = np.ptp(filt_hl)  # 最大最小值之比
        GL_std = np.std(filt_gl)
        HL_std = np.std(filt_hl)  # 方差
        GL_diff1 = np.diff(filt_gl)
        HL_diff1 = np.diff(filt_hl)
        GL_diff2 = np.diff(GL_diff1)
        HL_diff2 = np.diff(HL_diff1)  # 一阶和二阶差分用于描写信号的速度和加速度
        GL_diff1_max_min = np.ptp(GL_diff1)
        HL_diff1_max_min = np.ptp(HL_diff1)
        GL_diff1_std = np.std(GL_diff1)
        HL_diff1_std = np.std(HL_diff1)
        GL_diff2_max_min = np.ptp(GL_diff2)
        HL_diff2_max_min = np.ptp(HL_diff2)
        GL_diff2_std = np.std(GL_diff2)
        HL_diff2_std = np.std(HL_diff2)
        A=[HL_mean,HL_max_min,HL_std]
        B=[GL_diff1_max_min,GL_diff1_std,GL_diff2_max_min,GL_diff2_std,GL_mean,GL_max_min]
        print("路易平安，感谢您的配合，采样已结束")
    return A,B,a1,a2,b1,b2,HL_std

def judge_process(G,H,A,B,a1,a2,b1,b2,HL_std):
    s = 2
    g1 = G[0:299]
    G1 = np.array(g1)
    h1= H[0:299]
    H1= np.array(h1)
    cnt_arrayg=np.where(G1<380, 0, 1)
    cnt_arrayh=np.where(H1, 0, 1)
    numg = np.sum(cnt_arrayg)
    numh = np.sum(cnt_arrayh)
    if numg>=20 or numh>=30:
        print("路易平安提醒您，把握好方向盘，才能把握住路面安全哦")
        G.clear()
        H.clear()
        s = 3
    else:
        #滤波
        filtG = signal.filtfilt(b1,a1,G1)
        filtH = signal.filtfilt(b2,a2,H1)
        #判据标准
        G_mean = np.mean(filtG)
        H_mean = np.mean(filtH)
        G_max_min = np.ptp(filtG)
        H_max_min = np.ptp(filtH)
        G_std = np.std(filtG)
        H_std = np.std(filtH)
        G_diff1 = np.diff(filtG)
        H_diff1 = np.diff(filtH)
        G_diff2 = np.diff(G_diff1)
        H_diff2 = np.diff(H_diff1)
        G_diff1_max_min = np.ptp(G_diff1)
        H_diff1_max_min = np.ptp(H_diff1)
        G_diff1_std = np.std(G_diff1)
        H_diff1_std = np.std(H_diff1)
        G_diff2_max_min = np.ptp(G_diff2)
        H_diff2_max_min = np.ptp(H_diff2)
        G_diff2_std = np.std(G_diff2)
        H_diff2_std = np.std(H_diff2)
        C=[H_mean,H_max_min,HL_std]
        D=[G_diff1_max_min,G_diff1_std,G_diff2_max_min,G_diff2_std,G_mean,G_max_min]
        if (C[0]>1.5*A[0])or(C[1]>2*A[1])or(C[2]>2*A[2]):
            print("路易平安提醒您,开车时可不能心烦气躁哦")
            s = 1
        if  (B[0]>1.5*D[0])&(B[1]>3*D[1])&(B[2]>3*D[2])&(B[3]>D[3])or((B[4]>1.2*D[4])&(D[5]>1.5*B[5])):
            print("路易平安提醒您，路上心平气和开车，才能平平安安回家")
            s = 1
        else:
            print("normal")
            s = 0
        return s
