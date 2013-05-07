# -*- coding: utf-8 -*-
#import sys
import re
import sqlite3
import codecs

kanaFile = codecs.open('radkfilex_fin.unicode', encoding='utf-8')
conn = sqlite3.connect('../dict.sqlite')
dbC = conn.cursor()

i = 0
for line in kanaFile:
#    line = u"$ 買 5 5474"
    l = re.match(u'\$ (\w) (\d+)', line, re.UNICODE)
    if l:
        dbC.execute(u"select * from radical where character=?", [l.group(1)])
        t = dbC.fetchone()
        if not t:
            dbC.execute(u"insert into radical (`character`,`rgroup`) values (?, ?)", [l.group(1), int(l.group(2))])
            kanaId = dbC.lastrowid
        else:
            kanaId = t[0]
    else:
        for heirog in line:
            dbC.execute(u"select * from hieroglyph where character=?", [heirog])
            t = dbC.fetchone()
            if not t:
                dbC.execute(u"insert into hieroglyph (`character`) values (?)", [heirog])
                heirogId = dbC.lastrowid
            else:
                heirogId = t[0]
            dbC.execute(u"insert into hieroglyphRadical (`hieroglyph_id`, `radical_id`) values (?, ?)", [heirogId, kanaId])
    i = i+1
    print(i, ' '),
conn.commit()
dbC.close()
kanaFile.close()                
