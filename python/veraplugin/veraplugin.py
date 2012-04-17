import xbmc,xbmcgui
import subprocess,os

class MyPlayer(xbmc.Player):

	###
	# Vera specific config
	###

	veraIP = "10.0.0.50"
	veraPluginID = 57

	# END
		
	requestUrl = 'http://%s:3480/data_request?id=variableset&DeviceNum=%d&serviceId=urn:upnp-org:serviceId:XBMC1&Variable=PlayerStatus&Value=' % (veraIP, veraPluginID)
	wgetCmd = 'wget --spider '


	def __init__ (self):
		xbmc.Player.__init__(self)

	def onPlayBackStarted(self):
		if xbmc.Player().isPlayingVideo():
			os.system('echo \'%s %sStarted\' > /tmp/veraplugin.log' % (self.wgetCmd,self.requestUrl))
			os.system('%s \'%sStarted\'' % (self.wgetCmd,self.requestUrl))

	def onPlayBackEnded(self):
		if (VIDEO == 1):
			os.system('%s \'%sEnded\'' % (self.wgetCmd,self.requestUrl))

	def onPlayBackStopped(self):
		if (VIDEO == 1):
			os.system('%s \'%sStopped\'' % (self.wgetCmd,self.requestUrl))

	def onPlayBackPaused(self):
		if xbmc.Player().isPlayingVideo():
			os.system('%s \'%sPaused\'' % (self.wgetCmd,self.requestUrl))
			os.system('echo \'%s %sPaused\' > /tmp/veraplugin.log' % (self.wgetCmd,self.requestUrl))

	def onPlayBackResumed(self):
		if xbmc.Player().isPlayingVideo():
			os.system('%s \'%s+"Resumed"\'' % (self.wgetCmd,self.requestUrl))


player=MyPlayer()

VIDEO = 0
 
while(1):
	if xbmc.Player().isPlaying():
		if xbmc.Player().isPlayingVideo():
			VIDEO = 1
		else:
			VIDEO = 0
	xbmc.sleep(1000)
