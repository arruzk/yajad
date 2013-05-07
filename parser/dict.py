# -*- coding: utf-8 -*-
#import sys
import re
import sqlite3
import codecs

dictFile = codecs.open('warodai.txt', encoding='utf-8')
conn = sqlite3.connect('../dict.sqlite')
dbC = conn.cursor()

mode = 1
content = ''
comments = ''
idioms = ''
for line in dictFile:
    if line.strip() == '':
        
        for i in xrange(len(transcription)):
            print transcription[i].strip()
        mode = 1
        content = ''
        comments = ''
        idioms = ''
        continue
    if mode == 1:
        l = re.match(u'([\w\, ]+)【([\w\,･ ]+)】\(([\w\,\:\- ]+)\)〔([0-9\;]+)〕', line, re.UNICODE)
        if not l:
            l = re.match(u'([\w\,]+)\(([\w\,]+)\)〔([0-9\;]+)〕', line, re.UNICODE)
        if l:
            transcription = re.split('[;\,]',l.group(1))
            ieroglif = re.split('[;\,]',l.group(2))
            polivanov = re.split('[;\,]',l.group(3))
        mode = 2
    else:
        content += line
        if line[0] == u'•'
            comments += line
        else if line[0] == u'◇'
            idioms += line
        else
            
#    print content    
dictFile.close()
