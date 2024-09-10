"""
This file defines the database models
"""

import datetime

from pydal.validators import *

from .common import Field, auth, db

def get_user_id():
    return auth.current_user.get('id') if auth.current_user else None

db.define_table(
    'check_names',
    Field('firstName', label='First Name', requires=IS_NOT_EMPTY()),
    Field('lastName', label='Last Name', requires=IS_NOT_EMPTY()),
    auth.signature
)

db.define_table(
    'check_number',
    Field('name_id', 'reference check_names', readable=False, writable=False),
    Field('phone', label='Phone', requires=IS_NOT_EMPTY()),
    Field('kind', label='Kind', requires=IS_NOT_EMPTY()),
    auth.signature
)

db.check_names.id.readable = db.check_names.id.writable = False
db.check_number.id.readable = db.check_number.id.writable = False

db.commit()