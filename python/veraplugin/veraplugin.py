import xbmc,xbmcgui
import subprocess,os

class MyPlayer(xbmc.Player) :
	###
	# Vera specific config
	###

	xbmcip = "10.0.0.132"
	veraPluginID = 57

	# END
		
	requestUrl = 'http://%s:3480/data_request?id=variableset&DeviceNum=%d&serviceId=urn:upnp-org:serviceId:XBMC1&Variable=PlayerStatus&Value=' % (xbmcip, veraPluginID)
	wgetCmd = 'wget --spider'


	def __init__ (self):
		print(requestUrl)
		xbmc.Player.__init__(self)

	def onPlayBackStarted(self):
		if xbmc.Player().isPlayingVideo():
			os.system('%s %s+"PlayBackStarted"' % (wgetCmd,requestUrl))

	def onPlayBackEnded(self):
		if (VIDEO == 1):
			os.system('%s %s+"PlayBackEnded"' % (wgetCmd,requestUrl))

	def onPlayBackStopped(self):
		if (VIDEO == 1):
			os.system('%s %s+"PlayBackStopped"' % (wgetCmd,requestUrl))

	def onPlayBackPaused(self):
		if xbmc.Player().isPlayingVideo():
			os.system('%s %s+"PlayBackPaused"' % (wgetCmd,requestUrl))

	def onPlayBackResumed(self):
		if xbmc.Player().isPlayingVideo():
			os.system('%s %s+"PlayBackResumed"' % (wgetCmd,requestUrl)

player=MyPlayer()
 
VIDEO = 0
 
while(1):
	if xbmc.Player().isPlaying():
		if xbmc.Player().isPlayingVideo():
			VIDEO = 1
	else:
		VIDEO = 0

	xbmc.sleep(1000)
