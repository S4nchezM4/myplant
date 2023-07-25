<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class inputController extends Controller
{
    public function __invoke($temp, $hum_a, $hum_f, $uv){
        return("Temperatura: $temp<br> Humedad en el ambiente: $hum_a<br> Humedad en el suelo: $hum_f<br> Rango de rayos UV: $uv<br>        
        Bienvenido a la pagina que recibe los datos del sensor
        
        
        ");
    }
}
