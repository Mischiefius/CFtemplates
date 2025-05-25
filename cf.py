#! /usr/bin/python3
import sys,os,subprocess,json
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

def get_or_input(*prompts):
    if len(fields):
        return fields.pop()
    return nl_input(*prompts)

def get_or_default(default):
    global fields
    if len(fields):
        return fields.pop()
    return default
    
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
    if os.path.exists(path):
        print('Entry with name \''+path+'\' already exists')
        return False
    else: 
        dirs = [d for d in os.listdir('.') if d not in ignore_dirs]
        subprocess.run(['mkdir',path])
        subprocess.run(['mv']+dirs+[path])
        return True
        
def check_active():
    if os.path.exists('.cfd'):
        return read_state()
    else:
        print('Currently not working on anything')
        return None
        
def try_make_inactive():
    if os.path.exists('.cfd'):
        state = read_state()
        print('Already working on \''+state['name']+'\'')
        r = nl_input('Clear[c] or Store[s] or Abort[_] : ')
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
    state['name'] = get_or_input('Name of task : ')
    state['lang'] = get_or_input('Language [py|cpp|..] : ')
    state['ansfile'] = get_or_default('ans.'+state['lang'])
    write_state(state)
    subprocess.run(['mkdir','tests'])
    if (lang:=get_lang(state['lang']))!=None:
        subprocess.run(['cp',lang['template'],state['ansfile']])
    else:
        with open(state['ansfile'],'w') as _ : pass        
        
@command
def clear():
    if (state:=check_active())==None : return
    clear_uc(state)

@command
def set():
    if (state:=check_active())==None : return
    for field in fields:
        attr,val = field.split('=')
    write_state(state)
    
@command
def store():
    if (state:=check_active())==None : return
    store_uc(state)
    
@command
def run():
    if (state:=check_active())==None : return
    lang = get_lang(state['lang'])
    env = os.environ.copy()
    env['ARGS'] = get_or_default('')
    env['ANSFILE'] = state['ansfile']
    result = subprocess.run(lang['comp-cmd'],shell=True,env=env)
    if result.returncode!=0: return

    tests = os.listdir('tests')
    if len(tests)==0:
        subprocess.run(lang['run-cmd'],env=env,shell=True)
        subprocess.run(lang['clean-cmd'],env=env,shell=True)
        return 
    with open('.out.txt','w+') as off:
        for test in tests:
            with open('tests/'+test,'r') as iff:
                print('-----------R---------------------R-----------')
                subprocess.run(lang['run-cmd'],
                               stdout=off, stdin=iff,
                               env=env, shell=True)
                off.seek(0)
                print('-----------O---------------------O-----------')
                print(off.read(),end='')
                off.truncate()
    subprocess.run(lang['clean-cmd'],env=env,shell=True)

@command
def archive():
    if (state:=check_active())==None : return
    entry = state['name']+'_'+state['ansfile']
    if os.path.exists('.archive/'+entry):
        print('Entry with name \''+entry+'\' already exists')
    else:
        subprocess.run(['mv',state['ansfile'],'.archive/'+entry])
        clear_uc(state)

@command
def extract():
    if not try_make_inactive(): return
    name = get_or_input('Name of entry to extract : ')
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
