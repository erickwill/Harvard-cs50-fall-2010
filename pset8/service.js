/****************************************************************************
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 ***************************************************************************/

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 35;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// global array for bus passengers
var bus_pass = new Array(SEATS);

// global passenger counter
var count = 0;

// global arrays for passenger markers
var mark_pass = new Array();
var mark_bld = new Array();

// global array for map markers
var markersArray = new Array();

// global array for earth points
var placemark = new Array();

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});


/*
 * void
 * dropoff()
 *
 * Drops up passengers if their stop is nearby.
 */

function dropoff()
{
    // if shuttle is empty; exit
    if (count == 0)
    {
        document.getElementById("announcements").innerHTML = "No passengers!";	
	return;
    }


    var foo = false;         // boolean to check if shuttle is close enough to a destination
    var found = new Array(); // array for shuttle passengers getting off
    var ct = 0;              // # of passengers dropping off
    var i = 0;               // variable to iterate through shuttle

    // iterate through shuttle
    for (i; i < count; i++)
    {
        var tmpho = bus_pass[i].house;  // passenger house
        var tmplat = HOUSES[tmpho].lat; // house latitude
        var tmplng = HOUSES[tmpho].lng; // house longitude

        // check distance from shuttle to houses
        var d = shuttle.distance(tmplat, tmplng);

        // log how many passengers are getting off and their place in the shuttle array
     	if (d < 30)
   	{ 
            found[ct] = i;
            ct++;
            count--;
	    foo = true;
	}    	

    }

    // remove passengers from shuttle array
    bus_pass.splice(found[0], ct);

    // annouce if shuttle is too far from house
    if (foo == false)
    {
        document.getElementById("announcements").innerHTML = "Not close enough to destination!";
	return;
    }

    // prepare to write passenger list
    document.getElementById("seats").innerHTML = "";

    // iterate over current passenger array
    for (var j = 0; j < SEATS; j++)
    {
        // print name and destination	
	if (bus_pass[j] != null)
            document.getElementById("seats").innerHTML += "<li>" + bus_pass[j].name + " --> " + bus_pass[j].house + "</li>";
	else
	    document.getElementById("seats").innerHTML += "<li>Empty Seat</li>";
    }
}


/*
 * void
 * failureCB(errorCode)
 *
 * Called if Google Earth fails to load.
 */

function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}


/*
 * void
 * frameend()
 *
 * Handler for Earth's frameend event.
 */

function frameend() 
{
    shuttle.update();
}


/*
 * void
 * initCB()
 *
 * Called once Google Earth has loaded.
 */

function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
     heading: HEADING,
     height: HEIGHT,
     latitude: LATITUDE,
     longitude: LONGITUDE,
     planet: earth,
     velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // populate Earth with passengers and houses
    populate();
}


/*
 * boolean
 * keystroke(event, state)
 *
 * Handles keystrokes.
 */

function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        document.getElementById("announcements").innerHTML = "no announcements at this time";
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        document.getElementById("announcements").innerHTML = "no announcements at this time";
        return false;
    }
  
    return true;
}


/*
 * void
 * load()
 *
 * Loads application.
 */

function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map(document.getElementById("map"), {
     center: latlng,
     disableDefaultUI: true,
     mapTypeId: google.maps.MapTypeId.ROADMAP,
     navigationControl: true,
     scrollwheel: false,
     zoom: 17
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
     icon: "http://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
     map: map,
     title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/*
 * void
 * pickup()
 *
 * Picks up nearby passengers.
 */

function pickup()
{
    // check if bus is full
    if (count == SEATS)
    {
	document.getElementById("announcements").innerHTML = "The shuttle is full!!!";
	return;
    }    
    
    // boolean to check if passenger is close enough to bus
    var foo = false;

    // iterate through markers
    for (var i = 0; i < mark_pass.length; i++)
    {
        // check distance from bus to passengers
    	var d = shuttle.distance(mark_bld[i].lat, mark_bld[i].lng);

        // if close enough and seats available
     	if (d < 15 && count < SEATS )
   	    {

        var found = false; // already on bus
        for (var j = 0; j < bus_pass.length; j++)
        {
            if (mark_pass[i] == bus_pass[j])
            {
                found = true;
                return;
            }
        }
        if (!found)
	        bus_pass[count] = mark_pass[i];	// add passenger to bus array
	    
	        markersArray[i].setMap(null);       // hide map marker
            var features = earth.getFeatures(); // hide earth placemark
            features.removeChild(placemark[i]); // 
            count++;                            // track available seats
	    }    	

        // we found a passenger
	    if (d < 15)
	        foo = true;
    }

    // make announcement if not close enough to passenger
    if (!foo)
    {
	document.getElementById("announcements").innerHTML = "No passenger found!";
    }

    bus_pass.sort(function(a, b){
	var nameA=a.house.toLowerCase(), nameB=b.house.toLowerCase()
	if (nameA < nameB) //sort string ascending
	    return -1 
	if (nameA > nameB)
	    return 1
	return 0 //default return value (no sorting)
    })

    // prepare to write passenger list
    document.getElementById("seats").innerHTML = "";

    // iterate over current passenger array
    for (var j = 0; j < bus_pass.length; j++)
    {
        // print name and destination	
	if (bus_pass[j] != null)
            document.getElementById("seats").innerHTML += "<li>" + bus_pass[j].name + " --> " + bus_pass[j].house + "</li>";
	else
	    document.getElementById("seats").innerHTML += "<li>Empty Seat</li>";
    }

    // check if bus is full
    if (count == SEATS)
    {
	document.getElementById("announcements").innerHTML = "The shuttle is full!!!";
	return;
    }    
}

function alreadyOnBus()
{

}

/*
 * void
 * populate()
 *
 * Populates Earth with passengers and houses.
 */

function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
         icon: "http://google-maps-icons.googlecode.com/files/home.png",
         map: map,
         position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
         title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark AND KEEP TRACK OF THEM IN ARRAY!!!!
        placemark[i] = earth.createPlacemark("");
        placemark[i].setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/passengers/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(5.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark[i].setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(2.0);

        // associate placemark with point
        placemark[i].setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark[i]);

 	// remember map marker
        mark_pass[i] = PASSENGERS[i]; 	
	mark_bld[i] = building;

        // add marker to map
        var marker = new google.maps.Marker({
         icon: "http://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
         map: map,
         position: new google.maps.LatLng(building.lat, building.lng),
         title: PASSENGERS[i].name + " at " + building.name
        }); markersArray.push(marker); // ADD MARKER TO ARRAY!
    }
}


/*
 * void
 * viewchange()
 *
 * Handler for Earth's viewchange event.
 */

function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}


/*
 * void
 * unload()
 *
 * Unloads Earth.
 */

function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}
