from socket import *

def http_req (server, path):
    s = socket(AF_INET, SOCK_STREAM)

    adr = (gethostbyname(server), 8000)

    s.connect(adr)

    rqst = "GET " + path + " HTTP/1.1\r\n"
    rqst += "Content-Type: text/plain\r\n"
    rqst += "Transfer-Encoding: chunked\r\n\r\n"
    rqst += "26\r\n"
    rqst += "Voici les donnees du premier morceau\r\n\r\n"
    rqst += "1C\r\n"
    rqst += "et voici un second morceau\r\n\r\n"
    rqst += "20\r\n"
    rqst += "et voici deux derniers morceaux \r\n"
    rqst += "13\r\n"
    rqst += "sans saut de ligne\n\r\n"
    rqst += "0\r\n"
    rqst += "\r\n"

    s.send(rqst)

    resp = s.recv(4096)
    while resp != "":
        print(resp)
        resp = s.recv(4096)

http_req("localhost", "/")