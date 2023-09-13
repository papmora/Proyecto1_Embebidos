document.addEventListener('DOMContentLoaded', function() {
    var form = document.getElementById('login-form');
    var errorMessage = document.querySelector('.error-message');

    form.addEventListener('submit', function(event) {
        event.preventDefault();
        errorMessage.textContent = '';

        var username = document.getElementById('username').value;
        var password = document.getElementById('password').value;

        // Realiza la validación de las credenciales aquí o envía una solicitud al servidor para verificarlas
        // Si las credenciales son válidas, el formulario se enviará a /auth automáticamente
        // De lo contrario, muestra un mensaje de error
        if (username === 'pablo' && password === 'pablo') {
            form.submit();
        } else {
            errorMessage.textContent = 'Credenciales incorrectas. Inténtalo de nuevo.';
        }
    });
});
