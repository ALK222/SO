cd ~/so 
chmod -r ./pruebas
ls pruebas
echo "hola" > pruebas/f1.txt
cat pruebas/f1.txt # No autocompleta
chmod +r ./pruebas
chmod -x ./pruebas
cat pruebas/f1.txt # No deja ejecutar cat encima
chmod +x ./pruebas
chmod -w ./pruebas
echo "final" > pruebas/f1.txt
touch pruebas/f2.txt
mv pruebas/f1.txt pruebas/f3.txt
