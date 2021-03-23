# CGPIO
Usando gpiod na beaglebone

Primeiros testes para validar funcionamento com C. 


Por algum motivo sempre depois do boot precisa executar o config-pingpio.sh. Preciso avalair como fazer em C




Procedimento para crosscompile


Procedimento base https://github.com/dockcross/dockcross

No Fedora é necessário desabilitar o SELinux

sudo setenforce=0

docker run --rm  dockcross/linux-armv7a > dockcross-linux-armv7a
chmod +x ./dockcross-linux-armv7a 

./dockcross-linux-armv7a bash -c '$CC src/hello.c -o helloCross'