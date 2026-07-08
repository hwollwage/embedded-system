<?php

namespace App\Http\Controllers\Api;

use App\Http\Controllers\Controller;
use App\Models\GasReading;
use Illuminate\Http\Request;

class GasController extends Controller
{
    public function store(Request $request) {
        $request->validate([
            'gas' => 'required|integer'
        ]);

        GasReading::create([
            'gas_value' => $request->gas
        ]);

        return response()->json([
            'status' => 'success'
        ]);
    }
}
