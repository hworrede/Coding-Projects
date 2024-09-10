# Hagos Worrede
# CSE 150 
# Part 1

import argparse
import sys
import os
import time

def Parse():

    create_parse = argparse.ArgumentParser()

    create_parse.add_argument('Port_number', type=int)
    create_parse.add_argument('Redirectory', type=str)

    calling_arg = create_parse.parse_args()

    if calling_arg.Port_number < 0 or calling_arg.Port_number > 65535:

        print("Error Message", file=sys.stderr) 

    return calling_arg

args = Parse()

###########################
def GetStatusLine():
    Status_line = "HTTP/1.1 200 OK\r\n"
    return Status_line
###########################


###############
def ContentLength(fileName):
    fileName += '/HelloWorld.html'
    Content_Length = "Content-Length: "
    size = os.path.getsize(fileName)
    Content_Length = Content_Length + str(size) + "\r\n"
    return Content_Length
################


# ##########################
# def Date():
#     Date = time.time()
#     date_final = time.gmtime(Date)
#     checking_day = ['Mon', 'Tues', 'Wed', 'Thurs', 'Fri', 'Sat', 'Sun']
#     final_time = checking_day[date_final.tm_wday]

#     last_date = time.strftime(f"{final_time}, %B %d, %Y %H:%M:%S GMT", date_final)

#     final_Date = "Date: "
#     final_Date = final_Date + str(last_date) + "\r\n"
#     return final_Date
# ###########################


##########################
def Date():
    Date = time.time()
    date_final = time.gmtime(Date)
    print(date_final)
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
###########################

def LastModified2(fileName):
    Last_Modified = os.path.getmtime(fileName)
    changeTime = time.gmtime(Last_Modified)
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

# #########################
# def LastModified(fileName):

#     Last_Modified = os.path.getmtime(fileName)
# # modified = time.localtime(Last_Modified)
# # modified2 = time.strftime(str(Last_Modified))

#     changeTime = time.gmtime(Last_Modified)
    
#     checking_day = ['Mon', 'Tues', 'Wed', 'Thurs', 'Fri', 'Sat', 'Sun']
#     finalDate = checking_day[changeTime.tm_wday]
    
#     date_str = time.strftime(f"{finalDate}, %B %d, %Y %H:%M:%S GMT", changeTime)

#     change_Time = "Last-Modified: "
#     change_Time = change_Time + str(date_str) + "\r\n"
#     return change_Time
# ########################
#########################
def ContentCheck(filename):
    filename += '/HelloWorld.html'
    with open(filename, 'rb') as f:
        data = f.read()
    print(data.decode())
        
#########################


###########################
def ContentType(fileName):
    fileName += '/HelloWorld.html'
    split_list = fileName.split(".")
    extension = split_list[len(split_list)-1]
    Content_type = "Content-Type: "
    Content_type = Content_type + "text/" + str(extension) + "\r\n"
    # Content_type += 'text/html'
    return Content_type
###########################


parse_arguments = Parse()
status = GetStatusLine()
last_Modified2 = LastModified2(args.Redirectory)
date_arg = Date()
content_len = ContentLength(args.Redirectory)
content_type = ContentType(args.Redirectory)

GetAll = (status + str(content_len) + str(last_Modified2) + str(date_arg) + content_type + "\r\n")

print(GetAll)
ContentCheck(args.Redirectory)