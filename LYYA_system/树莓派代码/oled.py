from luma.core.interface.serial import i2c, spi
from luma.core.render import canvas
from luma.oled.device import ssd1306, ssd1327, ssd1331, sh1106
import time

serial = i2c(port=1, address=0x3C)
device = ssd1306(serial)
def text_clear():
    with canvas(device) as draw:
        draw.rectangle((1,1,128,30), fill="black")

def loading(G,s):
        # 调用显示函数
    with canvas(device) as draw:
        draw.rectangle(device.bounding_box, outline="white", fill="black")
        draw.rectangle((25, 30, 100, 40), outline="white")
        draw.rectangle((25, 30, int(25 + len(G)/4), 40), fill="white")
        if s == 0:
            draw.text((45, 15), "mild", fill="white")
        if s == 1:
            draw.text((45, 15), "angry", fill="white")
        if s == 3:
            draw.text((45, 15), "error", fill="white")
        if s == 2:
            draw.text((40, 15), "loading", fill="white")


        
    
