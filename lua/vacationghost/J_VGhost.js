// device service
var HC_SID = "urn:upnp-org:serviceId:VGhost1";

//local ip
var ipaddress = data_request_url;

//*****************************************************************************
// function: showStatus => used to show the status bar on top
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
//  function: VGhostsettings => basic function for the tab "Lights & Times"
//*****************************************************************************
function vghostsettings (device)
{
	var html = '';
	
	//read variables from vera and reset change variables
	for (i = 1; i <= 8; i++)
	{
		ngtchg = "0";
		window["jlid"+i+"chg"] = "0";
		window["jts"+i+"chg"] = "0";
		window["jtst"+i+"chg"] = "0";
		window["jot"+i+"chg"] = "0";
		window["jov"+i+"chg"] = "0";
		window["jop"+i+"chg"] = "0";
		window["jdl"+i+"chg"] = "0";
		window["joc"+i+"chg"] = "0";
		
		window["jlid"+i] = get_device_state(device,HC_SID,"LightID"+i,1);
		window["jts"+i] = get_device_state(device,HC_SID,"TimeStart"+i,1);
		window["jtst"+i] = get_device_state(device,HC_SID,"TimeStop"+i,1);
		window["jot"+i] = get_device_state(device,HC_SID,"OnTime"+i,1);
		window["jov"+i] = get_device_state(device,HC_SID,"OnVariation"+i,1);
		window["jop"+i] = get_device_state(device,HC_SID,"OnPropability"+i,1);
		window["jdl"+i] = get_device_state(device,HC_SID,"DimLevel"+i,1);
		window["joc"+i] = get_device_state(device,HC_SID,"OnCycle"+i,1);
	}
	
	{
		// show status area
		html += '<div><p id="status_display" style="width:100%; position:relative; margin-left:auto; margin-right:auto; table-layout:fixed; text-align:center; border-radius: 5px; color:black"></div>';
		html += '<table style="width:100%; position:relative; margin-left:auto; margin-right:auto; border-radius: 5px">';

		// show titles
		html += '<tr>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">LightID:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:15%">Start:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:15%">Stop:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">Cycles:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">OnTime:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">Variation:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">Probability:</td>';
			html += '<td style="font-weight:bold; text-align:left; width:10%">DimLevel:</td>';
		html += '</tr>';
 
		//show variable-fields
		vn1 = "jlid"; 
		vn2 = "jts"; 
		vn3 = "jtst"; 
		vn4 = "jot"; 
		vn5 = "jov"; 
		vn6 = "jop"; 
		vn7 = "joc"; 
		vn8 = "jdl";
		
		for (i = 1; i <= 8; i++)
		{
			html += '<tr>';
			html += '<td><input type="number" min="1" max="999" id="light'+window["jlid"+i]+'" value="'+window["jlid"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn1+'\')"/></td>';
			html += '<td><input type="time" maxlength="5" id="starts'+window["jts"+i]+'" value="'+window["jts"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn2+'\')"/></td>';
			html += '<td><input type="time" maxlength="5" id="stops'+window["jtst"+i]+'" value="'+window["jtst"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn3+'\')"/></td>';
			html += '<td><input type="number" min="0" max="999" id="oncycles'+window["joc"+i]+'" value="'+window["joc"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn7+'\')"/></td>';
			html += '<td><input type="number" min="1" max="999" id="ontimes'+window["jot"+i]+'" value="'+window["jot"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn4+'\')"/></td>';
			html += '<td><input type="number" min="1" max="999" id="onvariations'+window["jov"+i]+'" value="'+window["jov"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn5+'\')"/></td>';
			html += '<td><input type="number" min="1" max="100" id="onpropabilities'+window["jop"+i]+'" value="'+window["jop"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn6+'\')" /></td>';
			html += '<td><input type="number" min="0" max="100" id="dimlevels'+window["jdl"+i]+'" value="'+window["jdl"+i]+'" style="width:95%; height:100%; text-align:left; font-family:arial,sans-serif; font-size:11px; border:1px solid #0379D8;" onChange="save('+i+',this.value,\''+vn8+'\')"/></td>';
			html += '</tr>';
		}
			
		// show save button and checkbox
		valchk = get_device_state(device,HC_SID,"Night",1);
		if (valchk==1){chk = "checked";}
		else {chk = "";}
		
		html += '<tr>';
			html += '<td colspan="2"><input name="ifnight" type="checkbox" value="1" '+chk+' onClick="savenight(this)" style="position:absolute;"/><bd style="position:absolute; font-family:arial,sans-serif; font-size:11px; left:25px;">Only turn on lights during night.</bd></td>';
			html += '<td colspan="2"><input type="button" value="SAVE" onClick="saveall(1,'+device+')" style="position:absolute; left:542px; background:#3295F8; color:white; text-align:center; border-radius:5px; padding-top:4px; text-transform:capitalize; font-family:Arial; font-size:14px; cursor:pointer; -khtml-border-radius: 5px; -webkit-border-radius:5px"/></td>';
		html += '</tr>';
	}
	set_panel_html (html);
	showStatus ("Enter your Settings:", false);
}
//*****************************************************************************
//  function: save => set variables after change and set change variables
//*****************************************************************************
function save(varis, newValue, varnames)
{
	showStatus ("UNSAVED CHANGES!", true);
    window[varnames+varis] = newValue;
	window[varnames+varis+"chg"] = "1";
}
//*****************************************************************************
//  function: savenight => set variables for night and according change variable
//*****************************************************************************
function savenight(cb)
{
	showStatus ("UNSAVED CHANGES!", true);
	ngtchg = 1;
    if (cb.checked){ngt = "1";}
	else {ngt = "0";}
}
//*****************************************************************************
//  function: sendhttp => send variables to vera http get
//*****************************************************************************
function sendhttp(device, varname, varvalue)
{
	var xmlHttp = null;
	xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", ''+ipaddress+'id=lu_action&serviceId=urn:micasaverde-com:serviceId:HomeAutomationGateway1&action=RunLua&Code=luup.variable_set("'+HC_SID+'","'+varname+'","'+varvalue+'",'+device+')', false );
	xmlHttp.send( null );
}
//*****************************************************************************
//  function: saveall => check which variables changed and write
//*****************************************************************************
function saveall (luupcode,device)
{
	for (i = 1; i <= 8; i++)
	{
		if (window["jlid"+i+"chg"]==1){sendhttp(+device,"LightID"+i,window["jlid"+i])}

		if (window["jts"+i+"chg"]==1){sendhttp(+device,"TimeStart"+i,window["jts"+i])}

		if (window["jtst"+i+"chg"]==1){sendhttp(+device,"TimeStop"+i,window["jtst"+i])}

		if (window["jot"+i+"chg"]==1){sendhttp(+device,"OnTime"+i,window["jot"+i])}

		if (window["joc"+i+"chg"]==1){sendhttp(+device,"OnCycle"+i,window["joc"+i])}

		if (window["jov"+i+"chg"]==1){sendhttp(+device,"OnVariation"+i,window["jov"+i])}

		if (window["jop"+i+"chg"]==1){sendhttp(+device,"OnPropability"+i,window["jop"+i])}

		if (window["jdl"+i+"chg"]==1){sendhttp(+device,"DimLevel"+i,window["jdl"+i])}
	}
	
	// Update Changes variable 
	sendhttp(+device,"Changes",1)	
	
	// Update Night variable
	if (ngtchg==1){sendhttp(+device,"Night",+ngt)}

	showStatus ("ALL CHANGES SAVED!", false);
}
//*****************************************************************************
//  function: Ghost Informations
//*****************************************************************************

function getDevicesPOC() {

	var testSel = 34;
	new Ajax.Request("/port_3480/data_request", {
		method: "get",
		parameters: {
			id: "lu_sdata"
		},	
		onSuccess: function(transport) {
			var res = transport.responseText.evalJSON();

			//alert(res['devices'][1]['category']);
			var selBox = document.getElementById("VGdevices");
			selBox.options[0]=new Option("select dev");
			
			var n = 1;
			for(var i=0; i<res['devices'].length; i++){
				var dev = res['devices'][i];
				if (dev['category'] == 2 || dev['category'] == 3){
					if(dev['id'] == testSel){
						selBox.options[n++] = new Option(dev['id']+" "+dev['name'],dev['id'],true);
						selBox.options[0] = new Option(dev['id'],dev['id']);
					}
					else {
						selBox.options[n++] = new Option(dev['id']+" "+dev['name'],dev['id']);
					}
				}
			}
		},
		onFailure: function() {
			alert("fuck");
		}
	});
	return true;	
}

function vghostInfo(device) {

	var html = [
		'<div id="info">',
			//'<textarea id="VGinfo" style="width:100%; height:100px;"></textarea>',
			'<table id="VGtblInfo" style="width:100%; border:1px solid #000;">',
				'<tr><th>Name</th><th>ID</th><th>From</th><th>To</th><th>On</th></tr></table>',
			'<select name="VGdevs" id="VGdevices"></select>',
		'</div>'
	].join("\n");

	getDevicesPOC();
	
	new Ajax.Request("/cmh/VGhostInfo.json", {
		method: "get",
		onSuccess: function(transport) {
			var res = transport.responseText.evalJSON();

			var tbl = document.getElementById("VGtblInfo");
			
			var ghostInfo = "";
			for(var i=0; i<res.length; i++){
				var g = res[i];
				ghostInfo += g['name'] + " light ID: "+ g['lightId'] +" from: "+ g['start'] +" till: "+ g['end'] +" on: "+ g['date'] +"\n";
				
				var tblRowCount = tbl.rows.length;
				var row = tbl.insertRow(tblRowCount);
				
				row.insertCell(0).innerHTML = g['name'];
				row.insertCell(1).innerHTML = g['lightId'];
				row.insertCell(2).innerHTML = g['start'];
				row.insertCell(3).innerHTML = g['end'];
				row.insertCell(4).innerHTML = g['date'];


			}
			//document.getElementById("VGinfo").innerHTML = ghostInfo;
		},
		onFailure: function() {
			document.getElementById("VGinfo").innerHTML = "No more ghosts or disabled?";
		}
	});
	set_panel_html(html);
	showStatus ("Next Ghost times", false);
	return true;
}

