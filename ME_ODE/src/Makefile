all:
	cl /W3 /nologo ode.c /link /DLL /out:ode.dll
	copy ode.dll binaries\win64
	7z a -r -tzip ode.fmu binaries modelDescription.xml