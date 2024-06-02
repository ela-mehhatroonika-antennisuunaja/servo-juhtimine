Arduino võtab andmeid sisse JSON kujul:
```
{
"hor_dir" : int,
"vert_dir : int, 
"initialbear" : int #kui see on -1, siis kasutatakse kaasatulevat antenni.
}
```
Kõik nurgad kraadides (ja hetkel täisarvud).
Seega saab suunajale kergesti tekitada uusi rakendusi, sest liigutamiseks võtab sisendina ainult kolm nurka.
