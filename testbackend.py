import requests
import time 

url = 'http://192.168.11.104:5000'  # Replace with the appropriate URL

data = {
    'message': 'Hello, backend!'
}
if __name__ == '__main__':
    while True:
        response = requests.post(url, json=data)
        if response.status_code == 200:
            print('String sent successfully!')
        else:
            print('Failed to send string.')
        time.sleep(5)
   