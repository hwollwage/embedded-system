<?php

namespace App\Http\Controllers\Api;

use App\Http\Controllers\Controller;
use Illuminate\Http\Request;

use App\Models\GasReading;

class GasController extends Controller
{
    public function store(Request $request) {
        $validated = $request->validate([
            'device_id' => 'required|string|max:50',
            'gas_value' => 'required|integer',
            'alarm' => 'required|boolean',
            'ip_address' => 'required|ip',
            'wifi_rssi' => 'required|integer',
            'uptime_ms' => 'required|integer',
            'free_heap' => 'required|integer'
        ]);

        $reading = GasReading::create($validated);

        return response()->json([
            'status' => 'success',
            'id' => $reading->id,
            'message' => 'reading stored successfully'
        ], 200);
    }
}
