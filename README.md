# Peaks_Code

Usare **schema.sql** per generare il database

Libreria OpenPGP: usare branch *pks_branch* e compilare con *make gpg-compatible*
Librerie NTL e GMP: lanciare *./compile_libraries.sh release* (o debug a seconda del build type richiesto)

Applicativi C++: compilare con "*cmake -DCMAKE_BUILD_TYPE=Release .*" (o debug a seconda del build type richiesto). L'eseguibile verrà creato nella sottocartella *bin*.

Recon Daemon: compilare con il classico *make*. Per creare l'albero lanciare sks con il parametro *pbuild*, per eseguire il recon daemon lanciare sks con il parametro *recon*.
