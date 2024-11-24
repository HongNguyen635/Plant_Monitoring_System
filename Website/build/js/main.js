// global variable visible to all javascript functions
var xmlHttp = createXmlHttpObject();

// var save the config values (not sent yet)
var airTempRate = 1;
var soilRate = 1;
var photocellRate = 1;

// function to create XML object
function createXmlHttpObject() {
  if (window.XMLHttpRequest) {
    xmlHttp = new XMLHttpRequest();
  } else {
    xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
  }
  return xmlHttp;
}

// function to handle button press from HTML code above
// and send a processing string back to server
// this processing string is use in the .on method
function configBtnPress() {
  var xhttp = new XMLHttpRequest();
  var message;
  // if you want to handle an immediate reply (like status from the ESP)
  // handling of the button press use this code
  // since this button status from the ESP is in the main XML code
  // we don't need this
  // remember that if you want immediate processing feedback you must send it
  // in the ESP handling function and here
  /*
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        message = this.responseText;
        // update some HTML data
      }
    }
    */

  // NOTE: whatever you name the server.on "/name" is
  // you need to put the "name" in 2nd arg of open below

  // NOTE: ? is a delimiter
  // first arg config is use in the .on method
  // server.on("/config", updateConfig);
  // then the second arg VALUE is use in the processing function
  // String t_state = server.arg("VALUE");
  // then + the configs value property
  xhttp.open(
    "PUT",
    "/config?airTempRate=" +
      airTempRate +
      "&soilRate=" +
      soilRate +
      "&photocellRate=" +
      photocellRate,
    true
  );
  xhttp.send();
}

// TODO: finish the following methods
function airTempBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/airTempBtn", false);
  xhttp.send();
}

function soilBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/soilBtn", false);
  xhttp.send();
}

function photocellBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/photocellBtn", false);
  xhttp.send();
}

function irBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/irBtn", false);
  xhttp.send();
}

function wateringBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/waterBtn", false);
  xhttp.send();
}

function growLightBtnPress() {
  var xhttp = new XMLHttpRequest();

  xhttp.open("PUT", "/growLightBtn", false);
  xhttp.send();
}

function updateAirTempSlider(value) {
  airTempRate = value;
}

function updateSoilSlider(value) {
  soilRate = value;
}

function updatePhotocellSlider(value) {
  photocellRate = value;
}

// function to handle the response from the ESP
// TODO: complete this. 349
function response() {}

// general processing code for the web page to ask for an XML stream
// this is actually why you need to keep sending data to the page to
// force this call with stuff like this
// server.on("/xml", SendXML);
// otherwise the page will not request XML from the ESP,
// and updates will not happen
function process() {
  if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
    xmlHttp.open("PUT", "xml", true);
    xmlHttp.onreadystatechange = response;
    xmlHttp.send(null);
  }
  // you may have to play with this value, big pages need more porcessing time,
  // and hence, a longer timeout
  setTimeout("process()", 100);
}
