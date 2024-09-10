import datetime
from .common import db, Field
from pydal.validators import *
from .common import db, Field, auth, T

def get_user_email():
    return auth.current_user.get('email') if auth.current_user else None

### Define your table below
db.define_table(
    'bird', 
    Field('bird', requires=IS_NOT_EMPTY()),
    Field('weight', 'integer', requires=IS_INT_IN_RANGE(0, 1e6)),
    Field('diet', requires=IS_NOT_EMPTY()),
    Field('habitat', requires=IS_NOT_EMPTY()),
    Field('n_sightings', 'integer', requires=IS_INT_IN_RANGE(0, 1e6)),
    Field('created_by', 'string',  default=get_user_email),
)
db.bird.id.readable = db.bird.id.writable = False
# always commit your models to avoid problems later
db.commit()

