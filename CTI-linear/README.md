# Linear CTI law for Ice

Detail can be found in Mansuy 2001 \[6.3.3\] or Burr 2017 \[1.2.1.4\]

## Equations

This equation is link to the crystal coordinate system :

<a href="https://www.codecogs.com/eqnedit.php?latex=\left\{&space;\begin{array}{rcl}&space;\sigma_{11}-\sigma_{22}&space;&&space;=&space;&&space;2\eta_{12}(\dot{\varepsilon}_{11}-\dot{\varepsilon}_{22})&space;\\&space;\sigma_{33}&space;&=&&space;2\eta_{12}\frac{4\alpha-1}{3}\dot{\varepsilon}_{33}&space;\\&space;\sigma_{23}&space;&=&&space;2\eta_{12}\beta\dot{\varepsilon}_{23}&space;\\&space;\sigma_{31}&space;&=&&space;2\eta_{12}\beta\dot{\varepsilon}_{31}&space;\\&space;\sigma_{12}&space;&=&&space;2\eta_{12}\dot{\varepsilon}_{12}&space;\\&space;\end{array}&space;\right." target="_blank"><img src="https://latex.codecogs.com/gif.latex?\left\{&space;\begin{array}{rcl}&space;\sigma_{11}-\sigma_{22}&space;&&space;=&space;&&space;2\eta_{12}(\dot{\varepsilon}_{11}-\dot{\varepsilon}_{22})&space;\\&space;\sigma_{33}&space;&=&&space;2\eta_{12}\frac{4\alpha-1}{3}\dot{\varepsilon}_{33}&space;\\&space;\sigma_{23}&space;&=&&space;2\eta_{12}\beta\dot{\varepsilon}_{23}&space;\\&space;\sigma_{31}&space;&=&&space;2\eta_{12}\beta\dot{\varepsilon}_{31}&space;\\&space;\sigma_{12}&space;&=&&space;2\eta_{12}\dot{\varepsilon}_{12}&space;\\&space;\end{array}&space;\right." title="\left\{ \begin{array}{rcl} \sigma_{11}-\sigma_{22} & = & 2\eta_{12}(\dot{\varepsilon}_{11}-\dot{\varepsilon}_{22}) \\ \sigma_{33} &=& 2\eta_{12}\frac{4\alpha-1}{3}\dot{\varepsilon}_{33} \\ \sigma_{23} &=& 2\eta_{12}\beta\dot{\varepsilon}_{23} \\ \sigma_{31} &=& 2\eta_{12}\beta\dot{\varepsilon}_{31} \\ \sigma_{12} &=& 2\eta_{12}\dot{\varepsilon}_{12} \\ \end{array} \right." /></a>

### Linear algebric formulation

<a href="https://www.codecogs.com/eqnedit.php?latex=\sigma=2\eta_{12}\left[\dot{\varepsilon}&plus;\left[2(\alpha&plus;\beta)M-\frac{2}{3}(\alpha-1)I&space;\right]Tr(M\dot{\varepsilon})&plus;(\beta-1)(M\dot{\varepsilon}&plus;\dot{\varepsilon}M)&space;\right]" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\sigma=2\eta_{12}\left[\dot{\varepsilon}&plus;\left[2(\alpha&plus;\beta)M-\frac{2}{3}(\alpha-1)I&space;\right]Tr(M\dot{\varepsilon})&plus;(\beta-1)(M\dot{\varepsilon}&plus;\dot{\varepsilon}M)&space;\right]" title="\sigma=2\eta_{12}\left[\dot{\varepsilon}+\left[2(\alpha+\beta)M-\frac{2}{3}(\alpha-1)I \right]Tr(M\dot{\varepsilon})+(\beta-1)(M\dot{\varepsilon}+\dot{\varepsilon}M) \right]" /></a>

### Linear case

<a href="https://www.codecogs.com/eqnedit.php?latex=\eta_{12}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\eta_{12}" title="\eta_{12}" /></a> is a constant

## Compilation
First you should compile the Ice_CTI.cc

`make`

Ice_CTI, mesh.sh and wrapper.sh sould be executable :

`chmod 750 Ice_CTI`

Then run mesh with the proper file name inside :

`./mesh.sh`

Therefore you can execute the code using the wrapper:

`./wrapper.sh`
