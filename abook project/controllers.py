import uuid

from py4web import URL, Field, abort, action, redirect, request
from py4web.utils.form import Form, FormStyleBulma
from .models import get_user_id

from py4web.utils.url_signer import URLSigner

from .common import T, auth, cache, db, session, signed_url

url_signer = URLSigner(session)

@action("index")
@action.uses('index.html', url_signer, db, auth.user)
def index():
    contacts = []
    if auth.user_id:
        check_query = db.check_names.created_by == get_user_id()
        check_rows = db(check_query).select()
        for row in check_rows:
            check_contact = dict(
                id=row.id,
                firstName=row.firstName,
                lastName=row.lastName,
                phones=[]
            )
            phone_query = db.check_number.name_id == row.id
            phones = db(phone_query).select()
            for phone in phones:
                check_contact['phones'].append(dict(
                    id=phone.id,
                    number=phone.phone,
                    kind=phone.kind
                ))
            contacts.append(check_contact)
    else:
        check_rows = None
    return locals()

@action('addNames', method=['GET', 'POST'])
@action.uses('addNames.html', url_signer, db, session, auth.user)
def addNames():
    form = Form(db.check_names, csrf_session = session, formstyle = FormStyleBulma)
    if form.accepted:
        redirect(URL('index'))
    return dict(form=form)

@action('edit/<bird_id:int>', method=["GET", "POST"])
@action.uses('edit.html', url_signer, db, session, auth.user)
def edit(bird_id=None):

    check_names = db.check_names[bird_id]
    # if check_names.created_by != get_user_id():
    #     raise HTTP(400)
    
    assert bird_id is not None
  
    p = db.check_names[bird_id]
    if p is None:
        redirect(URL('index'))
    form = Form(db.check_names, record=p, deletable=False, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:
        redirect(URL('index'))
    return dict(form=form)



@action('addNums', method=["GET", "POST"])
@action.uses('addNums.html', session, db)
def addNums():
    form = Form(db.check_number, csrf_session=session, formstyle=FormStyleBulma)
    if form.accepted:

        name_id = db.check_names.insert(created_by=get_user_id())
        db.check_number.insert(phone=form.vars['phone'], name_id=name_id, kind=form.vars['kind'])
        redirect(URL('index'))
    return dict(form=form)

@action('delete/<product_id:int>')
@action.uses(db, session, auth.user, url_signer.verify())
def delete(product_id=None):

    assert product_id is not None

    db(db.product.id == product_id).delete()
    redirect(URL('index'))






