import socket
import argparse
import sys
import os
import time

HOST = '127.0.0.1'


def Parse2():
    parser = argparse.ArgumentParser()
   
    parser.add_argument('--Redirectory', '-d', required = True, type=str)
    parser.add_argument('--Port_number', '-p', required = True, type=int)
    calling_arg = parser.parse_args()
    if calling_arg.Port_number < 0 or calling_arg.Port_number > 65535:
        print("Error Message", file=sys.stderr) 
    return calling_arg

def Parse():

    create_parse = argparse.ArgumentParser()
    create_parse.add_argument('Port_number', type=int)
    create_parse.add_argument('Redirectory', type=str)
    calling_arg = create_parse.parse_args()
    if calling_arg.Port_number < 0 or calling_arg.Port_number > 65535:
        print("Error Message", file=sys.stderr) 
    return calling_arg

args = Parse2()

def GetStatusLine():
    Status_line = "HTTP/1.1 200 OK\r\n"
    return Status_line

def ContentLength(fileName):
    # fileName += '/HelloWorld.html'
    Content_Length = "Content-Length: "
    size = os.path.getsize(fileName)
    Content_Length = Content_Length + str(size) + "\r\n"
    return Content_Length

def LastModified2(fileName):
    Last_Modified = os.path.getmtime(fileName)
    changeTime = time.gmtime(Last_Modified)
    # print(changeTime)
    checking_day = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
    checking_month = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
    weekday = checking_day[changeTime.tm_wday]
    day = changeTime.tm_mday
    month = checking_month[changeTime.tm_mon - 1]
    year = changeTime.tm_year
    hour = changeTime.tm_hour
    minute = changeTime.tm_min
    second = changeTime.tm_sec
    finalDate = checking_day[changeTime.tm_wday]
    date_str = "%s, %02d %s %04d %02d:%02d:%02d GMT" % (weekday, day, month, year, hour, minute, second)
    change_Time = "Last-Modified: "
    change_Time = change_Time + str(date_str) + "\r\n"
    return change_Time

def ContentCheck(filename):
    # filename += '/HelloWorld.html'
    with open(filename, 'rb') as f:
        data = f.read()
    print(data.decode())


def Date():
    Date = time.time()
    date_final = time.gmtime(Date)
    # print(date_final)
    checking_day = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
    checking_month = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
    weekday = checking_day[date_final.tm_wday]
    day = date_final.tm_mday
    month = checking_month[date_final.tm_mon - 1]
    year = date_final.tm_year
    hour = date_final.tm_hour
    minute = date_final.tm_min
    second = date_final.tm_sec
    finalDate = checking_day[date_final.tm_wday]
    date_str = "%s, %02d %s %04d %02d:%02d:%02d GMT" % (weekday, day, month, year, hour, minute, second)

    final_Date = "Date: "
    final_Date = final_Date + str(date_str) + "\r\n"
    return final_Date

def ContentType(fileName):
    # fileName += '/HelloWorld.html'
    split_list = fileName.split(".")
    extension = split_list[len(split_list)-1]
    Content_type = "Content-Type: "
    Content_type = Content_type + "text/" + str(extension) + "\r\n"
    return Content_type


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, args.Port_number))
    s.listen(args.Port_number)


    print("Server is listening on http://%s:%s" % ((HOST), args.Port_number))

    while True:
        conn, addr = s.accept()
        request_data = conn.recv(1024).decode()
        # print(request_data)
        request_lines = request_data.split('\r\n')
        request_method, request_path, _ = request_lines[0].split(' ')
        # file_name = request_path.split('/')[-1]
        if request_method == 'GET':
            print("get")
            try:
                temp = args.Redirectory
                status = GetStatusLine()
                args.Redirectory += request_path
                # print(args.Redirectory)
                last_Modified = LastModified2(args.Redirectory)
                date_arg = Date()
                content_len = ContentLength(args.Redirectory)
                content_type = ContentType(args.Redirectory)
                response_body = status + content_len + last_Modified + date_arg + content_type + "\r\n"
                with open(args.Redirectory, 'rb') as f:
                    data = f.read()
                    response_body += data.decode()
            except FileNotFoundError:
                response_body = 'HTTP/1.1 404 Not Found\r\n\r\n'
            conn.sendall(response_body.encode())
            args.Redirectory = temp
        conn.close()