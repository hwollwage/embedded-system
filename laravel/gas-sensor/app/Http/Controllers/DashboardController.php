<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\GasReading;

class DashboardController extends Controller
{
    public function index() {
        $readings = GasReading::latest()->get();

        return view('welcome', compact('readings'));
    }
}
