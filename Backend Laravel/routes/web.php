<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\inputController;  #Input information controller

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider and all of them will
| be assigned to the "web" middleware group. Make something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

/*Route::get('/pushData', function () {
    return ("Esto es un retorno de informacion");
});*/

Route::get('/input', function(){
    return ("Escribe los datos en el siguiente orden para subir la información a la base dedatos. (Separados por '/') <br> 1. Humedad en suelo<br>2. Humedad en ambiente<br>3. Temperatura de ambiente<br>4. Luz del ambiente<br>5. Espectro de rayos UV");
});


Route::post('/input/{user_floor_humidity}/{user_atmosphere_humidity}/{user_temperature}/{user_light}/{user_uv}', function ($user_floor_humidity, $user_atmosphere_humidity, $user_temperature, $user_light, $user_uv) {
    
});