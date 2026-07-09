<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\Api\GasController;

Route::post('/gas', [GasController::class, 'store']);