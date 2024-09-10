"""
This file defines actions, i.e. functions the URLs are mapped into
The @action(path) decorator exposed the function at URL:

    http://127.0.0.1:8000/{app_name}/{path}

If app_name == '_default' then simply

    http://127.0.0.1:8000/{path}

If path == 'index' it can be omitted:

    http://127.0.0.1:8000/

The path follows the bottlepy syntax.

@action.uses('generic.html')  indicates that the action uses the generic.html template
@action.uses(session)         indicates that the action uses the session
@action.uses(db)              indicates that the action uses the db
@action.uses(T)               indicates that the action uses the i18n & pluralization
@action.uses(auth.user)       indicates that the action requires a logged in user
@action.uses(auth)            indicates that the action requires the auth object

session, db, T, auth, and tempates are examples of Fixtures.
Warning: Fixtures MUST be declared with @action.uses({fixtures}) else your app will result in undefined behavior
"""

import datetime
import random

from py4web import action, request, abort, redirect, URL
from yatl.helpers import A
from .common import db, session, T, cache, auth, logger, authenticated, unauthenticated, flash
from py4web.utils.url_signer import URLSigner
from .models import get_username

url_signer = URLSigner(session)

# Some constants.
MAX_RETURNED_USERS = 20 # Our searches do not return more than 20 users.
MAX_RESULTS = 20 # Maximum number of returned meows. 

@action('index')
@action.uses('index.html', db, auth.user, url_signer)
def index():
    return dict(
        # COMPLETE: return here any signed URLs you need.
        get_feed_url = URL('makeFullArea', signer=url_signer).replace('/meow/', '../'),
#each has its own function that will be important 
        post_meow_url = URL('makemeow', signer=url_signer).replace('/meow/', '../'),
        

#each has its own function that will be important 
        get_users_url = URL('findUser', signer=url_signer).replace('/meow/', '../'),
        #each has its own function that will be important 
        set_follow_url = URL('makeFollow', signer=url_signer).replace('/meow/', '../'),
    #each has its own function that will be important 
        set_reply_url = URL('makeReply', signer=url_signer).replace('/meow/', '../')
    )



@action("findUser")
@action.uses(db, auth.user)
def findUser():
    #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
    # Returns users excluding self.
    users = db(db.auth_user.get("username") != auth.current_user.get("username")).select().as_list()
    return dict(users=users)



@action("makeFullArea", method="GET")
@action.uses(db, auth.user)
def makeFullArea():

    # below will be split into different sections as for the different feeds
    #each will have its on corresponding numbers

    
    makingResponses = request.query.get('reply_source')


    changingFeeds = int(request.query['feed_type'])


    if makingResponses != None:
        makingResponses = int(makingResponses)
#we initialize making a list for the below part 
    makingList_fit = 0
#thsi woild be the meow part for the section 
    meows = []

#def set_follow():
    #user_id = request.json.get('user_id')

    #if user_id is None:
        #return "Invalid user ID"
#checking the valid users
    #original_ID = auth.current_user.get('id')

    #originaluser = db((db.checkingNextFollow.user_id == user_id) & (db.checkingNextFollow.follower_id == original_ID)).select().first()
    #if originaluser:
        #db(db.checkingNextFollow.id == originaluser.id).delete()
        #return "Unfollowed user successfully"
    #else:

    def checkFinalMeow(column):
        makeAChangeToPlayer = db(db.auth_user.id == column['author']).select()[0]


        if makeAChangeToPlayer:

            column['username'] = makeAChangeToPlayer['username']
            column['timestamp'] = column['timestamp'].isoformat()
        
            checkingOther_list = db(db.findNextResponse.findMain == column['id']).select()
            column['replies'] = len(checkingOther_list)

            return column
        return None
    
     # then we get to my feed below for the final product 
   

    if changingFeeds == 0:
        follow_final_column = db(db.checkingNextFollow.created_by == auth.user_id).select()
        if len(follow_final_column) == 0:
            #the main part for the view of the page
            changingFeeds = 2
        else:
            #the main part for the view of the page
            checkforuser = {follow_row['following'] for follow_row in follow_final_column}
            for column in db(db.meow).iterselect(orderby=~db.meow.timestamp):
                if makingList_fit >= MAX_RESULTS:
                    break


                 #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
                #the main part for the view of the page
                if column['author'] in checkforuser:
                    processed_row = checkFinalMeow(column)
                    if processed_row:
                        #the main part for the view of the page
                        meows.append(processed_row)
                        makingList_fit += 1

    # checking for more below

        # Being able to findNextResponse to other users and make sure it is working fine
    if changingFeeds == 3:
        checkforuser = {reply_row['findreply'] for reply_row in db(db.findreply.findMain == makingResponses).select()}
        for column in db(db.meow).iterselect(orderby=~db.meow.timestamp):
            # Being able to findNextResponse to other users and make sure it is working fine
            if makingList_fit >= MAX_RESULTS:
                break


             #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
            # Being able to findNextResponse to other users and make sure it is working fine
            if column['id'] in checkforuser:
                processed_row = checkFinalMeow(column)
                if processed_row:
                    # Being able to findNextResponse to other users and make sure it is working fine
                    meows.append(processed_row)
                    makingList_fit += 1


    # this would be my own meows that show 
    
    if changingFeeds == 1:
        #this part will be the start of the meow
        for column in db(db.meow.author == auth.user_id).iterselect(orderby=~db.meow.timestamp):
            if makingList_fit >= MAX_RESULTS:
                break


             #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
            #this part will be the start of the meow

            processed_row = checkFinalMeow(column)
            if processed_row:
                #this part will be the start of the meow
                meows.append(processed_row)
                makingList_fit += 1


   
    
    # now we see that there is another feed

    #update the most new meows respondtoUser
    if changingFeeds == 2:
        for column in db(db.meow).iterselect(orderby=~db.meow.timestamp):
            if makingList_fit >= MAX_RESULTS:
                break

             #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
             #update the most new meows respondtoUser
            processed_row = checkFinalMeow(column)
            if processed_row:
                 #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
                 #update the most new meows respondtoUser
                meows.append(processed_row)
                makingList_fit += 1
    
    
    
    return dict(meows = meows)

@action("makeFollow", method="POST")
@action.uses(db, auth.user, url_signer.verify())
    #making sure that all is working for the checkingNextFollow

def makeFollow():
    get_all = request.json
#first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
    final_column = db((db.checkingNextFollow.created_by == auth.user_id) & (db.checkingNextFollow.following == get_all['id'])).select()
    #making sure that all is working for the checkingNextFollow
    if final_column:
        column = final_column.first()
        if not get_all['following']:
            column.delete_record()
    else:
        #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
            #making sure that all is working for the checkingNextFollow

        if get_all['following']:
            db.checkingNextFollow.insert(following=get_all['id'])
    #making sure that all is working for the checkingNextFollow

    return dict(following=get_all['following'])





@action("makeReply", method="POST")
@action.uses(db, auth.user, url_signer.verify())
#making a findNextResponse to the correseponding action that is needed

def makeReply():
    get_all = request.json
#making a findNextResponse to the correseponding action that is needed
    final_column = db((db.findreply.findMain == get_all['findMain']) & (db.findreply.findreply == get_all['findreply'])).select()
    if final_column:
        #making a findNextResponse to the correseponding action that is needed
        column = final_column.first()
        if not get_all['theyreply']:
            #making a findNextResponse to the correseponding action that is needed
            column.delete_record()
            #first_name=user_active.first_name,
            #last_name=user_active.last_name,
            #user_id=user_id,
            #follower_id=original_ID,
            #followed_user_id=user_id 
    else:
        if get_all['theyreply']:
            #making a findNextResponse to the correseponding action that is needed
            db.findreply.insert(findMain=get_all['findMain'], findreply=get_all['findreply'])
            #making a findNextResponse to the correseponding action that is needed

    return dict(theyreply=get_all['theyreply'])





@action("makemeow", method="POST")
@action.uses(db, auth.user, url_signer.verify())
def makemeow():
    #lists of the meows that will be shown and needed
    data = request.json
#lists of the meows that will be shown and needed
    new_meow = {
        'author': auth.user_id,
        #lists of the meows that will be shown and needed
        'timestamp': datetime.datetime.utcnow(),
        #lists of the meows that will be shown and needed
        'content': data['content']
    }
#lists of the meows that will be shown and needed
    id = db.meow.insert(**new_meow)

    return dict(id=id)




    


