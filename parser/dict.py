# -*- coding: utf-8 -*-
import sys
import re
import sqlite3
import codecs

def delete_word(text, wordList):
    for i in wordList:
        text = text.replace(i, '')
    return text

badWord = codecs.open('replace.txt', encoding='utf-8').read()
badWord = badWord.split('\r\n')

dictFile = codecs.open('warodai.txt', encoding='utf-8')
conn = sqlite3.connect('../dict.sqlite')
dbC = conn.cursor()

mode = 1
content = ''
comments = ''
idioms = ''
rusWords = []
successCount = 0
lineNum = 0
for line in dictFile:
    lineNum += 1
    if lineNum%5000 == 0:
        print lineNum
    if line.strip() == '':
        if curData: #article title
            dbC.execute(u"insert into article (`aText`,`comment`,`idioms`,`lang`) values (?, ?, ?, 'ru')", [content, comments, idioms])
            articleId = dbC.lastrowid
            for word in rusWords:
                dbC.execute(u"insert into translation (`word`,`articleId`) values (?, ?)", [word, articleId])
            if (len(curData.groups()) == 4):
                for syllabary, hieroglyphs, transcription in zip(re.split('[;\,]', curData.group(1)),  #transcription -> polivanov
                                                              re.split('[;\,]', curData.group(2)),
                                                              re.split('[;\,]', curData.group(3))):
                    dbC.execute(u"insert into jaWord (`syllabary`,`hieroglyph`,`transcription`, `code`) values (?, ?, ?, ?)",
                                [syllabary.strip(), hieroglyphs.strip(), transcription.strip(), curData.group(4)])
                    jaWordId = dbC.lastrowid
                    for hieroglyph in hieroglyphs.split(u'･'):
                        dbC.execute(u"insert into hieroglyphWord (`hieroglyph`,`jaWordId`) values (?, ?)", [hieroglyph, jaWordId])
                    dbC.execute(u"insert into jaWordArticle (`jaWordId`,`articleId`) values (?, ?)", [jaWordId, articleId])
            else: #sorry!
                for syllabary, transcription in zip(re.split('[;\,]', curData.group(1)),  #transcription -> polivanov
                                                    re.split('[;\,]', curData.group(2))):
                    dbC.execute(u"insert into jaWord (`syllabary`,`transcription`, `code`) values (?, ?, ?)",
                                [syllabary.strip(), transcription.strip(), curData.group(3)])
                    jaWordId = dbC.lastrowid
                    dbC.execute(u"insert into jaWordArticle (`jaWordId`,`articleId`) values (?, ?)", [jaWordId, articleId])
            successCount += 1
        mode = 1
        content = ''
        comments = ''
        idioms = ''
        rusWords = []
        conn.commit()
        continue
    if mode == 1: #read article title
        l = re.match(u'([\w\, ]+)【([\w\,･ ]+)】\(([\w\,\:\- ]+)\)〔([0-9\;]+)〕', line, re.UNICODE)
        if not l:
            l = re.match(u'([\w\,]+)\(([\w\,]+)\)〔([0-9\;]+)〕', line, re.UNICODE)
        if l:
            curData = l
        mode = 2
    else:
        content += line
        if line[0] == u'•':
            comments += line.replace(u'•', '')
        elif line[0] == u'◇':
            idioms += line.replace(u'◇', '')
        else:
            rus_line = re.sub(r'<[^>]*?>', u'', line) #delete html tags
            rus_line = re.sub(r'\([^\)]*?\)', u'', rus_line) #delete parentheses
            rus_line = re.sub(r'[\d]*\)[\: ]*', u'', rus_line)
            rus_line = delete_word(rus_line, badWord)
            rus_line = rus_line.strip()
            if re.match(u'^[a-яА-ЯёЁ].*', rus_line):
#                print rus_line
                manyRusWord = re.split(u'[\,\;]', rus_line)
                for once in manyRusWord:
                    if once != u'':
                        rusWords.append(once.strip().replace('.',''))
print successCount
dictFile.close()
conn.commit()
dbC.close()
