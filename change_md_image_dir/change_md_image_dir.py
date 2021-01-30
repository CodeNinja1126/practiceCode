import re
import sys
import os

addr = input('md file name : ')

f = None
if os.path.isfile(addr):
    f = open(addr, mode='r', encoding='utf8')
else:
    print('There isn\'t such file')
    sys.exit(0)
# open target md file

image_addr = input('where is the images? : ')
# dir you want to change

md_dir = os.path.abspath(addr).split(os.path.sep)
md_dir = os.path.sep.join(md_dir[:-1]) + os.path.sep

f2 = input('new file name is? : ')
f2 = open(md_dir+f2, mode='w', encoding='utf8')
# open new md file

content = 1
while content:
    content = f.readline()
    url = re.findall(r'!\[[\x20-\x7E]+\]',content)
    # finding embeded image
    
    if url:
        url = re.findall(r'\([\x20-\x7E]+\)',content)[0]
        url = url[1:-1]
        url = url.split(sep='/')
        content = '/'.join((image_addr, url[-1]))
        content = f'![{url[-1]}]({content})'
        # change image directory
        
    f2.writelines(content)

f.close()
f2.close()
