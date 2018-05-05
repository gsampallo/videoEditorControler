# videoEditorControler
Controlador en base a un encoder rotativo para un editor de video

Se utilizan las bibliotecas:
Rotary https://github.com/brianlow/Rotary para recibir correctamente los datos del encoder rotativo
HID https://github.com/NicoHood/HID para enviar las macros al sistema operativo.

Utilizo el Arduino Pro Micro, porque esta armado sobre la base de Arduino Leonardo, otras versiones de Arduino pueden no ser compatibles por el tipo de micro que tienen.

En el esquematico se utilizo Arduino Leonardo, pero la ubicacion de los pines y el conexionado es similar
![alt text](https://raw.githubusercontent.com/gsampallo/videoEditorControler/master/video_editor_controler_bb.png "Esquematico")