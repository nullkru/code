#!/usr/bin/python

import os,time
class lightylist:
	def __init__(self):
		search_dir = "/p/"
		os.chdir(search_dir)
		files = os.listdir(search_dir)
		files = [os.path.join(search_dir, f) for f in files] # add path to each file
		files.sort(key=lambda y: os.path.getmtime(y),reverse=True)

		for file in files:
			mtime = time.ctime(os.path.getmtime(file))
			print "%s - %s" % (file, mtime)


if __name__ == '__main__':
	ls = lightylist()
	ls
