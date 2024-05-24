from flask import Flask, request
import csv

app = Flask(__name__)

@app.route('/', methods=['POST'])
def receive_data():
    data = request.get_json()
    print(data)
    
    with open('data.csv', 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(data.values())
    
    return 'Data received'

if __name__ == '__main__':
    app.run(host='192.168.11.104', port=5000)