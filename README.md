# Async Addon

Este repositorio contiene el código que utilice como demostración para la charla  [Extensiones nativas en NodeJS: Cómo y por qué?](https://docs.google.com/presentation/d/1yBYuXJgpCLtAhYE2RMtd8ORgmlqtxN8hItZOVJBNLHw/edit?usp=sharing)

Para construir la extensión nativa solo necesitamos correr `npm install`.

Luego, ejecutamos `npm start` el cual va a levantar un web server express en el puerto 3000 con dos endpoints definidos:
* `/sync` - ejecuta un código JS sincronico
* `/async` - ejecuta la extensión nativa

Nota: Este repositorio fue desarrollado usando la version 8.9.1 de node. Esta definido en el archivo `.nvmrc`.

### Contacto
Twitter: @btomoretti

Email: marianomoretti.87@gmail.com