#! /usr/bin/python3
import sys,os,subprocess,json
delim = '--'
ignore_dirs = {
    '.archive',
    '.store',
    os.path.basename(__file__),
    '.git',
    '.gitignore',
    'tmpls'
}
commands = {}

def command(func):
    assert commands.get(func.__name__)==None
    commands[func.__name__] = func
    return func

def nl_input(*prompts):
    s = ''
    while s=='': s = input(*prompts).strip()
    return s
    
def get_field(*prompts,default=None):
    global fields
    if len(fields):
        return fields.pop()
    elif default!=None:
        return default
    else:
        return nl_input(*prompts)
    
def read_state():
    with open('.cfd','r') as f:
        return json.load(f)

def write_state(state):
    with open('.cfd','w') as f:
        json.dump(state,f,indent=2)

def get_lang(target):
    with open('tmpls/langs.json','r') as f:
        for lang in json.load(f):
            if lang['name']==target: return lang
    return None

def clear_uc(state):
    dirs = [d for d in os.listdir('.') if d not in ignore_dirs]
    print('Deleting entries from task \''+state['name']+'\'')
    print(*dirs)
    subprocess.run(['rm']+dirs)
    return True
    
def store_uc(state):
    path = '.store/'+state['name']
    while os.path.exists(path):
        print('Entry with name \''+path+'\' already exists')
        r = nl_input('Rename[r] or abort[_] : ')
        if r=='r':
            state['name'] = nl_input('')
        else:
            return False
    write_state(state)
    dirs = [d for d in os.listdir('.') if d not in ignore_dirs]
    subprocess.run(['mkdir',path])
    subprocess.run(['mv']+dirs+[path])
    return True
    
def try_make_active():
    if os.path.exists('.cfd'):
        return read_state()
    else:
        print('Currently not working on anything')
        # could prompt to create new task instead or extract
        return None
        
def try_make_inactive():
    if os.path.exists('.cfd'):
        state = read_state()
        print('Already working on \''+state['name']+'\'')
        r = nl_input('Clear[c] or store[s] or abort[_] : ')
        if r=='c':
            return clear_uc(state)
        elif r=='s':
            return store_uc(state)
        else : return False
    else : return True

@command
def new():
    if not try_make_inactive(): return
    state = {}
    state['name'] = get_field('Name of task : ')
    lang_name = get_field('Language [py|cpp|..] : ')
    state['ansfile'] = get_field(default='ans.'+lang_name)
    write_state(state)
    if (lang:=get_lang(lang_name))!=None:
        subprocess.run(['cp',lang['template'],state['ansfile']])
    else:
        with open(state['ansfile']) as _ : pass        
        
@command
def clear():
    if (state:=try_make_active())==None : return
    clear_uc(state)
        
@command
def store():
    if (state:=try_make_active())==None : return
    store_uc(state)

@command
def extract():
    if not try_make_inactive(): return
    name = get_field('Name of entry to extract : ')
    path = '.store/'+name+'/'
    if os.path.exists(path):
        dirs = [path+dir for dir in os.listdir(path)]
        subprocess.run(['mv']+dirs+['./'])
        subprocess.run(['rmdir',path])
    else:
        print('No entry with name \''+name+'\' in store')
    
#---------------------------entry_point---------------------------#
for dir in ignore_dirs:
    assert os.path.exists(dir)

if len(sys.argv)>=2 and sys.argv[1] in commands:
    fields = sys.argv[2:][::-1]
    commands[sys.argv[1]]()
else:
    print('wat?')
    # later
