# Othello
Proyecto 2 de Inteligencia Artificial I - USB Abril-Julio 2015

**Integrantes:**

    10-10666 Andrea Salcedo
    10-10757 Reinaldo Verdugo

### Para compilar:

`make`

### Para correr:

`./othello <algoritmo> <nombreArchivo>`

### Para correr por 10 minutos:

`./othello <algoritmo> <nombreArchivo> & PID=$!; sleep 600; kill $PID`

\<algoritmo\>:
  - 1: negamax
  - 2: negamax alpha-beta
  - 3: scout
  - 4: negascout

\<nombreArchivo\>:
  - Archivo donde se guarda los resultados
  - Es opcional y el valor por defecto es result.txt

### Resultados
  - Los resultados de los algoritmos están guardados en la carpeta **results/**
  - El informe se encuentra en la carpeta **docs/**
