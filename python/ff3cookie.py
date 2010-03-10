# Extract cookies.txt-like file from FF3 sqlite3 cookies file.  e.g.:
#  cookies-sql2txt ~/.mozilla/*/cookies.sqlite launchpad
#
# Copyright 2008 Kees Cook <kees@outflux.net>
# License: GPLv2
import sys
from pysqlite2 import dbapi2 as sqlite

def usage():
    print >>sys.stderr, "Usage: %s SQLITE3DB DOMAIN"
    sys.exit(1)

try:
    filename = sys.argv[1]
    match = '%%%s%%' % sys.argv[2]
except:
    usage()

con = sqlite.connect(filename)

cur = con.cursor()
cur.execute("select host, path, isSecure, expiry, name, value from moz_cookies where host like ?", [match])

ftstr = ["FALSE","TRUE"]

print '# HTTP Cookie File'
for item in cur.fetchall():
    print "%s\t%s\t%s\t%s\t%s\t%s\t%s" % (
        item[0], ftstr[item[0].startswith('.')], item[1],
        ftstr[item[2]], item[3], item[4], item[5])
