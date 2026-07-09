<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\GasReading;

class DashboardController extends Controller
{
    public function index() {
        $readings = GasReading::latest()
            ->take(20)
            ->get();
        return view('gas-dashboard', compact('readings'));
    }
}
