<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class GasReading extends Model
{
    protected $fillable = [
        'device_id',
        'gas_value',
        'alarm',
        'ip_address',
        'wifi_rssi',
        'uptime_ms',
        'free_heap',
    ];
}
