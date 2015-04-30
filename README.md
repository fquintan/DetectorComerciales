# DetectorComerciales
Tarea 2 del curso de Busqueda por Contenido de Imagenes y Videos

-Para compilar:
	ejecutar make desde la carpeta principal

-Para ejecutar extractor:
	extractor inputDirname descriptor outputDirname

	ejecutar para los comerciales y el video largo

-Para ejectutar detector:
	detector comercialesDirname videoLargoDirname outputDirname limit
	Limit indica hasta que descriptor del video largo realizar la búsqueda (para testear)
	para correrlo pata todo el video usar limit > 72000

Alternativamente se pueden usar los scripts script_extractor.sh y script_detector.sh para correr la extracción y búsqueda para todos las configuraciones.

