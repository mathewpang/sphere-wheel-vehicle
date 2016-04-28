#!/usr/bin/python

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
from subprocess import Popen, PIPE, STDOUT

class WirelessDriver(BaseHTTPRequestHandler):

    def __init__(self, *args):
        self.p = Popen(['./VehicleDriver'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        #self.a = 1
        BaseHTTPRequestHandler.__init__(self, *args)

    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        f = open("index.html", "r")
        text = f.read()
        text = text + "Distance Sensor: 34"
        self.wfile.write(text)


    def do_POST(self):
        self._set_headers()
        self.data_string = self.rfile.read(int(self.headers['Content-Length']))
        print "POST!"
        data2 = self.data_string.split('&')
        for data in data2:
            data1 = data.split('=')
            method = data1[0]
            value = data1[1]
            print(data)
            print(value)
            if value.isdigit():
                if method == "Radius":
                    if int(value) < 0 or int(value) > 127:
                        print('Radius out of Range!')
                    else:
                        print('Sending values!')
                        self.p.stdin.write(data + '\n')
                    
                if method == "Angle":
                    if(int(value) < 0 or int(value) > 360):
                        print('Angle out of Range!')
                    else:
                        print('Sending values!')            
        f = open("index.html", "r")
        self.wfile.write(f.read())   
        self.end_headers()


def run(server_class=HTTPServer, handler_class=WirelessDriver, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    #p = Popen(['./VehicleDriver'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    #a = 1
    print 'Start Server'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

if len(argv) == 2:
    run(port=int(argv[1]))
else:
    run()
