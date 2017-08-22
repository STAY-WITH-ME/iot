import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev

GPIO.setmode(GPIO.BCM)

pipes = [[0xe8, 0xe8, 0xe8, 0xe8, 0xe8], [0xe8, 0xe8, 0xe8, 0xe8, 0xe7]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 22)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setDataRate(RF24.BR_1MBPS)
radio.setPALevel(RF24.PA_MIN)
radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openWritingPipe(pipes[1])
radio.printDetails()

msg = list("GETSTRING")

while len(msg) < 32:
    msg.append(0)

activeTime=0
while True:
    start = time.time()
    #while times of sending packages
    radio.write(msg)
    print("Sent --> {}".format(msg))

    receivedMessage = []
    radio.read(receivedMessage, radio.getDynamicPayloadSize())
    print("Received: {}".format(receivedMessage))

    end=time.time()
    activeTime=activeTime+end-start
    print(activeTime)
    if activeTime>=20:
       print("sleep starts!!!")
       time.sleep(10)
       print("sleep ends!!!!!")
       activeTime=0
