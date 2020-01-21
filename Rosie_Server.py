# -*- coding: utf-8 -*-
"""
@author: John Entrieri

Sensor Driver API
"""

#import json
import flask

#Define Flask API Application
app = flask.Flask(__name__)

laundryData = {
    "X Accelerometer" : 0,
    "Y Accelerometer" : 0,
    "Z Accelerometer" : 0,
    "X Gyro" : 0,
    "Y Gyro" : 0,
    "Z Gyro" : 0,
    "Temperature" : 0,
}

@app.route('/laundry/', methods=['POST'])
def postData():

    content = flask.request.json

    laundryData["X Accelerometer"] = content['AccX']
    laundryData["Y Accelerometer"] = content['AccY']
    laundryData["Z Accelerometer"] = content['AccZ']
    laundryData["X Gyro"] = content['GyX']
    laundryData["Y Gyro"] = content['GyY']
    laundryData["Z Gyro"] = content['GyZ']
    laundryData["Temperature"] = content['Temp']
                              
    responseDict = { "response" : "OK" }

    response = flask.jsonify(responseDict)
    response.headers.add('Access-Control-Allow-Origin', '*')    
    
    return response

@app.route('/laundry/', methods=['GET'])
def getData():
                              
    responseDict = laundryData

    response = flask.jsonify(responseDict)
    response.headers.add('Access-Control-Allow-Origin', '*')    
    
    return response

if __name__ == '__main__':    
    app.run(debug=True,host='IP_ADDRESS',port=PORT)
