#Sistema operativo que nosotros queremos pero podemos poner node 
#porque hay varias imagenes subidas con versiones con linux y node sobre ella
# con :alpine podemos definir  la version de linux que queremos usar
#alpine es una que pesa muy poquito
FROM node:alpine

# con copy copiamos los archivos que se encuentran en el directorio y los vamos a meter en nuestra imagen
COPY . /app
#ingresar al directorio de trabajo del tiron
WORKDIR /app
#ejecutamos node y le pasamos la ruta de donde esta nuestros archivos
CMD node app.js

#Comandos ejecutados en la terminal
#construimos la imgane con "docker build -t hola-mundo(nombre de la imagne) .(direccion del archivo Dockerfile)"
#con "docker image ls" enlistamos todas las imagenes de la maquina
#con "docker run hola-mundo" ejecutamos la imagen y la transformamos en un contenedor
#ahora la puedo subir a dockerhub y luego 