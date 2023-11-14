2022-4-21
新增内容：加入转向速度限制函数，仅对遥控器下发的角度进行了限制，上位机下发的角度未给限制
调试遇到的问题及注意事项：
（1）调试过程中禁止在车辆运动时在电脑终端ctrl+c退出程序，否则下一次直接运行程序的时候会出现部分轮胎驱动电机失控现象
（2）出现上电之后左后轮驱动电机不工作，用遥控器重新使能无法解决，重新上电开机可以解决，暂时没有找到问题所在。

2022-4-22
新增内容：让转向速度限制程序对上位机下发的角度也有效

2022-10-26
CH0：左摇杆前后：前后速度
CH1：右摇杆左右：左右转向
CH2：开关SA：速度档位
CH3：开关SC：使能/转向使能/运动使能
CH4：开关SB：遥控器控制/程序控制
CH5：开关SD：转向模式
CH6：左摇杆左右：左右侧偏
CH7：右摇杆前后：
CH8：开关SE（左上）：速度控制/力矩模式
CH9：开关SG（右上）：转向模式3开关
CH10：拨杆LS（左手食指位置）
CH11：拨杆RS（右手食指位置，带回弹）：原地旋转模式开关

编译命令：
/home/bit/software/CLion-2019.3.6/clion-2019.3.6/bin/cmake/linux/bin/cmake --build /home/bit/program_by_lhz/car_8drv_202306/cmakes --target Car_8drv_unstable -- -j 6
复制命令：
sudo scp -r Car_8drv_unstable1 root@192.168.3.103:/home/
挂载命令;
mount -t nfs -o nolock 192.168.3.115:/home/bit/program_by_lhz/car_8drv_202306/cmakes/ ~/mnt
