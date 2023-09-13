from flask import Flask, render_template, request, redirect, url_for, jsonify

from ctypes import *

# Carga la biblioteca dinámica (.so)
#my_library = ctypes.CDLL('./archivo.so')


app = Flask(__name__)

###-----------------Funciones para ejecutar las funciones en C-----------

#@app.route('/encender_luz', methods=['GET'])
#def api_encender_luz():
#    resultado = encender_luz()
#    return jsonify({'estado_luz': resultado})

#@app.route('/apagar_luz', methods=['GET'])
#def api_encender_luz():
#    resultado = apagar_luz()
#    return jsonify({'estado_luz': resultado})

#@app.route('/puertas', methods=['GET'])
#def get_puertas():
#    js = util.readFile('jsonAPI.txt')
#    puertas = js['puertas']
#    print(puertas)
#    for puerta in puertas:
#        state = controlFunctions.state_door(puerta['id'])
#        puerta['state'] = state
#    print(puertas)
#    util.writeFile('jsonAPI.txt', js)
#    return jsonify(puertas)

#@app.route('/camara', methods=['GET'])
#def get_foto():
#    #Llamar camara
#    os.system("fswebcam /media/image.jpg")
#    imageB64 = util.readImage('/media/image.jpg')
#    return jsonify({"camara": imageB64})





######----------------rutas de pagina
@app.route('/')
def login():
    return render_template('login.html')


####-------- ruta de autenticacion 

@app.route('/auth', methods=['POST'])
def auth():
    # Aquí debes agregar la lógica de autenticación
    username = request.form.get('username')
    password = request.form.get('password')

    if username == 'pablo' and password == 'pablo':
        return redirect(url_for('inicio'))
    else:
        error_message = "Credenciales incorrectas. Inténtalo de nuevo."
        return render_template('login.html', error_message=error_message)

@app.route('/inicio')
def inicio():
    return render_template('index.html', year=2023)

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)

