import requests
from time import sleep

def run():
    print('Wird ausgeführt...')
    # einschalt
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=60&SX=64&IX=113&T=1')
    sleep(2,5)
    # rot lauf
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=255&G=0&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=60&SX=203&IX=246&T=1')
    sleep(24)
    # grün
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=255&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    sleep(10)
    # weiß = requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    # sleep(1)
    #spots
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=15&S2=299&GP=7&SP=30&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    sleep(30)
    # aus
    requests.get('http://wled-1.local/win&T=0')
    print('fertig')

def run_reset():
    print('reset')
    # reset
    requests.get('http://wled-1.local/win&T=0')
    print('Wird ausgeführt...')
    # einschalt
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=60&SX=64&IX=113&T=1')
    sleep(2,5)
    # rot lauf
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=255&G=0&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=60&SX=203&IX=246&T=1')
    sleep(24)
    # grün
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=255&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    sleep(10)
    # weiß = requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    # sleep(1)
    #spots
    requests.get('http://wled-1.local/winSM=0&SS=0&SV=2&S=15&S2=299&GP=7&SP=30&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1')
    sleep(30)
    # aus
    requests.get('http://wled-1.local/win&T=0')
    print('fertig')

ans = input('Operation:\n:')
if ans == 'run':
    print('Wird ausgeführt...')
    run()
elif ans == 'rrun':
    print('reset\nWird ausgeführt')
    run_reset()
else:
    print('Ungültige Eingabe')
