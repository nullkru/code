#!/usr/bin/python
# www.devshed.com/c/a/Python/Using-SQLite-inPython/3/

from pysqlite2 import dbapi2 as sqlite

#connection to db
connection = sqlite.connect('test.db')

cursor = connection.cursor()

#create db
#cursor.execute('CREATE TABLE names (id INTEGER PRIMARY KEY, name VARCHAR(50), email VARCHAR(50))')


cursor.execute('INSERT INTO names VALUES (null, "mirko messer", "mm@chao.ch")')


name='blah'
mail='mm@chao.ch'

cursor.execute('INSERT INTO names VALUES (null, ?, ?)', (name, mail))
connection.commit()

print cursor.lastrowid


cursor.execute('SELECT * FROM names')
#print cursor.fetchall()
print cursor.fetchmany()
