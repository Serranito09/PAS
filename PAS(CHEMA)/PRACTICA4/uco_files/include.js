function includeHTML() {
  var z, i, elmnt, file, xhttp;
  z = document.getElementsByTagName("*");
  for (i = 0; i < z.length; i++) {
    elmnt = z[i];
    file = elmnt.getAttribute("include-html");
    if (file) {
      xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
          if (this.status == 200) {elmnt.innerHTML = this.responseText;}
          if (this.status == 404) {elmnt.innerHTML = "Error al cargar, recargue ventana por favor.";}
          elmnt.removeAttribute("include-html");
          includeHTML();
        }
      }      
      xhttp.open("GET", file, true);
      xhttp.send();
      return;
    }
  }
};
//Lanzamos al cargar todo
window.onload = function() {
	includeHTML();
};

//Botones (no usado)
var botones = {
		"sede electrónica" : "https://sede.uco.es/",
		"transparencia y RRSS" : "https://www.uco.es/servicios/informatica/sag/sag-uco-16/",
		"BOUCO": "https://sede.uco.es/bouco/",
		"factura electrónica" : "https://www.uco.es/servicios/informatica/sag/sag-uco-18/",
		"portal del personal" : "https://www.uco.es/servicios/informatica/sag/sag-uco-13/",
		"actualidad universitaria" : "servicios/actualidad/"
};

