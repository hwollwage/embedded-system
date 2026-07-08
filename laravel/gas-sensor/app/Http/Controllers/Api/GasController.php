<?php

namespace App\Http\Controllers\Api;

use App\Http\Controllers\Controller;
use App\Models\GasReading;
use Illuminate\Http\Request;

class GasController extends Controller
{
    public function store(Request $request) {
        $validated = $request->validate([
            'device_id' => 'required|string|max:50',
            'gas_value' => 'required|integer',
            'alarm' => 'required|boolean'
        ]);

        $reading = GasReading::create([
            'device_id' => $validated['device_id'],
            'gas_value' => $validated['gas_value'],
            'alarm' => $validated['alarm'],
        ]);

        return response()->json([
            'status' => 'success',
            'id' => $reading->id,
            'message' => 'Reading stored successfully'
        ]);
    }
}
