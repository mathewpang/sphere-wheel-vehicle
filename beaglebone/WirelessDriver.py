#!/usr/bin/python

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
from subprocess import Popen, PIPE, STDOUT

class WirelessDriver(BaseHTTPRequestHandler):

    def __init__(self, *args):
        #self.p = Popen(['./VehicleDriver'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        #self.a = 1
        BaseHTTPRequestHandler.__init__(self, *args)

    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        f = open("index.html", "r")
        self.wfile.write(f.read())


    def do_POST(self):
        self._set_headers()
        self.data_string = self.rfile.read(int(self.headers['Content-Length']))
        print "POST!"
        data = self.data_string.split('=')
        method = data[0]
        value = data[1]
        print('%s' % value)
        #self.p.stdin.write('%s\n' % value)
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
