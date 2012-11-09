// device service
var HC_SID = "urn:upnp-org:serviceId:VGhost1";

//local ip
var ipaddress = data_request_url;

//global variables
var jlid1;
var jts1;
var jtst1;
var jot1;
var jov1;
var jop1;
var jdl1;
var joc1;

var jlid2;
var jts2;
var jtst2;
var jot2;
var jov2;
var jop2;
var jdl2;
var joc2;

var jlid3;
var jts3;
var jtst3;
var jot3;
var jov3;
var jop3;
var jdl3;
var joc3;

var jlid4;
var jts4;
var jtst4;
var jot4;
var jov4;
var jop4;
var jdl4;
var joc4;

var jlid5;
var jts5;
var jtst5;
var jot5;
var jov5;
var jop5;
var jdl5;
var joc5;

var jlid6;
var jts6;
var jtst6;
var jot6;
var jov6;
var jop6;
var jdl6;
var joc6;

var jlid7;
var jts7;
var jtst7;
var jot7;
var jov7;
var jop7;
var jdl7;
var joc7;

var jlid8;
var jts8;
var jtst8;
var jot8;
var jov8;
var jop8;
var jdl8;
var joc8;

//*****************************************************************************
// function: showStatus
//*****************************************************************************
function showStatus (text, error)
{
	if (!error)
	{
		document.getElementById ('status_display').style.backgroundColor = "#90FF90";
		document.getElementById ('status_display').innerHTML = text;
	}
	else
	{
		document.getElementById ('status_display').style.backgroundColor = "#FF9090";
		document.getElementById ('status_display').innerHTML = text;
	}
}
//*****************************************************************************
//  function: VGhostsettings
//*****************************************************************************
function vghostsettings (device)
{
	var html = '';

	jlid1 = get_device_state (device, HC_SID, "LightID1", 1);
	jts1 = get_device_state (device, HC_SID, "TimeStart1", 1);
	jtst1 = get_device_state (device, HC_SID, "TimeStop1", 1);
	jot1 = get_device_state (device, HC_SID, "OnTime1", 1);
	jov1 = get_device_state (device, HC_SID, "OnVariation1", 1);
	jop1 = get_device_state (device, HC_SID, "OnPropability1", 1);
	jdl1 = get_device_state (device, HC_SID, "DimLevel1", 1);
	joc1 = get_device_state (device, HC_SID, "OnCycle1", 1);

	jlid2 = get_device_state (device, HC_SID, "LightID2", 1);
	jts2 = get_device_state (device, HC_SID, "TimeStart2", 1);
	jtst2 = get_device_state (device, HC_SID, "TimeStop2", 1);
	jot2 = get_device_state (device, HC_SID, "OnTime2", 1);
	jov2 = get_device_state (device, HC_SID, "OnVariation2", 1);
	jop2 = get_device_state (device, HC_SID, "OnPropability2", 1);
	jdl2 = get_device_state (device, HC_SID, "DimLevel2", 1);
	joc2 = get_device_state (device, HC_SID, "OnCycle2", 1);
	
	jlid3 = get_device_state (device, HC_SID, "LightID3", 1);
	jts3 = get_device_state (device, HC_SID, "TimeStart3", 1);
	jtst3 = get_device_state (device, HC_SID, "TimeStop3", 1);
	jot3 = get_device_state (device, HC_SID, "OnTime3", 1);
	jov3 = get_device_state (device, HC_SID, "OnVariation3", 1);
	jop3 = get_device_state (device, HC_SID, "OnPropability3", 1);
	jdl3 = get_device_state (device, HC_SID, "DimLevel3", 1);
	joc3 = get_device_state (device, HC_SID, "OnCycle3", 1);
	
	jlid4 = get_device_state (device, HC_SID, "LightID4", 1);
	jts4 = get_device_state (device, HC_SID, "TimeStart4", 1);
	jtst4 = get_device_state (device, HC_SID, "TimeStop4", 1);
	jot4 = get_device_state (device, HC_SID, "OnTime4", 1);
	jov4 = get_device_state (device, HC_SID, "OnVariation4", 1);
	jop4 = get_device_state (device, HC_SID, "OnPropability4", 1);
	jdl4 = get_device_state (device, HC_SID, "DimLevel4", 1);
	joc4 = get_device_state (device, HC_SID, "OnCycle4", 1);
	
	jlid5 = get_device_state (device, HC_SID, "LightID5", 1);
	jts5 = get_device_state (device, HC_SID, "TimeStart5", 1);
	jtst5 = get_device_state (device, HC_SID, "TimeStop5", 1);
	jot5 = get_device_state (device, HC_SID, "OnTime5", 1);
	jov5 = get_device_state (device, HC_SID, "OnVariation5", 1);
	jop5 = get_device_state (device, HC_SID, "OnPropability5", 1);
	jdl5 = get_device_state (device, HC_SID, "DimLevel5", 1);
	joc5 = get_device_state (device, HC_SID, "OnCycle5", 1);
	
	jlid6 = get_device_state (device, HC_SID, "LightID6", 1);
	jts6 = get_device_state (device, HC_SID, "TimeStart6", 1);
	jtst6 = get_device_state (device, HC_SID, "TimeStop6", 1);
	jot6 = get_device_state (device, HC_SID, "OnTime6", 1);
	jov6 = get_device_state (device, HC_SID, "OnVariation6", 1);
	jop6 = get_device_state (device, HC_SID, "OnPropability6", 1);
	jdl6 = get_device_state (device, HC_SID, "DimLevel6", 1);
	joc6 = get_device_state (device, HC_SID, "OnCycle6", 1);
	
	jlid7 = get_device_state (device, HC_SID, "LightID7", 1);
	jts7 = get_device_state (device, HC_SID, "TimeStart7", 1);
	jtst7 = get_device_state (device, HC_SID, "TimeStop7", 1);
	jot7 = get_device_state (device, HC_SID, "OnTime7", 1);
	jov7 = get_device_state (device, HC_SID, "OnVariation7", 1);
	jop7 = get_device_state (device, HC_SID, "OnPropability7", 1);
	jdl7 = get_device_state (device, HC_SID, "DimLevel7", 1);
	joc7 = get_device_state (device, HC_SID, "OnCycle7", 1);
	
	jlid8 = get_device_state (device, HC_SID, "LightID8", 1);
	jts8 = get_device_state (device, HC_SID, "TimeStart8", 1);
	jtst8 = get_device_state (device, HC_SID, "TimeStop8", 1);
	jot8 = get_device_state (device, HC_SID, "OnTime8", 1);
	jov8 = get_device_state (device, HC_SID, "OnVariation8", 1);
	jop8 = get_device_state (device, HC_SID, "OnPropability8", 1);
	jdl8 = get_device_state (device, HC_SID, "DimLevel8", 1);
	joc8 = get_device_state (device, HC_SID, "OnCycle8", 1);

	{
		// show status area
		html += '<div><p id="status_display" style="width:100%; position:relative; margin-left:auto; margin-right:auto; table-layout:fixed; text-align:center; border-radius: 5px; color:black"></div>';
		html += '<table style="width:100%; position:relative; margin-left:auto; margin-right:auto; border-radius: 5px">';

		// show titles
		html += '<tr>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">LightID:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:20%">TimeStart:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:20%">TimeStop:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">OnCycles:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:20%">OnTime:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">OnTimeVariation:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">OnProbability:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">DimLevel:</td>';
		html += '</tr>';
 
		//show variables
		lights = new Array(jlid1, jlid2, jlid3, jlid4, jlid5, jlid6, jlid7, jlid8);
		starts = new Array(jts1, jts2, jts3, jts4, jts5, jts6, jts7, jts8);
		stops = new Array(jtst1, jtst2, jtst3, jtst4, jtst5, jtst6, jtst7, jtst8);
		ontimes = new Array(jot1, jot2, jot3, jot4, jot5, jot6, jot7, jot8);
		onvariations = new Array(jov1, jov2, jov3, jov4, jov5, jov6, jov7, jov8);
		onpropabilities = new Array(jop1, jop2, jop3, jop4, jop5, jop6, jop7, jop8);
		oncycles = new Array(joc1, joc2, joc3, joc4, joc5, joc6, joc7, joc8);
		dimlevels = new Array(jdl1, jdl2, jdl3, jdl4, jdl5, jdl6, jdl7, jdl8);
		
		for (i = 0; i <= 7; i++)
		{
		html += '<tr>';
		html += '<td><input type="text" maxlength="20" id="light' + lights[i] + '" value="' + lights[i] + '" style="width:95%; text-align:left" onChange="savejlid(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="starts' + starts[i] + '" value="' + starts[i] + '" style="width:95%; text-align:left" onChange="savejts(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="stops' + stops[i] + '" value="' + stops[i] + '" style="width:95%; text-align:left" onChange="savejtst(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="oncycles' + oncycles[i] + '" value="' + oncycles[i] + '" style="width:95%; text-align:left" onChange="savejoc(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="ontimes' + ontimes[i] + '" value="' + ontimes[i] + '" style="width:95%; text-align:left" onChange="savejot(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="onvariations' + onvariations[i] + '" value="' + onvariations[i] + '" style="width:95%; text-align:left" onChange="savejov(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="onpropabilities' + onpropabilities[i] + '" value="' + onpropabilities[i] + '" style="width:95%; text-align:left" onChange="savejop(' + device + ', ' + i + ', this.value)" /></td>';
		html += '<td><input type="text" maxlength="20" id="dimlevels' + dimlevels[i] + '" value="' + dimlevels[i] + '" style="width:95%; text-align:left" onChange="savejdl(' + device + ', ' + i + ', this.value)" /></td>';
		html += '</tr>';
		}
			
		// show save button
		html += '<tr>';
			html += '<td colspan="3"><input type="button" value="SAVE" onClick="saveall(1,' + device + ')" style="margin-left:255%; background:#3295F8; color:white; text-align:center; border-radius:5px; padding-top:4px; text-transform:capitalize; font-family:Arial; font-size:14px; cursor:pointer; -khtml-border-radius: 5px; -webkit-border-radius:5px"/></td>';
		html += '</tr>';
	}
	set_panel_html (html);
	showStatus ("Enter your Settings!", false);
}
//*****************************************************************************
//  function: save => jlid
//*****************************************************************************
function savejlid (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jlid1 = newValue;}
	else if(varis==1){jlid2 = newValue;}
	else if(varis==2){jlid3 = newValue;}
	else if(varis==3){jlid4 = newValue;}
	else if(varis==4){jlid5 = newValue;}
	else if(varis==5){jlid6 = newValue;}
	else if(varis==6){jlid7 = newValue;}
	else if(varis==7){jlid8 = newValue;}
}
//*****************************************************************************
//  function: save => jts
//*****************************************************************************
function savejts (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jts1 = newValue;}
	else if(varis==1){jts2 = newValue;}
	else if(varis==2){jts3 = newValue;}
	else if(varis==3){jts4 = newValue;}
	else if(varis==4){jts5 = newValue;}
	else if(varis==5){jts6 = newValue;}
	else if(varis==6){jts7 = newValue;}
	else if(varis==7){jts8 = newValue;}
}
//*****************************************************************************
//  function: save => jtst
//*****************************************************************************
function savejtst (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jtst1 = newValue;}
	else if(varis==1){jtst2 = newValue;}
	else if(varis==2){jtst3 = newValue;}
	else if(varis==3){jtst4 = newValue;}
	else if(varis==4){jtst5 = newValue;}
	else if(varis==5){jtst6 = newValue;}
	else if(varis==6){jtst7 = newValue;}
	else if(varis==7){jtst8 = newValue;}
}
//*****************************************************************************
//  function: save => jot
//*****************************************************************************
function savejot (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jot1 = newValue;}
	else if(varis==1){jot2 = newValue;}
	else if(varis==2){jot3 = newValue;}
	else if(varis==3){jot4 = newValue;}
	else if(varis==4){jot5 = newValue;}
	else if(varis==5){jot6 = newValue;}
	else if(varis==6){jot7 = newValue;}
	else if(varis==7){jot8 = newValue;}
}
//*****************************************************************************
//  function: save => jov
//*****************************************************************************
function savejov (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jov1 = newValue;}
	else if(varis==1){jov2 = newValue;}
	else if(varis==2){jov3 = newValue;}
	else if(varis==3){jov4 = newValue;}
	else if(varis==4){jov5 = newValue;}
	else if(varis==5){jov6 = newValue;}
	else if(varis==6){jov7 = newValue;}
	else if(varis==7){jov8 = newValue;}
}
//*****************************************************************************
//  function: save => jop
//*****************************************************************************
function savejop (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jop1 = newValue;}
	else if(varis==1){jop2 = newValue;}
	else if(varis==2){jop3 = newValue;}
	else if(varis==3){jop4 = newValue;}
	else if(varis==4){jop5 = newValue;}
	else if(varis==5){jop6 = newValue;}
	else if(varis==6){jop7 = newValue;}
	else if(varis==7){jop8 = newValue;}
}
//*****************************************************************************
//  function: save => jdl
//*****************************************************************************
function savejdl (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){jdl1 = newValue;}
	else if(varis==1){jdl2 = newValue;}
	else if(varis==2){jdl3 = newValue;}
	else if(varis==3){jdl4 = newValue;}
	else if(varis==4){jdl5 = newValue;}
	else if(varis==5){jdl6 = newValue;}
	else if(varis==6){jdl7 = newValue;}
	else if(varis==7){jdl8 = newValue;}
}
//*****************************************************************************
//  function: save => joc
//*****************************************************************************
function savejoc (deviceid, varis, newValue)
{
	showStatus ("UNSAVED CHANGES!", true);
		
	if(varis==0){joc1 = newValue;}
	else if(varis==1){joc2 = newValue;}
	else if(varis==2){joc3 = newValue;}
	else if(varis==3){joc4 = newValue;}
	else if(varis==4){joc5 = newValue;}
	else if(varis==5){joc6 = newValue;}
	else if(varis==6){joc7 = newValue;}
	else if(varis==7){joc8 = newValue;}
}
//*****************************************************************************
//  function: statussaving
//*****************************************************************************
function statussaving ()
{
	showStatus ("SAVING...", false);
}

//*****************************************************************************
//  function: saveall
//*****************************************************************************
function saveall (luupcode,device)
{
	statussaving ()

	lightsss = new Array(jlid1, jlid2, jlid3, jlid4, jlid5, jlid6, jlid7, jlid8);
	startsss = new Array(jts1, jts2, jts3, jts4, jts5, jts6, jts7, jts8);
	stopsss = new Array(jtst1, jtst2, jtst3, jtst4, jtst5, jtst6, jtst7, jtst8);
	ontimesss = new Array(jot1, jot2, jot3, jot4, jot5, jot6, jot7, jot8);
	onvariationsss = new Array(jov1, jov2, jov3, jov4, jov5, jov6, jov7, jov8);
	onpropabilitiesss = new Array(jop1, jop2, jop3, jop4, jop5, jop6, jop7, jop8);
	oncyclesss = new Array(joc1, joc2, joc3, joc4, joc5, joc6, joc7, joc8);	
	dimlevelsss = new Array(jdl1, jdl2, jdl3, jdl4, jdl5, jdl6, jdl7, jdl8);
	
	lightss = new Array("LightID1", "LightID2", "LightID3", "LightID4", "LightID5", "LightID6", "LightID7", "LightID8");
	startss = new Array("TimeStart1", "TimeStart2", "TimeStart3", "TimeStart4", "TimeStart5", "TimeStart6", "TimeStart7", "TimeStart8");
	stopss = new Array("TimeStop1", "TimeStop2", "TimeStop3", "TimeStop4", "TimeStop5", "TimeStop6", "TimeStop7", "TimeStop8");
	ontimess = new Array("OnTime1", "OnTime2", "OnTime3", "OnTime4", "OnTime5", "OnTime6", "OnTime7", "OnTime8");
	onvariationss = new Array("OnVariation1", "OnVariation2", "OnVariation3", "OnVariation4", "OnVariation5", "OnVariation6", "OnVariation7", "OnVariation8");
	onpropabilitiess = new Array("OnPropability1", "OnPropability2", "OnPropability3", "OnPropability4", "OnPropability5", "OnPropability6", "OnPropability7", "OnPropability8");
	oncycless = new Array("OnCycle1", "OnCycle2", "OnCycle3", "OnCycle4", "OnCycle5", "OnCycle6", "OnCycle7", "OnCycle8");
	dimlevelss = new Array("DimLevel1", "DimLevel2", "DimLevel3", "DimLevel4", "DimLevel5", "DimLevel6", "DimLevel7", "DimLevel8");
	
	for (i = 0; i <= 7; i++)
	{
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+lightss[i]+'","'+lightsss[i]+'",'+ device +')', false );
	xmlHttp.send( null );

	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+startss[i]+'","'+startsss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+stopss[i]+'","'+stopsss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+ontimess[i]+'","'+ontimesss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+oncycless[i]+'","'+oncyclesss[i]+'",'+ device +')', false );
	xmlHttp.send( null );

	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+onvariationss[i]+'","'+onvariationsss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+onpropabilitiess[i]+'","'+onpropabilitiesss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ ipaddress +'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+ HC_SID +'","'+dimlevelss[i]+'","'+dimlevelsss[i]+'",'+ device +')', false );
	xmlHttp.send( null );
	}
	
	function finished () {showStatus ("ALL CHANGES SAVED!", false);}
	window.setTimeout(finished, 1000);
}
