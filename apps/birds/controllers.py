import os
import json
from py4web import action, request, abort, redirect, URL
from .common import db, session, T, cache, auth, logger
from .models import get_user_email
from .settings import APP_FOLDER

filename = os.path.join(APP_FOLDER, "data", "table.json")

@action('index')
@action.uses('index.html', auth)
def index():
    # Open the JSON file and read its contents
    f = open(filename, 'r')
    try:
        # Load the JSON content into a Python dictionary
        content = json.load(f)
    finally:
        # Close the file
        f.close()
    return dict(content=content)