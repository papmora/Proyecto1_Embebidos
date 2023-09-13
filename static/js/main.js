document.addEventListener("DOMContentLoaded", function() {



    // Función para alternar el estado de los botones de luz
    function toggleLight(button) {
        if (button.classList.contains("on-button")) {
            button.innerHTML = '<i class="far fa-lightbulb"></i>';
            button.classList.remove("on-button");
            button.classList.add("off-button");
        } else {
            button.innerHTML = '<i class="fas fa-lightbulb"></i>';
            button.classList.remove("off-button");
            button.classList.add("on-button");
        }
    }


    // Función para alternar el estado de los botones de la puerta
    function toggleDoor(button) {
        if (button.classList.contains("open-button")) {
            button.innerHTML = '<i class="fas fa-door-closed"></i>';
            button.classList.remove("open-button");
            button.classList.add("close-button");
        } else {
            button.innerHTML = '<i class="fas fa-door-open"></i>';
            button.classList.remove("close-button");
            button.classList.add("open-button");
        }
    }



    // Función para alternar el estado de los botones de la cámara
    function toggleCamera(button) {
        // Agrega aquí la lógica para la cámara, como abrir una vista previa o realizar una acción específica
        alert("Cámara activada.");
    }



    // Eventos de clic para los botones de luz de Cuarto 1
    var cuarto1LightButton = document.getElementById("cuarto1-light");
    cuarto1LightButton.addEventListener("click", function () {
        toggleLight(cuarto1LightButton);
    });

    // Eventos de clic para los botones de puerta de Cuarto 1
    var cuarto1DoorButton = document.getElementById("cuarto1-door");
    cuarto1DoorButton.addEventListener("click", function () {
        toggleDoor(cuarto1DoorButton);
    });


    // Eventos de clic para los botones de luz de Cuarto 2
    var cuarto2LightButton = document.getElementById("cuarto2-light");
    cuarto2LightButton.addEventListener("click", function () {
        toggleLight(cuarto2LightButton);
    });

    // Eventos de clic para los botones de puerta de Cuarto 2
    var cuarto2DoorButton = document.getElementById("cuarto2-door");
    cuarto2DoorButton.addEventListener("click", function () {
        toggleDoor(cuarto2DoorButton);
    });



    // Eventos de clic para los botones de luz de Sala
    var salaLightButton = document.getElementById("sala-light");
    salaLightButton.addEventListener("click", function () {
        toggleLight(salaLightButton);
    });

    // Eventos de clic para los botones de puerta de Sala
    var salaDoorButton = document.getElementById("sala-door");
    salaDoorButton.addEventListener("click", function () {
        toggleDoor(salaDoorButton);
    });


    // Eventos de clic para los botones de luz de Comedor
    var comedorLightButton = document.getElementById("comedor-light");
    comedorLightButton.addEventListener("click", function () {
        toggleLight(comedorLightButton);
    });


    // Eventos de clic para los botones de luz de Servicio
    var servicioLightButton = document.getElementById("servicio-light");
    servicioLightButton.addEventListener("click", function () {
        toggleLight(servicioLightButton);
    });

    // Eventos de clic para los botones de luz de Cocina
    var cocinaLightButton = document.getElementById("cocina-light");
    cocinaLightButton.addEventListener("click", function () {
        toggleLight(cocinaLightButton);
    });

    // Eventos de clic para los botones de luz de Garaje
    var garajeLightButton = document.getElementById("garaje-light");
    garajeLightButton.addEventListener("click", function () {
        toggleLight(garajeLightButton);
    });




    // Evento de clic para el botón de la cámara de Jardin
    var jardinCameraButton = document.getElementById("jardin-camera");
    jardinCameraButton.addEventListener("click", function () {
        // Agrega aquí la lógica para la cámara, como abrir una vista previa o realizar una acción específica
        alert("Cámara de jardin activada.");
    });

    // Eventos de clic para los botones de puerta de Jardin
    var jardinDoorButton = document.getElementById("jardin-door");
    jardinDoorButton.addEventListener("click", function () {
        toggleDoor(jardinDoorButton);
    });



    // funcion para refrescar la pagina cada 10 segundos 
    //setInterval(function() {
    //    location.reload();
    //}, 10000);




});